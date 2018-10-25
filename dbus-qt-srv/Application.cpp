#include "Application.hpp"

#include <QThread>
#include "CustomLogger.hpp"


Application::Application(QObject *parent) :
    ApplicationBase(parent)
{ 
    m_oSBBInfoSrvAdaptor = new OSBBInfoSrvAdaptor(&m_oSBBInfoSrv);
}


Application::~Application()
{
    delete m_oSBBInfoSrvAdaptor;
}


bool Application::initializeDbusService()
{
    if (0 == QString::compare(OSBBINFOSRV_BUS_TYPE, "session", Qt::CaseInsensitive))
        return initializeDBusServerOnSessionBus();
    else
        return initializeDBusServerOnSystemBus();
}


bool Application::initializeDBusServerOnSystemBus()
{
    return false;
}


bool Application::initializeDBusServerOnSessionBus()
{
    //#define OSBBINFOSRV_BUS_TYPE        "session"
    //#define OSBBINFOSRV_SERVICE_NAME    "pl.osbbinfosrv.service"
    //#define OSBBINFOSRV_OBJECT_NAME     "/objectName"

    if (!QDBusConnection::sessionBus().isConnected())
    {
        LOG(QString("Can not connect to D-Bus bus: %1!").arg(OSBBINFOSRV_BUS_TYPE));
        return false;
    }

    if (!QDBusConnection::sessionBus().registerService(OSBBINFOSRV_SERVICE_NAME))
    {
        LOG(QString("Can not register service: %1 (or is already registered) at D-Bus bus: %2!")
            .arg(OSBBINFOSRV_SERVICE_NAME).arg(OSBBINFOSRV_BUS_TYPE));
        return false;
    }

    if (!QDBusConnection::sessionBus().registerObject(OSBBINFOSRV_OBJECT_NAME, &m_oSBBInfoSrv))
    {
        LOG(QString("Can not register object: %1 at D-Bus bus: %2!")
            .arg(OSBBINFOSRV_OBJECT_NAME).arg(OSBBINFOSRV_BUS_TYPE));
        return false;
    }

    LOG(QString("D-Bus bus: %1 service: %2 object: '%3' successfully registered")
        .arg(OSBBINFOSRV_BUS_TYPE)
        .arg(OSBBINFOSRV_SERVICE_NAME)
        .arg(OSBBINFOSRV_OBJECT_NAME));

    return true;
}


void Application::run()
{
    parseCmdLnArgs();

    if (!this->initializeDbusService())
    {
        LOG(QString("Failed to initialize DBus Service (bus: %1)!").arg(OSBBINFOSRV_BUS_TYPE));
        return;
    }
}

