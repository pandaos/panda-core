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

signals:
    void darkModeChanged(bool darkMode);

private:
    QSettings *m_settings;
    bool m_isDarkMode;
};

#endif