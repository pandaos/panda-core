#include "modulemanager.h"

#include <QCoreApplication>
#include "xdgautostart.h"
#include "xdgdesktopfile.h"
#include "xdgdirs.h"
#include <QFileInfo>
#include <QStringList>
#include <QSettings>
#include <QStandardPaths>
#include <QDebug>
#include <QTimer>

ModuleManager::ModuleManager(QObject* parent)
    : QObject(parent),
      m_wmProcess(new QProcess(this))
{
}

ModuleManager::~ModuleManager()
{

}

void ModuleManager::startup()
{
    startWm();
    startSettingsDaemon();
    startAutostartApps();

    QProcess *deskProc = new QProcess(this);
    QProcess *taskProc = new QProcess(this);
    QProcess *topbarProc = new QProcess(this);
    QProcess *launcherProc = new QProcess(this);

    deskProc->start("/usr/bin/panda-files", QStringList() << "--desktop");
    taskProc->start("/usr/bin/panda-dock");
    topbarProc->start("/usr/bin/panda-topbar");
    launcherProc->start("/usr/bin/panda-launcher");
}

void ModuleManager::startProcess(const QString &name)
{
    if (!mNameMap.contains(name)) {
        const auto files = XdgAutoStart::desktopFileList(false);
        for (const XdgDesktopFile& file : files)
        {
            if (QFileInfo(file.fileName()).fileName() == name)
            {
                startProcess(file);
                return;
            }
        }
    }
}

void ModuleManager::startProcess(const XdgDesktopFile &file)
{
//    if (!file.value(QL1S("X-LXQt-Module"), false).toBool())
//    {
//        file.startDetached();
//        return;
//    }
    QStringList args = file.expandExecString();
    if (args.isEmpty())
    {
        // qCWarning(SESSION) << "Wrong desktop file" << file.fileName();
        return;
    }
    Module *proc = new Module(file, this);
    // connect(proc, SIGNAL(moduleStateChanged(QString,bool)), this, SIGNAL(moduleStateChanged(QString,bool)));
    proc->start();

    QString name = QFileInfo(file.fileName()).fileName();
    mNameMap[name] = proc;

    connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(restartModules(int, QProcess::ExitStatus)));
}

void ModuleManager::stopProcess(const QString &name)
{
    if (mNameMap.contains(name))
        mNameMap[name]->terminate();
}

void ModuleManager::logout(bool doExit)
{
    ModulesMapIterator i(mNameMap);
    while (i.hasNext()) {
        i.next();
        Module *p = i.value();
        p->terminate();
    }
    i.toFront();

    while (i.hasNext()) {
        i.next();
        Module *p = i.value();
        if (p->state() != QProcess::NotRunning && !p->waitForFinished(2000)) {
            p->kill();
        }
    }

    m_wmProcess->terminate();
    if (m_wmProcess->state() != QProcess::NotRunning && !m_wmProcess->waitForFinished(2000)) {
        m_wmProcess->kill();
    }

    if (doExit) {
        QCoreApplication::exit(0);
    }
}

void ModuleManager::startWm()
{
    m_wmProcess->start("kwin_x11");

    // Wait until the WM loads
    QEventLoop waitLoop;
    m_waitLoop = &waitLoop;
    // add a timeout to avoid infinite blocking if a WM fail to execute.
    QTimer::singleShot(2000, &waitLoop, SLOT(quit()));
    waitLoop.exec();
    m_waitLoop = nullptr;
}

void ModuleManager::startSettingsDaemon()
{
    QProcess *process = new QProcess(this);
    process->start("/usr/bin/panda-settings-daemon");
}

void ModuleManager::startAutostartApps()
{
    // XDG autostart
    const XdgDesktopFileList fileList = XdgAutoStart::desktopFileList();
    QList<const XdgDesktopFile*> trayApps;
    for (XdgDesktopFileList::const_iterator i = fileList.constBegin(); i != fileList.constEnd(); ++i)
    {
        if (i->value(QSL("X-LXQt-Need-Tray"), false).toBool())
            trayApps.append(&(*i));
        else
        {
            startProcess(*i);
            qDebug() << "start" << i->fileName();
        }
    }

    if (!trayApps.isEmpty())
    {
        for (const XdgDesktopFile* const f : qAsConst(trayApps))
        {
            qDebug() << "start tray app" << f->fileName();
            startProcess(*f);
        }
    }
}

void ModuleManager::restartModules(int exitCode, QProcess::ExitStatus exitStatus)
{
    Module* proc = qobject_cast<Module*>(sender());
    if(proc->restartNum > 10){
        mNameMap.remove(proc->fileName);
        disconnect(proc, SIGNAL(finished(int, QProcess::ExitStatus)), nullptr, nullptr);
        proc->deleteLater();
        return;
    }
    if (nullptr == proc) {
        qWarning() << "Got an invalid (null) module to restart, Ignoring it";
        return;
    }

    if (!proc->isTerminating())
    {
        QString procName = proc->file.name();
        switch (exitStatus)
        {
            case QProcess::NormalExit:
                qDebug() << "Process" << procName << "(" << proc << ") exited correctly.";
                break;
            case QProcess::CrashExit:
            {
                qDebug() << "Process" << procName << "(" << proc << ") has to be restarted";
                proc->start();
                proc->restartNum++;
                return;
            }
        }
    }

    mNameMap.remove(proc->fileName);
    proc->deleteLater();
}

