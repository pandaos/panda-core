#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include "audio/pulseaudioengine.h"
#include "audio/audiodevice.h"

class AudioManager : public QObject
{
    Q_OBJECT

public:
    AudioManager(QObject *parent = nullptr);

    int volume();
    bool mute();
    void setVolume(int volume);
    void toggleMute();
    void setMute(bool state);

signals:
    void volumeChanged(int volume);
    void muteChanged(bool state);

private:
    PulseAudioEngine *m_engine;
    AudioDevice *m_defaultSink;
    int m_defaultSinkIndex;
};

#endif