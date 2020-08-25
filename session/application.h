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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "modulemanager.h"
#include "power/power.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv);

public slots:
    void logout()
    {
        m_moduleManager->logout(true);
    }

    void reboot()
    {
        m_moduleManager->logout(false);
        m_power.reboot();
        QCoreApplication::exit(0);
    }

    void powerOff()
    {
        m_moduleManager->logout(false);
        m_power.shutdown();
        QCoreApplication::exit(0);
    }

    void startModule(const QString& name)
    {
        m_moduleManager->startProcess(name);
    }

    void stopModule(const QString& name)
    {
        m_moduleManager->stopProcess(name);
    }

private:
    int runSync(const QString& program, const QStringList &args, const QStringList &env = {});
    void createConfigDirectory();
    void initLanguage();
    void initScreenScaleFactors();
    void initCursor();
    bool syncDBusEnvironment();

private:
    ModuleManager *m_moduleManager;
    Power m_power;
};

#endif // APPLICATION_H
