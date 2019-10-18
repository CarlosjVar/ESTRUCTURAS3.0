#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include <QTcpServer>
#include "mycliente.h"

class Server:public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject*parent=nullptr);
    void StartServer();
protected:
    void incomingConnection(qintptr handle) override;
public slots:
    void facturaV(qintptr*socket,QByteArray data);
private:
    QThreadPool*pool;
    QList <Mycliente*> sockets;

};

#endif // SERVER_H
