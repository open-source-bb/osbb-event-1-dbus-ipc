#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

#include "ApplicationBase.hpp"
#include "OSBBInfoSrv.hpp"
#include "OSBBInfoSrvAdaptor.h"


class Application : public ApplicationBase
{
    Q_OBJECT

public:
    Application(QObject *parent = nullptr);
    ~Application();

    bool initializeDbusService();
    void run() override;

private:
    bool initializeDBusServerOnSystemBus();
    bool initializeDBusServerOnSessionBus();

private slots:

private:
    OSBBInfoSrv             m_oSBBInfoSrv;
    OSBBInfoSrvAdaptor*     m_oSBBInfoSrvAdaptor;
};


#endif // APPLICATION_H
