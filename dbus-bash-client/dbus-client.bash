#!/usr/bin/env bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
DBUS_CONF="$SCRIPT_DIR/dbus-service.conf"

[ ! -r "$DBUS_CONF" ] && { echo "Missing d-bus conf file $DBUS_CONF"; exit 1; }
. "$DBUS_CONF"

echo "D-Bus bus type: $OSBBINFOSRV_BUS_TYPE"
echo "D-Bus service name: $OSBBINFOSRV_SERVICE_NAME"
echo "D-Bus object name: $OSBBINFOSRV_OBJECT_NAME"

# Example dbus-send usage
# command is used to send a message to a D-Bus message bus

FUNC_NAME="$OSBBINFOSRV_IFC.getUpTime"
echo "Call function: $FUNC_NAME"
dbus-send --session --print-reply --dest=$OSBBINFOSRV_SERVICE_NAME $OSBBINFOSRV_OBJECT_NAME $FUNC_NAME

echo ""
echo "Ask D-Bus std service: org.freedesktop.DBus about our service PID"
dbus-send --session --print-reply --dest=org.freedesktop.DBus / org.freedesktop.DBus.GetConnectionUnixProcessID string:$OSBBINFOSRV_SERVICE_NAME

[ $? -ne 0 ] && { echo "Failed to get the service PID"; exit 1; }

PID=$(dbus-send --session --print-reply --dest=org.freedesktop.DBus / org.freedesktop.DBus.GetConnectionUnixProcessID string:$OSBBINFOSRV_SERVICE_NAME |\
    tail -n 1 | \
    awk '{ print $NF }')

echo ""
echo "$(ps aux -q $PID)"

echo
