#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QSettings>

class ThemeManager : public QObject
{
    Q_OBJECT

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
