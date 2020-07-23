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
