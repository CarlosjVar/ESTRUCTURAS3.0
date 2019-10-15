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
        registrarCliente(data);
    }
    else if(data.toStdString().substr(0,2)=="CO")
    {
        if(data.toStdString().substr(2,2)=="PA")
        {
        string send="COPA;";
        string arbol;
        arbol=inordenMandar(supermercado.raiz);
        send.append(arbol);
        this->write(QByteArray::fromStdString(send));
        }
        else if(data.toStdString().substr(2,2)=="PR")
        {
            string datos=data.toStdString();
            char separador[]=";";
            char cstr[datos.size()+1];
            strcpy(cstr,datos.c_str());
            char*token= strtok(cstr,separador);
            token=strtok(nullptr,separador);
            string pasillo=token;
            int pasilloi=std::stoi(pasillo);
            pNodoBinario raiz=supermercado.raiz;
            pNodoBinario pasillop=buscarNodo(raiz,pasilloi);
            if(pasillop!=nullptr)
            {
                string send="COPR;";
                string arbol;
                arbol=inordenMandarP(pasillop->productos);
                send.append(arbol);
                this->write(QByteArray::fromStdString(send));
            }
            else
            {
                QByteArray validacion="VAPA";
                this->write(validacion);
            }

        }
        else if(data.toStdString().substr(2,2)=="MA")
        {
            string datos=data.toStdString();
            char separador[]=";";
            char cstr[datos.size()+1];
            strcpy(cstr,datos.c_str());
            char*token= strtok(cstr,separador);
            token=strtok(nullptr,separador);
            string producto=token;
            int pasillo=stoi(token);
            token=strtok(nullptr,separador);
            int productoi=stoi(token);
            pNodoBinario raiz=supermercado.raiz;
            pNodoBinario pasillon=buscarNodo(raiz,pasillo);
            pNodoBinarioAVL producton=buscarNodoAVL(pasillon->productos,productoi);
            if (producton!=nullptr)
            {
            string send="COMA;";
            string arbol=inordenMandarM(producton->marcas);
            send.append(arbol);
            this->write(QByteArray::fromStdString(send));
            }
            else
            {
                QByteArray validacion="VAPR";
                this->write(validacion);
            }


        }
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
        setCedula(cedulaS);
    }
    else
    {
        socket->write("RGN");
    }
}
void Mycliente::setCedula(int cedula)
{
    this->cedula=cedula;
}
string Mycliente::inordenMandar(pNodoBinario nodo)
{
    if(nodo==NULL){
            return "";
    }else
    {   string aux;
        aux.append(nodo->nombre);
        aux.append(" ");
        aux.append(std::to_string(nodo->valor));
        aux.append("\n");
        aux+=inordenMandar(nodo->Hizq);
        aux+=inordenMandar(nodo->Hder);
        return aux;
    }
}
string Mycliente::inordenMandarP(pNodoBinarioAVL nodo)
{
    if(nodo==NULL){
            return "";
    }else
    {   string aux;
        aux.append(nodo->nombre);
        aux.append(" ");
        aux.append(std::to_string(nodo->valor));
        aux.append("\n");
        aux+=inordenMandarP(nodo->Hizq);
        aux+=inordenMandarP(nodo->Hder);
        return aux;
    }
}
string Mycliente::inordenMandarM(NodePtr nodo)
{
    if(nodo==NULL){
            return "";
    }else
    {   string aux;
        aux.append(nodo->nombre);
        aux.append(" ");
        aux.append(std::to_string(nodo->data));
        aux.append("\n");
        aux+=inordenMandarM(nodo->left);
        aux+=inordenMandarM(nodo->right);
        return aux;
    }
}
