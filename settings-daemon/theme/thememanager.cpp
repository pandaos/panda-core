#include "thememanager.h"
#include "themedbusadaptor.h"
#include <QDebug>

static const QByteArray s_systemFontName = QByteArrayLiteral("Font");
static const QByteArray s_systemFixedFontName = QByteArrayLiteral("FixedFont");
static const QByteArray s_systemPointFontSize = QByteArrayLiteral("FontSize");
static const QByteArray s_devicePixelRatio = QByteArrayLiteral("PixelRatio");

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

QString ThemeManager::systemFont()
{
    return m_settings->value(s_systemFontName, "Noto Sans").toString();
}

void ThemeManager::setSystemFont(const QString &fontFamily)
{
    m_settings->setValue(s_systemFontName, fontFamily);
}

QString ThemeManager::systemFixedFont()
{
    return m_settings->value(s_systemFixedFontName, "Monospace").toString();
}

void ThemeManager::setSystemFixedFont(const QString &fontFamily)
{
    m_settings->setValue(s_systemFixedFontName, fontFamily);
}

qreal ThemeManager::systemFontPointSize()
{
    return m_settings->value(s_systemPointFontSize, 10.5).toReal();
}

void ThemeManager::setSystemFontPointSize(qreal fontSize)
{
    m_settings->setValue(s_systemPointFontSize, fontSize);
}

qreal ThemeManager::devicePixelRatio()
{
    return m_settings->value(s_devicePixelRatio, 1.0).toReal();
}

void ThemeManager::setDevicePixelRatio(qreal ratio)
{
    m_settings->setValue(s_devicePixelRatio, ratio);
}

void ThemeManager::updateGtkFont()
{

}
