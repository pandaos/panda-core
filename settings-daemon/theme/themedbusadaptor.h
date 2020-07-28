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

    QString systemFont() { return m_manager->systemFont(); }
    void setSystemFont(const QString &fontFamily) { m_manager->setSystemFont(fontFamily); }

    QString systemFixedFont() { return m_manager->systemFixedFont(); }
    void setSystemFixedFont(const QString &fontFamily) { m_manager->setSystemFixedFont(fontFamily); }

    qreal systemFontPointSize() { return m_manager->systemFontPointSize(); }
    void setSystemFontPointSize(qreal fontSize) { m_manager->setSystemFontPointSize(fontSize); }

Q_SIGNALS:
    void darkModeChanged(bool darkMode);

private:
    ThemeManager *m_manager;
};

#endif
