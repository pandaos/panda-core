#ifndef THEMEDBUSADAPTOR_H
#define THEMEDBUSADAPTOR_H

#include <QtDBus>
#include "thememanager.h"

class ThemeDBusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.panda.Theme")

public:
    ThemeDBusAdaptor(ThemeManager *parent) 
      : QDBusAbstractAdaptor(parent),
        m_manager(parent)
    {
        connect(m_manager, &ThemeManager::darkModeChanged, this, &ThemeDBusAdaptor::darkModeChanged);
    };

public slots:
    bool darkMode() { return m_manager->isDarkMode(); }
    void setDarkMode(bool darkMode) { m_manager->setDarkMode(darkMode); }

Q_SIGNALS:
    void darkModeChanged(bool darkMode);

private:
    ThemeManager *m_manager;
};

#endif