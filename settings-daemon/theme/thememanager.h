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

#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QSettings>

class ThemeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isDarkMode READ isDarkMode WRITE setDarkMode)
    Q_PROPERTY(QString systemFont READ systemFont WRITE setSystemFont)
    Q_PROPERTY(QString systemFixedFont READ systemFixedFont WRITE setSystemFixedFont)
    Q_PROPERTY(qreal systemFontPointSize READ systemFontPointSize WRITE setSystemFontPointSize)
    Q_PROPERTY(qreal devicePixelRatio READ devicePixelRatio WRITE setDevicePixelRatio)

public:
    ThemeManager(QObject *parent = nullptr);

    bool isDarkMode();
    void setDarkMode(bool darkMode);

    QString systemFont();
    void setSystemFont(const QString &fontFamily);

    QString systemFixedFont();
    void setSystemFixedFont(const QString &fontFamily);

    qreal systemFontPointSize();
    void setSystemFontPointSize(qreal fontSize);

    qreal devicePixelRatio();
    void setDevicePixelRatio(qreal ratio);

signals:
    void darkModeChanged(bool darkMode);

private:
    void updateGtkFont();
    void updateGtkDarkTheme();

private:
    QSettings *m_settings;
    bool m_isDarkMode;
};

#endif
