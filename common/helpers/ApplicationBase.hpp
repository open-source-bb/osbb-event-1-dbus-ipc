#ifndef APPLICATIONBASE_H
#define APPLICATIONBASE_H


#include <QCoreApplication>
#include <QCommandLineParser>
#include <QObject>

#include <atomic>


class ApplicationBase : public QObject
{
    Q_OBJECT

public:
    ApplicationBase(QObject *parent = nullptr);
    ~ApplicationBase();

    ApplicationBase(ApplicationBase const&)   = delete;
    void operator=(ApplicationBase const&)  = delete;

    virtual bool parseCmdLnArgs();
    void quitApplication(int exitCode);

public slots:
    virtual void run() = 0;

protected:
    QCoreApplication*   m_coreApp;
    std::atomic<bool>   m_shouldQuit;
    QCommandLineParser  m_cmdLnParser;

};


#endif // APPLICATIONBASE_H
