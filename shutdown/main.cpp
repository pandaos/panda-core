#include <QApplication>
#include <QCommandLineParser>
#include <QDBusInterface>

const static QString s_dbusName = "org.panda.session";
const static QString s_pathName = "/PandaSession";
const static QString s_interfaceName = "org.panda.session";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("Panda Shutdown"));
    parser.addHelpOption();

    QCommandLineOption logoutOption(QStringLiteral("logout"), QCoreApplication::translate("main", "Logout."));
    parser.addOption(logoutOption);

    QCommandLineOption shutdownOption(QStringLiteral("shutdown"), QCoreApplication::translate("main", "Shutdown."));
    parser.addOption(shutdownOption);

    QCommandLineOption rebootOption(QStringLiteral("reboot"), QCoreApplication::translate("main", "Reboot."));
    parser.addOption(rebootOption);

    parser.process(a);

    if (parser.isSet(logoutOption)) {
        QDBusInterface iface(s_dbusName, s_pathName, s_interfaceName, QDBusConnection::sessionBus());
        if (iface.isValid()) {
            iface.call("logout");
        }
        return 0;
    }

    if (parser.isSet(shutdownOption)) {
        QDBusInterface iface(s_dbusName, s_pathName, s_interfaceName, QDBusConnection::sessionBus());
        if (iface.isValid()) {
            iface.call("powerOff");
        }
        return 0;
    }

    if (parser.isSet(rebootOption)) {
        QDBusInterface iface(s_dbusName, s_pathName, s_interfaceName, QDBusConnection::sessionBus());
        if (iface.isValid()) {
            iface.call("reboot");
        }
        return 0;
    }

    return a.exec();
}
