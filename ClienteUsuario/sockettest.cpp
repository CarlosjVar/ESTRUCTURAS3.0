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
     else if(data.toStdString().substr(0,2)=="BC")
     {
         this->concalma=true;
     }
     else if(data.toStdString().substr(0,2)=="UC")
     {
         this->concalma=false;
     }
     else if(data.toStdString().substr(0,2)=="FA")
     {
         std::cout<<data.toStdString().substr(2,data.toStdString().length()-2);
         this->cola=false;
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
             paInv=false;
             std::string datos=data.toStdString();
             char separador[]=";";
             char cstr[datos.size()+1];
             strcpy(cstr,datos.c_str());
             char*token= strtok(cstr,separador);
             token=strtok(nullptr,separador);
             std::string arbolbin=token;
             std::cout<<arbolbin<<std::endl;
         }
         else if(data.toStdString().substr(2,2)=="CI")
         {
             std::cout<<data.toStdString().substr(4,data.toStdString().length()-4)<<std::endl;
         }
         else if(data.toStdString().substr(2,2)=="CC")
         {
             std::string canasta=data.toStdString().substr(4,data.toStdString().length()-4);
             if(canasta=="1")
             {
                 std::cout<<"Pertenece a la canasta"<<std::endl;
             }
             else
             {
                 std::cout<<"No pertenece a la canasta"<<std::endl;
             }
         }
         else if(data.toStdString().substr(2,2)=="PR")
         {
             paInv=false;
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
             proInv=false;
             std::string datos=data.toStdString();
             char separador[]=";";
             char cstr[datos.size()+1];
             strcpy(cstr,datos.c_str());
             char*token= strtok(cstr,separador);
             token=strtok(nullptr,separador);
             std::string arbolbin=token;
             std::cout<<arbolbin<<std::endl;

         }
       else if(data.toStdString().substr(2,2)=="CO")
         {
             marInv=false;
             std::string datos=data.toStdString();
             char separador[]=";";
             char cstr[datos.size()+1];
             strcpy(cstr,datos.c_str());
             char*token= strtok(cstr,separador);
             token=strtok(nullptr,separador);
             std::cout<<"Tenemos en stock esta cantidad de productos: "<<std::endl;
             std::cout<<token<<std::endl;

         }
       else if(data.toStdString().substr(2,2)=="CA")
         {
             std::cout<<"El precio es de: "<<data.toStdString().substr(4,data.toStdString().length()-4)<<std::endl;
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
         else if(data.toStdString().substr(2,2)=="MA")
         {
           std::cout<<"Marca invalido"<<std::endl;
           this->marInv=true;
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
bool SocketTest::getmar()
{
    return this->marInv;
}
void SocketTest::setCed(std::string ced)
{
    this->cedula=stoi(ced);
}
int SocketTest::getCed()
{
    return this->cedula;
}
