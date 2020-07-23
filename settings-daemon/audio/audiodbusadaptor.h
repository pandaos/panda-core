#ifndef AUDIODBUSADAPTOR_H
#define AUDIODBUSADAPTOR_H

#include <QtDBus>
#include "audiomanager.h"

class AudioDBusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.panda.Audio")

public:
    AudioDBusAdaptor(AudioManager *parent) 
      : QDBusAbstractAdaptor(parent),
        m_manager(parent)
    {
        connect(m_manager, &AudioManager::volumeChanged, this, &AudioDBusAdaptor::volumeChanged);
        connect(m_manager, &AudioManager::muteChanged, this, &AudioDBusAdaptor::muteChanged);
    };

Q_SIGNALS:
    void volumeChanged(int volume);
    void muteChanged(bool state);

public slots:
    int volume() { return m_manager->volume(); }
    bool mute() { return m_manager->mute(); }
    void setVolume(int volume) { m_manager->setVolume(volume); }
    void toggleMute() { m_manager->toggleMute(); }
    void setMute(bool state) { m_manager->setMute(state); }

private:
    AudioManager *m_manager;
};

#endif