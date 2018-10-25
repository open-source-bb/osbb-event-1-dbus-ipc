#include "OSBBInfoSrv.hpp"

#include <QTimer>


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


void OSBBInfoSrv::setLastSycnDT(const QDateTime lastSyncDT)
{
    m_lastSyncDT = lastSyncDT;
    emit lastSyncDTChanged(lastSyncDT);
}







