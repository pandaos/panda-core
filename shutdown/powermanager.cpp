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