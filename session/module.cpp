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

#include "module.h"

#include <QFileInfo>
#include <QDebug>

Module::Module(const XdgDesktopFile& file, QObject* parent) :
    QProcess(parent),
    file(file),
    fileName(QFileInfo(file.fileName()).fileName()),
    mIsTerminating(false)
{
    restartNum = 0;
    QProcess::setProcessChannelMode(QProcess::ForwardedChannels);
    connect(this, SIGNAL(stateChanged(QProcess::ProcessState)), SLOT(updateState(QProcess::ProcessState)));
}

void Module::start()
{
    mIsTerminating = false;
    QStringList args = file.expandExecString();
    QString command = args.takeFirst();
    qDebug() << "Start module: " << command << "args: " << args;
    QProcess::start(command, args);
}

void Module::terminate()
{
    mIsTerminating = true;
    QProcess::terminate();
}

bool Module::isTerminating()
{
    return mIsTerminating;
}

void Module::updateState(QProcess::ProcessState newState)
{
    if (newState != QProcess::Starting)
        emit moduleStateChanged(fileName, (newState == QProcess::Running));
}
