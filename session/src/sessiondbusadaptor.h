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

#ifndef SESSIONDBUSADAPTOR_H
#define SESSIONDBUSADAPTOR_H

#include <QtDBus>
#include "modulemanager.h"
#include "power/power.h"

class SessionDBusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.panda.session")

public:
    SessionDBusAdaptor(ModuleManager * manager)
      : QDBusAbstractAdaptor(manager),
        m_manager(manager),
        m_power(false)
    {
        connect(m_manager, SIGNAL(moduleStateChanged(QString,bool)), SIGNAL(moduleStateChanged(QString, bool)));
    }

signals:
    void moduleStateChanged(QString moduleName, bool state);

public slots:
    Q_NOREPLY void logout()
    {
        m_manager->logout(true);
    }

    Q_NOREPLY void reboot()
    {
        m_manager->logout(false);
        m_power.reboot();
        QCoreApplication::exit(0);
    }

    Q_NOREPLY void powerOff()
    {
        m_manager->logout(false);
        m_power.shutdown();
        QCoreApplication::exit(0);
    }

    Q_NOREPLY void startModule(const QString& name)
    {
        m_manager->startProcess(name);
    }

    Q_NOREPLY void stopModule(const QString& name)
    {
        m_manager->stopProcess(name);
    }

private:
    ModuleManager * m_manager;
    Power m_power;
};

#endif
