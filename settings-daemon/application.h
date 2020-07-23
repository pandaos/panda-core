#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "audio/audiomanager.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv);

    AudioManager *audioManager() { return m_audioManager; }

private:
    AudioManager *m_audioManager;
};

#endif // APPLICATION_H
