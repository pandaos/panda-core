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

#ifndef BRIGHTNESSDBUSADAPTOR_H
#define BRIGHTNESSDBUSADAPTOR_H

#include <QtDBus>
#include "brightnessmanager.h"

class BrightnessDBusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.panda.Brightness")
    Q_PROPERTY(int maxBrightness READ maxBrightness)
    Q_PROPERTY(int brightness READ brightness WRITE setValue)

public:
    BrightnessDBusAdaptor(BrightnessManager *parent)
      : QDBusAbstractAdaptor(parent),
        m_manager(parent)
    {
        connect(m_manager, &BrightnessManager::brightnessChanged, this, &BrightnessDBusAdaptor::brightnessChanged);
    };

public slots:
    int maxBrightness() { return m_manager->maxBrightness(); }
    int brightness() { return m_manager->brightness(); }

    void setValue(int value) { m_manager->setValue(value); }

Q_SIGNALS:
    void brightnessChanged();

private:
    BrightnessManager *m_manager;
};

#endif
