#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "modulemanager.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv);

private:
    int runSync(const QString& program, const QStringList &args, const QStringList &env = {});
    void createConfigDirectory();
    void initLanguage();
    void initScreenScaleFactors();
    void initCursor();
    bool syncDBusEnvironment();

private:
    ModuleManager *m_moduleManager;
};

#endif // APPLICATION_H
