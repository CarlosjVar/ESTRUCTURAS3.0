#include "sockettest.h"

SocketTest::SocketTest(QObject *parent) :
    QObject(parent)
{
}

void SocketTest::Connect()
{
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    socket->connectToHost("localhost",1234);


        if(socket->waitForConnected(3000))
        {
            qDebug() << "Connected!";
        }
        else
        {
            qDebug() << "Not connected!";
        }

}
void SocketTest::connected()
{
    qDebug()<<"Conectado";
}
void SocketTest::disconnected()
{
    qDebug()<<"Desconectao";
}
void SocketTest::WriteByte(QByteArray data)
{
    this->socket->write(data);
}
void SocketTest::readyRead()
{
     QByteArray data=socket->readAll();
     if(data.toStdString().substr(0,2)=="LO")
     {
         if(data.toStdString().substr(2,1)=="S")
         {
           this->conectado=true;
         }
         else
         {
           this->conectado=false;
         }
     }
     else if(data.toStdString().substr(0,2)=="RG")
     {
         if(data.toStdString().substr(2,1)=="Y")
         {
             qDebug()<<"Se ha registrado correctamente";
         }
         else
         {
             qDebug()<<"Esta cédula ya existe en el sistemas";
         }
     }
    else if(data.toStdString().substr(0,2)=="CO")
     {
         if(data.toStdString().substr(2,2)=="PA")
         {
             paInv=true;
             std::string datos=data.toStdString();
             char separador[]=";";
             char cstr[datos.size()+1];
             strcpy(cstr,datos.c_str());
             char*token= strtok(cstr,separador);
             token=strtok(nullptr,separador);
             std::string arbolbin=token;
             std::cout<<arbolbin<<std::endl;
         }
         else if(data.toStdString().substr(2,2)=="PR")
         {
             paInv=true;
             std::string datos=data.toStdString();
             char separador[]=";";
             char cstr[datos.size()+1];
             strcpy(cstr,datos.c_str());
             char*token= strtok(cstr,separador);
             token=strtok(nullptr,separador);
             std::string arbolbin=token;
             std::cout<<arbolbin<<std::endl;
         }
        else if(data.toStdString().substr(2,2)=="MA")
         {
             proInv=true;
             std::string datos=data.toStdString();
             char separador[]=";";
             char cstr[datos.size()+1];
             strcpy(cstr,datos.c_str());
             char*token= strtok(cstr,separador);
             token=strtok(nullptr,separador);
             std::string arbolbin=token;
             std::cout<<arbolbin<<std::endl;
         }
     }
    else if(data.toStdString().substr(0,2)=="VA")
     {
         if(data.toStdString().substr(2,2)=="PA")
         {
             std::cout<<"Pasillo invalido"<<std::endl;
             this->paInv=true;
         }
         else if(data.toStdString().substr(2,2)=="PR")
         {

            std::cout<<"Producto invalido"<<std::endl;
            this->proInv=true;
         }
     }
}
void SocketTest::waitResponse(int q)
{
    this->socket->waitForReadyRead(q);
}
bool SocketTest::getestado()
{
    return this->conectado;
}
bool SocketTest::getpa()
{
    return this->paInv;
}
bool SocketTest::getpro()
{
    return this->proInv;
}
