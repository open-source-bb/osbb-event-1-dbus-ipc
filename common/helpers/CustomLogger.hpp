#ifndef CUSTOMLOGGER_HPP
#define CUSTOMLOGGER_HPP

#include <QDebug>

#ifndef APP_NAME
#define APP_NAME "undefined"
#endif

#define LOG(message)        qDebug().noquote() << QString("[%1][%2] %3").arg(APP_NAME).arg(QCoreApplication::applicationPid()).arg(message)

#endif // CUSTOMLOGGER_HPP
