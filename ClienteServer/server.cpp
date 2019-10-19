#include "server.h"
Server::Server(QObject*parent):QTcpServer(parent)
{
    pool=new QThreadPool(this);
    pool->setMaxThreadCount(15);
}
void Server::StartServer()
//Inicia el servidor
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
//Manejo de recepción de conexiones
{
    Mycliente*cliente=new Mycliente(this);
    cliente->SetSocket(handle);
    this->sockets.append(cliente);
    if(concalma)
        //Si el servidor está en mantenimiento los nuevos clientes también se verán bloqueados
    {
        cliente->write("BC");
    }
}
void Server::facturaV(qintptr*socket,QByteArray data)
//Envio de datos de factura
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
//Envia señal de bloqueo a todos los sockets
{
    this->concalma=true;
    foreach(Mycliente*sok,this->sockets)
    {
        sok->write("BC");
    }
}
void Server::unblockall()
//Envia señal de desbloqueo a todos los sockets
{
    this->concalma=false;
    foreach(Mycliente*sok,this->sockets)
    {
        sok->write("UC");
    }
}
