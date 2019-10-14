#include "mycliente.h"

Mycliente::Mycliente(QObject*parent):QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(15);
}
void Mycliente::SetSocket(qintptr Desc)
{
    socket=new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    socket->setSocketDescriptor(Desc);
    qDebug()<<"Cliente conectado";
}
void Mycliente::connected()
{
    qDebug()<<"Cliente conectado ev";
}
void Mycliente::disconnected()
{
    qDebug()<<"Cliente no conectado";
}
void Mycliente::readyRead()
{
    QByteArray data=socket->readAll();
    if(data.toStdString().substr(0,2)=="LO")
    {
        conectadoE(data);
    }
    else if(data.toStdString().substr(0,2)=="RE")
    {
        cout<<"hola"<<endl;
        registrarCliente(data);

    }
}

void Mycliente::write(QByteArray data)
{
        // Must always be called on thread 1
        this->socket->write(data);
}
void Mycliente::conectadoE(QByteArray data)
{
std::string cedula=data.toStdString().substr(2,7);
Pagina*cliente=new Pagina(5);
int k;
cliente=clientes.buscar(std::stoi(cedula),k);
if (cliente!=nullptr)
{
    socket->write("LOS");
}
else
{
    socket->write("LON");
}
}
void Mycliente::registrarCliente(QByteArray data)
{
    string datos=data.toStdString();
    char separador[]=";";
    char cstr[datos.size()+1];
    strcpy(cstr,datos.c_str());
    char*token= strtok(cstr,separador);
    string cedula=token;
    token=strtok(nullptr,separador);
    string nombre=token;
    token=strtok(nullptr,separador);
    string ciudad=token;
    token=strtok(nullptr,separador);
    string numero=token;
    token=strtok(nullptr,separador);
    string correo=token;
    cout<<cedula<<endl;
    cedula=cedula.substr(2,7);
    int cedulaS = std::stoi(cedula);
    int n;
    Pagina* aux = clientes.buscar(cedulaS,n);
    if (aux == NULL){
        clientes.insertar(cedulaS,nombre,numero,ciudad,correo);
        socket->write("RGY");
    }
    else
    {
        socket->write("RGN");
    }




}
