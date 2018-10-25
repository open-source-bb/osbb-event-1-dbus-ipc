#include "Application.hpp"

//#include <QCommandLineParser>
#include <QThread>

#include "CustomLogger.hpp"


Application::Application(QObject *parent) :
    ApplicationBase(parent)
{ 
//    m_dbusAdaptor = new SynchronizationInfoServerAdaptor(&m_syncInfoServer);
//    SynchronizationInfoServer   m_syncInfoServer;
//    SynchronizationInfoServerAdaptor* m_sisA;
}



Application::~Application()
{
    delete m_dbusAdaptor;
}


bool Application::initializeDBusServer()
{
    return true;
}


void Application::run()
{
//    if (!this->initializeDBusServer())
//    {
//        LOG("Failed to initialize DBus Server!");
//        return;
//    }

    while (m_shouldQuit == false)
    {
        QThread::msleep(1000);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        LOG("cycm Application::run");
    }

    this->quitApplication(0);
}

