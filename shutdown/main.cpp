#include <QApplication>
#include <QCommandLineParser>
#include "powermanager.h"

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
        PowerManager power;
        power.logout();
        return 0;
    }

    if (parser.isSet(shutdownOption)) {
        return 0;
    }

    if (parser.isSet(rebootOption)) {
        return 0;
    }

    return a.exec();
}
