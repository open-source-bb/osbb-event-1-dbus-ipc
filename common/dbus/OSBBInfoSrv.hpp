#ifndef OSBBINFOSRV_HPP
#define OSBBINFOSRV_HPP


#include <QDateTime>
#include <QObject>

//
// INFO: Execute './generate_dbus_files.bash' after each change of OSBBInfoSrv API!
//

#define OSBBINFOSRV_BUS_TYPE        "session"
#define OSBBINFOSRV_SERVICE_NAME    "pl.osbbinfosrv.service"
#define OSBBINFOSRV_OBJECT_NAME     "/myObject"


class OSBBInfoSrv : public QObject
{
    Q_OBJECT

public:
    OSBBInfoSrv();

signals:
    void upTimeChanged(const uint upTime);
    void lastSyncDTChanged(const QDateTime lastSyncDT);

// shared on the D-Bus
public slots:
    uint getUpTime();

// not shared on the D-Bus
private slots:
    void incrementSrvUpTime();

public:
    void setLastSycnDT(const QDateTime lastSyncdDT);

private:
    uint m_upTimeSec;
    QDateTime m_lastSyncDT;

};


#endif // OSBBINFOSRV_HPP
