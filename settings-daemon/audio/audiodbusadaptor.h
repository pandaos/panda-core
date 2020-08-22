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

#ifndef AUDIODBUSADAPTOR_H
#define AUDIODBUSADAPTOR_H

#include <QtDBus>
#include "audiomanager.h"

class AudioDBusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.panda.Audio")
    Q_PROPERTY(int volume READ volume WRITE setVolume)
    Q_PROPERTY(bool mute READ mute WRITE setMute)

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
