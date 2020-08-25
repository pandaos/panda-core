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

#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "module.h"
#include <QString>
#include <QAbstractNativeEventFilter>
#include <QObject>
#include <QEventLoop>
#include <QProcess>
#include <QVector>
#include <QMap>
#include <QTimer>

class XdgDesktopFile;
class IdleWatcher;

typedef QMap<QString, Module*> ModulesMap;
typedef QMapIterator<QString, Module*> ModulesMapIterator;

class ModuleManager : public QObject
{
    Q_OBJECT

public:
    ModuleManager(QObject* parent = nullptr);
    ~ModuleManager() override;

    void startup();
    void startProcess(const QString &name);
    void startProcess(const XdgDesktopFile &file);
    void stopProcess(const QString &name);

public slots:
    void logout(bool doExit);

private:
    void startWm();
    void startSettingsDaemon();
    void startAutostartApps();

private slots:
    void restartModules(int exitCode, QProcess::ExitStatus exitStatus);

private:
    QProcess *m_wmProcess;
    QEventLoop *m_waitLoop;

    ModulesMap mNameMap;
};

#endif
