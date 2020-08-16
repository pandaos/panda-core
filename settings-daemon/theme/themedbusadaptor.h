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

    qreal devicePixelRatio() { return m_manager->devicePixelRatio(); }
    void setDevicePixelRatio(qreal ratio) { m_manager->setDevicePixelRatio(ratio); }

Q_SIGNALS:
    void darkModeChanged(bool darkMode);

private:
    ThemeManager *m_manager;
};

#endif
