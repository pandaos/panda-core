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

#ifndef IDLEWATCHER_H
#define IDLEWATCHER_H

#include <QObject>

//class ScreenSaver;

class IdleWatcher : public QObject
{
    Q_OBJECT
public:
    explicit IdleWatcher(int secs, QObject *parent = nullptr);
    virtual ~IdleWatcher();

    void reset(int timeout);

private slots:
    void timeoutReached(int identifier);
    void setup();

signals:
    void StatusChanged(uint status);

private:
    int mSecs;

};

#endif // IDLEWATCHER_H
