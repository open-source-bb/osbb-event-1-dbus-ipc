/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -p OSBBInfoSrvInterface OSBBInfoSrv.xml
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef OSBBINFOSRVINTERFACE_H
#define OSBBINFOSRVINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface local.OSBBInfoSrv
 */
class LocalOSBBInfoSrvInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "local.OSBBInfoSrv"; }

public:
    LocalOSBBInfoSrvInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~LocalOSBBInfoSrvInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<uint> getUpTime()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("getUpTime"), argumentList);
    }

    inline QDBusPendingReply<double> process()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("process"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void lastSyncDTChanged(const QDateTime &lastSyncDT);
    void upTimeChanged(uint upTime);
};

namespace local {
  typedef ::LocalOSBBInfoSrvInterface OSBBInfoSrv;
}
#endif
