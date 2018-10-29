#include "OSBBInfoSrv.hpp"

#include <QTimer>
#include <QThread>

OSBBInfoSrv::OSBBInfoSrv():
    m_upTimeSec(0)
{
    m_lastSyncDT.setTime_t(0);

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(incrementSrvUpTime()));
    timer->start(1000);
}


void OSBBInfoSrv::incrementSrvUpTime()
{
    m_upTimeSec++;
    emit upTimeChanged(m_upTimeSec);
}


uint OSBBInfoSrv::getUpTime()
{
    return m_upTimeSec;
}


double OSBBInfoSrv::process()
{
    QTime timer;
    timer.start();
    QThread::sleep(10);
    double time = timer.elapsed()/1000.0;
    return time;
}


void OSBBInfoSrv::setLastSycnDT(const QDateTime lastSyncDT)
{
    m_lastSyncDT = lastSyncDT;
    emit lastSyncDTChanged(lastSyncDT);
}







