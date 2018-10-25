#include "ApplicationBase.hpp"

#include <QCommandLineParser>
#include <QThread>

#include "CustomLogger.hpp"


ApplicationBase::ApplicationBase(QObject *parent) :
    QObject(parent), m_shouldQuit(false), m_cmdLnParser()
{
    LOG(QString("Application %1 version %2 started...").arg(APP_NAME).arg(GIT_VERSION));

    m_coreApp = QCoreApplication::instance();
}


bool ApplicationBase::parseCmdLnArgs()
{
    // parse program parameters
    const auto helpOption = m_cmdLnParser.addHelpOption();
    QCommandLineOption verboseOption("v", "Show verbose output");
    m_cmdLnParser.addOption(verboseOption);

    if (!m_cmdLnParser.parse(m_coreApp->arguments()))
    {
        LOG(QString("Application %1 called with wrong parameters!").arg(APP_NAME));
        m_cmdLnParser.showHelp(1);
        // return false;
    }

    if (m_cmdLnParser.isSet(helpOption))
    {
        m_cmdLnParser.showHelp(1);
        // return false;
    }

    return true;
}


ApplicationBase::~ApplicationBase()
{
}


void ApplicationBase::quitApplication(int exitCode=EXIT_SUCCESS)
{
    LOG(QString("ApplicationBase::quitApplication with exitCode: %1").arg(exitCode));
//    ::exit(exitCode);
}
