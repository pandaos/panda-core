#ifndef SESSIONDBUSADAPTOR_H
#define SESSIONDBUSADAPTOR_H

#include <QtDBus>
#include "modulemanager.h"

class SessionDBusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.panda.session")

public:
    SessionDBusAdaptor(ModuleManager * manager)
        : QDBusAbstractAdaptor(manager),
          m_manager(manager)
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
        // m_power.reboot();
        QCoreApplication::exit(0);
    }

    Q_NOREPLY void powerOff()
    {
        m_manager->logout(false);
        // m_power.shutdown();
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
};

#endif
