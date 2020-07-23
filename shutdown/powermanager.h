#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <QObject>

class PowerManager : public QObject
{
    Q_OBJECT

public:
    explicit PowerManager(QObject *parent = nullptr);

    bool logout();
    bool reboot();
};

#endif
