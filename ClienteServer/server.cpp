#include "server.h"
Server::Server(QObject*parent):QTcpServer(parent)
{
    pool=new QThreadPool(this);
    pool->setMaxThreadCount(15);
}
void Server::StartServer()
{
    if(listen(QHostAddress::Any,1234))
    {
        qDebug()<<"Servidor conectado";
    }
    else
    {
        qDebug()<<"No se ha conectado el servidor";
    }
}
void Server::incomingConnection(qintptr handle)
{
    Mycliente*cliente=new Mycliente(this);
    cliente->SetSocket(handle);
    this->sockets.append(cliente);
}
void Server::facturaV(qintptr*socket,QByteArray data)
{
    foreach (Mycliente*sok,this->sockets)
    {
       if(sok->socket->socketDescriptor()==*socket)
       {
           sok->write(data);
       }
    }
}
