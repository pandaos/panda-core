#ifndef DBUSADAPTOR_H
#define DBUSADAPTOR_H

#include <QtDBus>
#include "application.h"

class DBusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.panda.settings")

public:
    DBusAdaptor(Application *app) : QDBusAbstractAdaptor(app) {

    };
};

#endif