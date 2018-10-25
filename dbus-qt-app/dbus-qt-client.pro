QT -= gui
QT += core dbus

CONFIG+=debug qml_debug
CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = dbus-qt-srv
TEMPLATE = app

isEmpty(GIT_VERSION) {
    GIT_VERSION = $$system(git describe --long --dirty --tags --always)
}

DEFINES += APP_NAME='\\"$$TARGET\\"'
DEFINES += GIT_VERSION='\\"$$GIT_VERSION\\"'
DEFINES += VERSION='\\"$$GIT_VERSION\\"'

DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH = $$PWD \
    ../common \
    ../common/helpers \
    ../common/dbus

SOURCES += \
    ../common/helpers/ApplicationBase.cpp \
    main.cpp \
    ../common/dbus/OSBBInfoSrv.cpp \
    Application.cpp

HEADERS += \
    ../common/helpers/ApplicationBase.hpp \
    ../common/helpers/CustomLogger.hpp \
    ../common/dbus/OSBBInfoSrv.hpp \
    Application.hpp
