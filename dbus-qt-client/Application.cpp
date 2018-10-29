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


bool Application::parseCmdLnArgs()
{
    bool result = false;

    m_cmdLnParser.setApplicationDescription(QString("Client attaches to service: %1").arg(OSBBINFOSRV_SERVICE_NAME));

    m_cmdLnParser.addOption(QCommandLineOption("callGetUpTime", "sync call dbus rpc getUpTime"));
    m_cmdLnParser.addOption(QCommandLineOption("callProcess", "sync call dbus rpc process"));
    m_cmdLnParser.addOption(QCommandLineOption("callProcessAsync", "async call dbus rpc process"));

    result = ApplicationBase::parseCmdLnArgs();

    return result;
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


void Application::processAsyncFinished(QDBusPendingCallWatcher *call)
{
    QDBusPendingReply<double> reply = *call;
    if (reply.isError())
    {
        LOG(QString("processAsyncFinished result with error"));
    } else {
        auto result = reply.argumentAt<0>();
        LOG(QString("processAsyncFinished result: %1").arg(result));
    }
    call->deleteLater();
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

    if (m_cmdLnParser.isSet("callGetUpTime"))
    {
        LOG(QString("callGetUpTime..."));
        uint upTime = m_dbusServiceIfc->getUpTime();
        LOG(QString("result: %1").arg(upTime));
        quitApplication(0);
    }

    if (m_cmdLnParser.isSet("callProcess"))
    {
        LOG(QString("callProcess..."));
        double time = m_dbusServiceIfc->process();
        LOG(QString("result: %1").arg(time));
        //quitApplication(0);
    }

    if (m_cmdLnParser.isSet("callProcessAsync"))
    {
        LOG(QString("callProcessAsync..."));

        QDBusPendingCall async = m_dbusServiceIfc->asyncCall("process");
        QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(async, this);
        QObject::connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)), this, SLOT(processAsyncFinished(QDBusPendingCallWatcher*)));

        QTimer *timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeouted()));
        timer->start(1000);
    }

}

