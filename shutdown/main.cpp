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

#include <QApplication>
#include <QCommandLineParser>
#include <QDBusInterface>

const static QString s_dbusName = "org.panda.Session";
const static QString s_pathName = "/Session";
const static QString s_interfaceName = "org.panda.Session";

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
