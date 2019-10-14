#include <QCoreApplication>
#include "sockettest.h"
#include "thread.h"
SocketTest socket;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    socket.Connect();
    Thread hilo;
    hilo.start();
    return a.exec();
}
