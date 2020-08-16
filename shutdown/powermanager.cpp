/*
 * Copyright (C) 2020 PandaOS Team.
 *
 * Author:     revenmartin <revenmartin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "powermanager.h"
#include <QDBusInterface>
#include <QDebug>

PowerManager::PowerManager(QObject *parent)
    : QObject(parent)
{

}

bool PowerManager::logout()
{
    QDBusInterface dbus("org.panda.session", "/PandaSession", "org.panda.session", QDBusConnection::sessionBus());

    if (!dbus.isValid()) {
        return false;
    }

    const QString method = "logout";
    QDBusMessage msg = dbus.call(method);
    if (!msg.errorName().isEmpty()) {

    }

    // If the method no returns value, we believe that it was successful.
    return msg.arguments().isEmpty() ||
           msg.arguments().constFirst().isNull() ||
           msg.arguments().constFirst().toBool();
}

bool PowerManager::reboot()
{
    return false;
}
