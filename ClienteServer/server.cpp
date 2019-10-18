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
    if(concalma)
    {
        cliente->write("BC");
    }
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
void Server::blockall()
{
    this->concalma=true;
    foreach(Mycliente*sok,this->sockets)
    {
        sok->write("BC");
    }
}
void Server::unblockall()
{
    this->concalma=false;
    foreach(Mycliente*sok,this->sockets)
    {
        sok->write("UC");
    }
}
