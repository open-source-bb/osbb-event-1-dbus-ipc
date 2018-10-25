#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

#include "ApplicationBase.hpp"


class Application : public ApplicationBase
{

public:
    Application(QObject *parent = nullptr);
    ~Application();

    bool initializeDBusServer();
    void run() override;

private:

};


#endif // APPLICATION_H
