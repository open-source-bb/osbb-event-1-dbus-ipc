#!/bin/bash

DBUS_SRC_NAME=OSBBInfoSrv

help() 
{
    echo "$(basename $0) script possible parameters:"
    echo " -p QT_PATH   - generate $DBUS_SRC_NAME dbus files using given qt path"
    echo "                QT_PATH - location dir of qdbuscpp2xml and qdbusxml2cpp"
    echo " -c           - clean generated files"
    echo " -h           - show this help"
    exit 1
}

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

generate()
{
    echo "Regenerating $DBUS_SRC_NAME d-bus files..."
    echo "Used QT_PATH: $QT_PATH_ARG"
    pushd "$SCRIPT_DIR"
    ${QT_PATH_ARG}/qdbuscpp2xml "${DBUS_SRC_NAME}.hpp"
    ${QT_PATH_ARG}/qdbuscpp2xml "${DBUS_SRC_NAME}.hpp" -o "${DBUS_SRC_NAME}.xml"
    ${QT_PATH_ARG}/qdbusxml2cpp -a "${DBUS_SRC_NAME}Adaptor" "${DBUS_SRC_NAME}.xml"
    ${QT_PATH_ARG}/qdbusxml2cpp -p "${DBUS_SRC_NAME}Interface" "${DBUS_SRC_NAME}.xml"
    popd
    exit 0
}


clean()
{
    echo "Cleaning $DBUS_SRC_NAME d-bus generated files..."
    PATTERN_OF_FILES="\
        Adaptor\
        Interface\
        xml"
    for PATTERN in $PATTERN_OF_FILES; do
        echo $PATTERN
        #find -name "*${PATTERN}*" -exec ls -alh  "{}" \;
        find -name "*${PATTERN}*" -delete
    done
    exit 0
}


OPTIND=1         # Reset in case getopts has been used previously in the shell.
QT_PATH_ARG=""

while getopts "hcp:" opt; do
    case "$opt" in
    h)
        help
        ;;
    c)  clean
        ;;
    p)  QT_PATH_ARG=$OPTARG
        ;;
    esac
done

shift $((OPTIND-1))
[ "${1:-}" = "--" ] && shift


[ "$QT_PATH_ARG" == "" ] && help

generate



