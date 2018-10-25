#include "Application.hpp"

#include <QThread>
#include <QDateTime>
#include "CustomLogger.hpp"
#include "OSBBInfoSrv.hpp"

Application::Application(QObject *parent) :
    ApplicationBase(parent), m_dbusServiceIfc(nullptr), m_dbusServiceRegisteredWatcher(nullptr), m_dbusServiceUnregisteredWatcher(nullptr)
{ 
}


Application::~Application()
{
}


bool Application::initializeDBusClient()
{
    if (0 == QString::compare(OSBBINFOSRV_BUS_TYPE, "session", Qt::CaseInsensitive))
        return initializeDBusClientOnSessionBus();
    else
        return initializeDBusClientOnSystemBus();
}


bool Application::initializeDBusClientOnSystemBus()
{
    return false;
}

bool Application::initializeDBusClientOnSessionBus()
{
    //#define OSBBINFOSRV_BUS_TYPE        "session"
    //#define OSBBINFOSRV_SERVICE_NAME    "pl.osbbinfosrv.service"
    //#define OSBBINFOSRV_OBJECT_NAME     "/objectName"

    if (m_dbusServiceIfc != nullptr)
        return false;

    m_dbusServiceIfc = new local::OSBBInfoSrv(OSBBINFOSRV_SERVICE_NAME,
                                                OSBBINFOSRV_OBJECT_NAME,
                                                QDBusConnection::sessionBus(), this);

    m_dbusServiceRegisteredWatcher = new QDBusServiceWatcher(OSBBINFOSRV_SERVICE_NAME,
                                                QDBusConnection::sessionBus(),
                                                QDBusServiceWatcher::WatchForRegistration);

    m_dbusServiceUnregisteredWatcher = new QDBusServiceWatcher(OSBBINFOSRV_SERVICE_NAME,
                                                QDBusConnection::sessionBus(),
                                                QDBusServiceWatcher::WatchForUnregistration);

    QObject::connect(m_dbusServiceRegisteredWatcher, SIGNAL(serviceRegistered(QString)),
                     this, SLOT(onServiceRegistered(QString)));
    QObject::connect(m_dbusServiceUnregisteredWatcher, SIGNAL(serviceUnregistered(QString)),
                     this, SLOT(onServiceUnregistered(QString)));

    QObject::connect(m_dbusServiceIfc, SIGNAL(upTimeChanged(uint)), this, SLOT(onUpTimeChanged(uint)));
    QObject::connect(m_dbusServiceIfc, SIGNAL(lastSyncDTChanged(QDateTime)), this, SLOT(onLastSyncDTChanged(QDateTime)));

    return true;
}


void Application::onServiceRegistered(const QString &name)
{
    LOG(QString("DBus service: %1 registered...").arg(name));
}


void Application::onServiceUnregistered(const QString &name)
{
    LOG(QString("DBus service: %1 unregistered...").arg(name));
}


void Application::onUpTimeChanged(const uint &upTime)
{
    LOG(QString("onUpTimeChanged upTime: %1").arg(upTime));
}


void Application::onLastSyncDTChanged(const QDateTime &ts)
{
    LOG(QString("onLastSyncDTChanged ts: %1").arg(ts.toString()));
}


void Application::onTimerTimeouted()
{
    LOG(QString("onTimerTimeouted ts: %1").arg(QDateTime::currentDateTime().toString()));
}


void Application::run()
{
    parseCmdLnArgs();

    if (!this->initializeDBusClient())
    {
        LOG(QString("Failed to initialize DBus Client (bus: %1)!").arg(OSBBINFOSRV_BUS_TYPE));
        return;
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeouted()));
//    timer->start(1000);
}

