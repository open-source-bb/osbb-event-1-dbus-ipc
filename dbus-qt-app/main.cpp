#include <QCoreApplication>

#include <QFileInfo>
#include <QTimer>
#include "CustomLogger.hpp"

#include "Application.hpp"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

//    cycm
//    QCoreApplication::setApplicationName(QFileInfo(QCoreApplication::applicationFilePath()).fileName());
//    QCoreApplication::setApplicationVersion(VERSION);


    Application application;

    // run the application task from the app event loop
    QTimer::singleShot(10, &application, SLOT(run()));

    return app.exec();

}
