/*
 * Registers as a embed container
 * Copyright (C) 2015 <davidedmundson@kde.org> David Edmundson
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#include "fdoselectionmanager.h"

#include <QCoreApplication>
#include <QHash>
#include <QTimer>
#include <QDebug>

#include <QTextDocument>
#include <QX11Info>

#include <KWindowSystem>
#include <KSelectionOwner>

#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include <xcb/xcb_event.h>
#include <xcb/composite.h>
#include <xcb/damage.h>

#include "xcbutils.h"
#include "sniproxy.h"

#define SYSTEM_TRAY_REQUEST_DOCK    0
#define SYSTEM_TRAY_BEGIN_MESSAGE   1
#define SYSTEM_TRAY_CANCEL_MESSAGE  2

FdoSelectionManager::FdoSelectionManager():
    QObject(),
    m_selectionOwner(new KSelectionOwner(Xcb::atoms->selectionAtom, -1, this))
{
    qDebug() << "starting";

    //we may end up calling QCoreApplication::quit() in this method, at which point we need the event loop running
    QTimer::singleShot(0, this, &FdoSelectionManager::init);
}

FdoSelectionManager::~FdoSelectionManager()
{
    qDebug() << "closing";
    m_selectionOwner->release();
}

void FdoSelectionManager::init()
{
    //load damage extension
    xcb_connection_t *c = QX11Info::connection();
    xcb_prefetch_extension_data(c, &xcb_damage_id);
    const auto *reply = xcb_get_extension_data(c, &xcb_damage_id);
    if (reply->present) {
        m_damageEventBase = reply->first_event;
        xcb_damage_query_version_unchecked(c, XCB_DAMAGE_MAJOR_VERSION, XCB_DAMAGE_MINOR_VERSION);
    } else {
        //no XDamage means
        qCritical() << "could not load damage extension. Quitting";
        qApp->exit(-1);
    }

    qApp->installNativeEventFilter(this);

    connect(m_selectionOwner, &KSelectionOwner::claimedOwnership, this, &FdoSelectionManager::onClaimedOwnership);
    connect(m_selectionOwner, &KSelectionOwner::failedToClaimOwnership, this, &FdoSelectionManager::onFailedToClaimOwnership);
    connect(m_selectionOwner, &KSelectionOwner::lostOwnership, this, &FdoSelectionManager::onLostOwnership);
    m_selectionOwner->claim(false);
}

bool FdoSelectionManager::addDamageWatch(xcb_window_t client)
{
    qDebug() << "adding damage watch for " << client;

    xcb_connection_t *c = QX11Info::connection();
    const auto attribsCookie = xcb_get_window_attributes_unchecked(c, client);

    const auto damageId = xcb_generate_id(c);
    m_damageWatches[client] = damageId;
    xcb_damage_create(c, damageId, client, XCB_DAMAGE_REPORT_LEVEL_NON_EMPTY);

    xcb_generic_error_t *error = nullptr;
    QScopedPointer<xcb_get_window_attributes_reply_t, QScopedPointerPodDeleter> attr(xcb_get_window_attributes_reply(c, attribsCookie, &error));
    QScopedPointer<xcb_generic_error_t, QScopedPointerPodDeleter> getAttrError(error);
    uint32_t events = XCB_EVENT_MASK_STRUCTURE_NOTIFY;
    if (!attr.isNull()) {
        events = events | attr->your_event_mask;
    }
    // if window is already gone, there is no need to handle it.
    if (getAttrError && getAttrError->error_code == XCB_WINDOW) {
        return false;
    }
    // the event mask will not be removed again. We cannot track whether another component also needs STRUCTURE_NOTIFY (e.g. KWindowSystem).
    // if we would remove the event mask again, other areas will break.
    const auto changeAttrCookie = xcb_change_window_attributes_checked(c, client, XCB_CW_EVENT_MASK, &events);
    QScopedPointer<xcb_generic_error_t, QScopedPointerPodDeleter> changeAttrError(xcb_request_check(c, changeAttrCookie));
    // if window is gone by this point, it will be caught by eventFilter, so no need to check later errors.
    if (changeAttrError && changeAttrError->error_code == XCB_WINDOW) {
        return false;
    }

    return true;
}

bool FdoSelectionManager::nativeEventFilter(const QByteArray& eventType, void* message, long int* result)
{
    Q_UNUSED(result);

    if (eventType != "xcb_generic_event_t") {
        return false;
    }

    xcb_generic_event_t* ev = static_cast<xcb_generic_event_t *>(message);

    const auto responseType = XCB_EVENT_RESPONSE_TYPE(ev);
    if (responseType == XCB_CLIENT_MESSAGE) {
        const auto ce = reinterpret_cast<xcb_client_message_event_t *>(ev);
        if (ce->type == Xcb::atoms->opcodeAtom) {
            switch (ce->data.data32[1]) {
                case SYSTEM_TRAY_REQUEST_DOCK:
                    dock(ce->data.data32[2]);
                    return true;
            }
        }
    } else if (responseType == XCB_UNMAP_NOTIFY) {
        const auto unmappedWId = reinterpret_cast<xcb_unmap_notify_event_t *>(ev)->window;
        if (m_proxies.contains(unmappedWId)) {
            undock(unmappedWId);
        }
    } else if (responseType == XCB_DESTROY_NOTIFY) {
        const auto destroyedWId = reinterpret_cast<xcb_destroy_notify_event_t *>(ev)->window;
        if (m_proxies.contains(destroyedWId)) {
            undock(destroyedWId);
        }
    } else if (responseType == m_damageEventBase + XCB_DAMAGE_NOTIFY) {
        const auto damagedWId = reinterpret_cast<xcb_damage_notify_event_t *>(ev)->drawable;
        const auto sniProx = m_proxies.value(damagedWId);
        if(sniProx) {
            sniProx->update();
            xcb_damage_subtract(QX11Info::connection(), m_damageWatches[damagedWId], XCB_NONE, XCB_NONE);
        }
    }

    return false;
}

void FdoSelectionManager::dock(xcb_window_t winId)
{
    qDebug() << "trying to dock window " << winId;

    if (m_proxies.contains(winId)) {
        return;
    }

    if (addDamageWatch(winId)) {
        m_proxies[winId] = new SNIProxy(winId, this);
    }
}

void FdoSelectionManager::undock(xcb_window_t winId)
{
    qDebug() << "trying to undock window " << winId;

    if (!m_proxies.contains(winId)) {
        return;
    }
    m_proxies[winId]->deleteLater();
    m_proxies.remove(winId);
}

void FdoSelectionManager::onClaimedOwnership()
{
    qDebug() << "Manager selection claimed";

    connect(KWindowSystem::self(), &KWindowSystem::compositingChanged, this, &FdoSelectionManager::compositingChanged);
    compositingChanged();
}

void FdoSelectionManager::onFailedToClaimOwnership()
{
    qWarning() << "failed to claim ownership of Systray Manager";
    qApp->exit(-1);
}

void FdoSelectionManager::onLostOwnership()
{
    qWarning() << "lost ownership of Systray Manager";
    disconnect(KWindowSystem::self(), &KWindowSystem::compositingChanged, this, &FdoSelectionManager::compositingChanged);
    qApp->exit(-1);
}

void FdoSelectionManager::compositingChanged()
{
    xcb_connection_t *c = QX11Info::connection();
    auto screen = xcb_setup_roots_iterator (xcb_get_setup (c)).data;
    auto trayVisual = screen->root_visual;
    if (KWindowSystem::compositingActive()) {
        xcb_depth_iterator_t depth_iterator = xcb_screen_allowed_depths_iterator(screen);
        xcb_depth_t *depth = nullptr;

        while (depth_iterator.rem) {
            if (depth_iterator.data->depth == 32) {
                depth = depth_iterator.data;
                break;
            }
            xcb_depth_next(&depth_iterator);
        }

        if (depth) {
            xcb_visualtype_iterator_t visualtype_iterator = xcb_depth_visuals_iterator(depth);
            while (visualtype_iterator.rem) {
                xcb_visualtype_t *visualtype = visualtype_iterator.data;
                if (visualtype->_class == XCB_VISUAL_CLASS_TRUE_COLOR) {
                    trayVisual = visualtype->visual_id;
                    break;
                }
                xcb_visualtype_next(&visualtype_iterator);
            }
        }
    }

    xcb_change_property(c,
                        XCB_PROP_MODE_REPLACE,
                        m_selectionOwner->ownerWindow(),
                        Xcb::atoms->visualAtom,
                        XCB_ATOM_VISUALID,
                        32,
                        1,
                        &trayVisual);
}
