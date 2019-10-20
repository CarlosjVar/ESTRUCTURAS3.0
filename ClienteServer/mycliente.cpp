#include "mycliente.h"

Mycliente::Mycliente(QObject*parent):QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(15);
}
void Mycliente::SetSocket(qintptr Desc)
// Configura el socket y conecta señales
{
    socket=new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));


    socket->setSocketDescriptor(Desc);
}
void Mycliente::connected()
//Accion a realizar con cliente conectado
{
    qDebug()<<"Cliente conectado ev";
}
void Mycliente::disconnected()
//Accion a realizar con cliente desconectado
{
    qDebug()<<"Cliente no conectado";
}
void Mycliente::readyRead()
//Se llevan a cabo las peticiones de los clientes
{
    QByteArray data=socket->readAll();
    if(data.toStdString().substr(0,2)=="LO")
        //Loggea un cliente
    {
        conectadoE(data);
    }
    else if(data.toStdString().substr(0,2)=="RE")
        //Registra un cliente
    {
        registrarCliente(data);
    }
    else if(data.toStdString().substr(0,2)=="AD")
        //Agrega un cliente a la cola de clientes
    {
        string ced=data.toStdString().substr(2,data.toStdString().length()-2);
        clienodo aux=clienteslog.primero;
        while(aux!=nullptr)
        {
            if(aux->cedula==ced)
            {
                colaclientes.insertarFinal(aux->cedula,aux->nombre,aux->telefono,aux->correo,aux->carrito,aux->facturas,aux->socket);

            }
                aux=aux->siguiente;
        }
    }
    else if(data.toStdString().substr(0,2)=="CO")
        //Comandos de compra
    {
        if(data.toStdString().substr(2,2)=="PA")
            //Devuelve pasillos
        {
        string send="COPA;";
        string arbol;
        arbol=inordenMandar(supermercado.raiz);
        send.append(arbol);
        this->write(QByteArray::fromStdString(send));
        }
        else if(data.toStdString().substr(2,2)=="PR")
            //Devuelve productos
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
                pasillop->cantidadVisitas+=1;
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
            //Devuelve marcas
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
        else if(data.toStdString().substr(2,2)=="CC")
            //Consulta de canasta
        {
            string datos=data.toStdString();
            char separador[]=";";
            char cstr[datos.size()+1];
            strcpy(cstr,datos.c_str());
            char*token= strtok(cstr,separador);
            token=strtok(nullptr,separador);
            int pasillo=stoi(token);
            token=strtok(nullptr,separador);
            int productoi=stoi(token);
            token=strtok(nullptr,separador);
            int marcaI=stoi(token);
            pNodoBinario raiz=supermercado.raiz;
            pNodoBinario pasillon=buscarNodo(raiz,pasillo);
            pNodoBinarioAVL producton=buscarNodoAVL(pasillon->productos,productoi);
            RBTree rojo=RBTree(producton->marcas);
            NodePtr marca=rojo.searchTree(marcaI);
            if(marca!=nullptr)
            {
                string send="COCC";
                string buscar=std::to_string(pasillon->valor)+std::to_string(producton->valor)+std::to_string(marca->data);
                nodoAA*inv=inventario.buscarNodoAA(inventario.raiz,stoi(buscar));
                send.append(std::to_string(inv->canastaB));
                this->write(QByteArray::fromStdString(send));
            }
            else
            {
                QByteArray validacion="VAMA";
                this->write(validacion);
            }
        }
        else if(data.toStdString().substr(2,2)=="CI")
            //Consulta de impuesto
        {
            string datos=data.toStdString();
            char separador[]=";";
            char cstr[datos.size()+1];
            strcpy(cstr,datos.c_str());
            char*token= strtok(cstr,separador);
            token=strtok(nullptr,separador);
            int pasillo=stoi(token);
            token=strtok(nullptr,separador);
            int productoi=stoi(token);
            token=strtok(nullptr,separador);
            int marcaI=stoi(token);
            pNodoBinario raiz=supermercado.raiz;
            pNodoBinario pasillon=buscarNodo(raiz,pasillo);
            pNodoBinarioAVL producton=buscarNodoAVL(pasillon->productos,productoi);
            RBTree rojo=RBTree(producton->marcas);
            NodePtr marca=rojo.searchTree(marcaI);
            if(marca!=nullptr)
            {
                string send="COCI";
                string buscar=std::to_string(pasillon->valor)+std::to_string(producton->valor)+std::to_string(marca->data);
                nodoAA*inv=inventario.buscarNodoAA(inventario.raiz,stoi(buscar));
                if(inv->canastaB==0)
                {
                    send.append("El impuesto es de 1%");
                }
                else
                {
                    send.append("El impuesto es de: ");
                    send.append(std::to_string(inv->impuesto));
                    send.append("%");
                }
                this->write(QByteArray::fromStdString(send));
            }
            else
            {
                QByteArray validacion="VAMA";
                this->write(validacion);
            }
        }
        else if(data.toStdString().substr(2,2)=="CN")
            //Consulta de precio
        {
            string datos=data.toStdString();
            char separador[]=";";
            char cstr[datos.size()+1];
            strcpy(cstr,datos.c_str());
            char*token= strtok(cstr,separador);
            token=strtok(nullptr,separador);
            int pasillo=stoi(token);
            token=strtok(nullptr,separador);
            int productoi=stoi(token);
            token=strtok(nullptr,separador);
            int marcaI=stoi(token);
            pNodoBinario raiz=supermercado.raiz;
            pNodoBinario pasillon=buscarNodo(raiz,pasillo);
            pNodoBinarioAVL producton=buscarNodoAVL(pasillon->productos,productoi);
            RBTree rojo=RBTree(producton->marcas);
            NodePtr marca=rojo.searchTree(marcaI);
            if(marca!=nullptr)
            {
                string send="COCA";
                send.append(std::to_string(marca->precio));
                this->write(QByteArray::fromStdString(send));
            }
            else
            {
                QByteArray validacion="VAMA";
                this->write(validacion);
            }
        }
        else if(data.toStdString().substr(2,2)=="CO")
            //Selección de marca para devolver cantidad
        {
            string datos=data.toStdString();
            char separador[]=";";
            char cstr[datos.size()+1];
            strcpy(cstr,datos.c_str());
            char*token= strtok(cstr,separador);
            token=strtok(nullptr,separador);
            int pasillo=stoi(token);
            token=strtok(nullptr,separador);
            int productoi=stoi(token);
            token=strtok(nullptr,separador);
            int marcaI=stoi(token);
            pNodoBinario raiz=supermercado.raiz;
            pNodoBinario pasillon=buscarNodo(raiz,pasillo);
            pNodoBinarioAVL producton=buscarNodoAVL(pasillon->productos,productoi);
            RBTree rojo=RBTree(producton->marcas);
            NodePtr marca=rojo.searchTree(marcaI);
            if(marca!=nullptr)
            {
                string send="COCO;";
                string arbol=std::to_string(marca->cantidadGondola);
                send.append(arbol);
                this->write(QByteArray::fromStdString(send));
            }
            else
            {
                QByteArray validacion="VAMA";
                this->write(validacion);
            }
        }
        else if(data.toStdString().substr(2,2)=="AG")
            //Agrega la cantidad al carrito
        {
            string datos=data.toStdString();
            char separador[]=";";
            char cstr[datos.size()+1];
            strcpy(cstr,datos.c_str());
            char*token= strtok(cstr,separador);
            token=strtok(nullptr,separador);
            int pasillo=stoi(token);
            token=strtok(nullptr,separador);
            int productoi=stoi(token);
            token=strtok(nullptr,separador);
            int marcaI=stoi(token);
            pNodoBinario raiz=supermercado.raiz;
            pNodoBinario pasillon=buscarNodo(raiz,pasillo);
            pNodoBinarioAVL producton=buscarNodoAVL(pasillon->productos,productoi);
            RBTree rojo=RBTree(producton->marcas);
            NodePtr marca=rojo.searchTree(marcaI);
            token=strtok(nullptr,separador);
            int cantidad=stoi(token);
            token=strtok(nullptr,separador);
            int cedula=stoi(token);
            if(cantidad>marca->cantidadGondola)
            {
                cantidad=marca->cantidadGondola;
                marca->cantidadGondola=0;
            }
            else
            {
                marca->cantidadGondola=marca->cantidadGondola-cantidad;
            }
            clienodo aux=clienteslog.primero;
            while(aux!=nullptr)
            {
                if(aux->cedula==std::to_string(cedula))
                {                    
                    nodoCompra*prod=aux->carrito->primero;
                    while(prod!=nullptr)
                    {
                        if(prod->nombre==marca->nombre)
                        {
                            prod->cantidad=prod->cantidad+cantidad;
                            return;
                        }
                        prod=prod->siguiente;
                    }
                    aux->carrito->InsertarInicio(std::to_string(pasillo),std::to_string(productoi),std::to_string(marcaI),marca->nombre,cantidad);

                }
                aux=aux->siguiente;
            }
        }
    }
}

void Mycliente::write(QByteArray data)
//Slot para escribir
{
        // Must always be called on thread 1
        this->socket->write(data);
}
void Mycliente::conectadoE(QByteArray data)
//Crea un nodo de clietne y lo agrega a una lista de loggeados
{
std::string cedula=data.toStdString().substr(2,7);
Pagina*cliente=new Pagina(5);
int k;
cliente=clientes.buscar(std::stoi(cedula),k);
if (cliente!=nullptr)
{
    string sen="LOS";
    clienodo client=colaclientes.primero;
    while(client)
    {
        if(client->cedula==cedula)
        {

            sen.append("C");
        }
        client=client->siguiente;
    }

    socket->write(QByteArray::fromStdString(sen));
    PilaC*carrito=new PilaC;
    clienteslog.insertarFinal(cedula,cliente->obtenerDato(k,0),cliente->obtenerDato(k,1),cliente->obtenerDato(k,3),carrito,cliente->obtenerEstadistica(k,0),this->socket->socketDescriptor());
    cliente->cambiarEstadistica(k,0,cliente->obtenerEstadistica(k,0)+1);
}
else
{
    socket->write("LON");
}
}
void Mycliente::registrarCliente(QByteArray data)
//Método de registro de clientes desde el cliente
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
    cedula=cedula.substr(2,7);
    int cedulaS = std::stoi(cedula);
    int n;
    Pagina* aux = clientes.buscar(cedulaS,n);
    if (aux == NULL){
        clientes.insertar(cedulaS,nombre,numero,ciudad,correo);
        aux->cambiarEstadistica(n,0,aux->obtenerEstadistica(n,0)+1);
        socket->write("RGY");

    }
    else
    {
        socket->write("RGN");
    }
}
void Mycliente::setCedula(int cedula)
//Set de cédula del socket
{
    this->cedula=cedula;
}
string Mycliente::inordenMandar(pNodoBinario nodo)
//Devuelve un string con el arbol binario
{
    if(nodo==NULL){
            return "";
    }else
    {   string aux;
        aux.append("Nombre: ");
        aux.append(nodo->nombre);
        aux.append(" Codigo: ");
        aux.append(std::to_string(nodo->valor));
        aux.append("\n");
        aux+=inordenMandar(nodo->Hizq);
        aux+=inordenMandar(nodo->Hder);
        return aux;
    }
}
string Mycliente::inordenMandarP(pNodoBinarioAVL nodo)
//Devuelve un string con el arbol avl seleccionado
{
    if(nodo==NULL){
            return "";
    }else
    {   string aux;
        aux.append("Nombre: ");
        aux.append(nodo->nombre);
        aux.append(" Codigo: ");
        aux.append(std::to_string(nodo->valor));
        aux.append("\n");
        aux+=inordenMandarP(nodo->Hizq);
        aux+=inordenMandarP(nodo->Hder);
        return aux;
    }
}
string Mycliente::inordenMandarM(NodePtr nodo)
//Devuelve un string con las marcas del rojinegro requerido
{
    if(nodo==NULL){
            return "";
    }else
    {   string aux;
        aux.append("Nombre: ");
        aux.append(nodo->nombre);
        aux.append(" Codigo: ");
        aux.append(std::to_string(nodo->data));
        aux.append(" Precio: ");
        aux.append(std::to_string(nodo->precio));
        aux.append("\n");
        aux+=inordenMandarM(nodo->left);
        aux+=inordenMandarM(nodo->right);
        return aux;
    }
}

