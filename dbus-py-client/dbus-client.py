import dbus
from dbus_service_conf import *


print "D-Bus bus type: " + OSBBINFOSRV_BUS_TYPE
print "D-Bus service name: " + OSBBINFOSRV_SERVICE_NAME
print "D-Bus object name: " + OSBBINFOSRV_OBJECT_NAME

if OSBBINFOSRV_BUS_TYPE == 'session':
    bus = dbus.SessionBus()
else:
    bus = dbus.SystemBus()

# proxy is a dbus.proxies.ProxyObject
proxy = bus.get_object(OSBBINFOSRV_SERVICE_NAME,
                       OSBBINFOSRV_OBJECT_NAME)

srvIfc = dbus.Interface(proxy, dbus_interface=OSBBINFOSRV_IFC)

serviceUpTime_1 = proxy.getUpTime(dbus_interface=OSBBINFOSRV_IFC)
serviceUpTime_2 = srvIfc.getUpTime()

print("serviceUpTime_1: %s serviceUpTime_2: %s"%(serviceUpTime_1, serviceUpTime_2))
