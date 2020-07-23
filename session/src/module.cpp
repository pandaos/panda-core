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
