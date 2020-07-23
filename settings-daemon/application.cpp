#include "application.h"
#include "dbusadaptor.h"
#include <QStandardPaths>
#include <QProcess>
#include <QTimer>
#include <QFile>
#include <QDebug>
#include <QDir>

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    new DBusAdaptor(this);
    // connect to D-Bus and register as an object:
    QDBusConnection::sessionBus().registerService(QStringLiteral("org.panda.settings"));
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/PandaSettings"), this);
}
