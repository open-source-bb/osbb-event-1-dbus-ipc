#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

#include "ApplicationBase.hpp"
#include "OSBBInfoSrvInterface.h"


class Application : public ApplicationBase
{
    Q_OBJECT

public:
    Application(QObject *parent = nullptr);
    ~Application();

    bool initializeDBusClient();
    void run() override;

private:
    bool initializeDBusClientOnSessionBus();
    bool initializeDBusClientOnSystemBus();
    bool parseCmdLnArgs() override;

private slots:
    void onServiceRegistered(const QString &);
    void onServiceUnregistered(const QString &);
    void onUpTimeChanged(const uint &);
    void onLastSyncDTChanged(const QDateTime &);

    void processAsyncFinished(QDBusPendingCallWatcher *call);

    void onTimerTimeouted();

private:
    local::OSBBInfoSrv* m_dbusServiceIfc;
    QDBusServiceWatcher* m_dbusServiceRegisteredWatcher;
    QDBusServiceWatcher* m_dbusServiceUnregisteredWatcher;
};


#endif // APPLICATION_H
