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
