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

#include "idlewatcher.h"

// libkf5idletime-dev
// #include <KIdleTime>
#include <QDebug>

IdleWatcher::IdleWatcher(int secs, QObject *parent) :
    QObject(parent),
    mSecs(secs)
{
    // connect(KIdleTime::instance(),
    //         static_cast<void (KIdleTime::*)(int)>(&KIdleTime::timeoutReached),
    //         this,
    //         &IdleWatcher::timeoutReached);

    setup();
}

IdleWatcher::~IdleWatcher()
{
    // KIdleTime::instance()->removeAllIdleTimeouts();
}

void IdleWatcher::setup()
{
    // KIdleTime::instance()->addIdleTimeout(1000 * mSecs);
}

void IdleWatcher::timeoutReached(int identifier)
{
    qDebug() << "Timeout Reached, emit StatusChanged signal!";
    emit StatusChanged(3);
}

void IdleWatcher::reset(int timeout)
{
    qDebug() << "Idle timeout reset to " << timeout;
    // KIdleTime::instance()->removeAllIdleTimeouts();
    mSecs = timeout;
    setup();
}
