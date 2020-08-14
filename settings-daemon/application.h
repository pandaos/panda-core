#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "audio/audiomanager.h"
#include "theme/thememanager.h"
#include "brightness/brightnessmanager.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv);

    AudioManager *audioManager() { return m_audioManager; }

private:
    AudioManager *m_audioManager;
    ThemeManager *m_themeManager;
    BrightnessManager *m_brightnessManager;
};

#endif // APPLICATION_H
