#ifndef BRIGHTNESSDBUSADAPTOR_H
#define BRIGHTNESSDBUSADAPTOR_H

#include <QtDBus>
#include "brightnessmanager.h"

class BrightnessDBusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.panda.Brightness")

public:
    BrightnessDBusAdaptor(BrightnessManager *parent)
      : QDBusAbstractAdaptor(parent),
        m_manager(parent)
    {
        connect(m_manager, &BrightnessManager::brightnessChanged, this, &BrightnessDBusAdaptor::brightnessChanged);
    };

public slots:
    int maxBrightness() { return m_manager->maxBrightness(); }
    int brightness() { return m_manager->brightness(); }

    void setValue(int value) { m_manager->setValue(value); }

Q_SIGNALS:
    void brightnessChanged();

private:
    BrightnessManager *m_manager;
};

#endif
