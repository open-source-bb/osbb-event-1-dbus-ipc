#include <QCoreApplication>

#include <QFileInfo>
#include <QTimer>


#include "Application.hpp"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Application application;

    // run the application task from the app event loop
    QTimer::singleShot(10, &application, SLOT(run()));

    return app.exec();
}
