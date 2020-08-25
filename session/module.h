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

#ifndef MODULE_H
#define MODULE_H

#include <QProcess>
#include "xdgautostart.h"
#include "xdgdesktopfile.h"
#include "xdgdirs.h"

class Module : public QProcess
{
    Q_OBJECT
public:
    Module(const XdgDesktopFile& file, QObject *parent = nullptr);
    void start();
    void terminate();
    bool isTerminating();

    int restartNum;

    const XdgDesktopFile file;
    const QString fileName;

signals:
    void moduleStateChanged(QString name, bool state);

private slots:
    void updateState(QProcess::ProcessState newState);

private:
    bool mIsTerminating;
};

#endif // MODULE_H
