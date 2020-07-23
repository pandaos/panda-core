#include "audiomanager.h"
#include "audiodbusadaptor.h"
#include <QDebug>

AudioManager::AudioManager(QObject *parent)
  : QObject(parent),
    m_engine(new PulseAudioEngine(this)),
    m_defaultSink(nullptr),
    m_defaultSinkIndex(0)
{
    if (m_engine->sinks().count() > 0) {
        m_defaultSink = m_engine->sinks().at(qBound(0, m_defaultSinkIndex, m_engine->sinks().count() - 1));
        connect(m_defaultSink, &AudioDevice::volumeChanged, this, &AudioManager::volumeChanged);
        connect(m_defaultSink, &AudioDevice::muteChanged, this, &AudioManager::muteChanged);

        new AudioDBusAdaptor(this);
        QDBusConnection::sessionBus().registerObject(QStringLiteral("/PandaSettings"), this);
    }
}

int AudioManager::volume()
{
    if (!m_defaultSink)
        return 0;

    return m_defaultSink->volume();
}

bool AudioManager::mute()
{
    if (!m_defaultSink)
        return false;

    return m_defaultSink->mute();
}

void AudioManager::setVolume(int volume)
{
    if (!m_defaultSink)
        return;

    m_defaultSink->setVolume(volume);
}

void AudioManager::toggleMute()
{
    if (!m_defaultSink)
        return;

    m_defaultSink->toggleMute();
}

void AudioManager::setMute(bool state)
{
    if (!m_defaultSink)
        return;

    m_defaultSink->setMute(state);
}