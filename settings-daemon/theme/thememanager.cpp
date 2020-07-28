#include "thememanager.h"
#include "themedbusadaptor.h"
#include <QDebug>

ThemeManager::ThemeManager(QObject *parent)
  : QObject(parent),
    m_settings(new QSettings(QStringLiteral("panda"), QStringLiteral("theme")))
{
    // init dbus
    new ThemeDBusAdaptor(this);
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/Theme"), this);

    // init value
    m_isDarkMode = m_settings->value("DarkMode", false).toBool();
}

bool ThemeManager::isDarkMode()
{
    return m_isDarkMode;
}

void ThemeManager::setDarkMode(bool darkMode)
{
    if (darkMode == m_isDarkMode)
        return;

    m_isDarkMode = darkMode;
    m_settings->setValue("DarkMode", darkMode);
    emit darkModeChanged(m_isDarkMode);
} 