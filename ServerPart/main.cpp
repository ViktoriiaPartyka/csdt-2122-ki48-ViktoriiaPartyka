#include <QCoreApplication>
#include "myserver.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    myServer* server;
    server = new myServer();
    server->startServer();

    return a.exec();
}
