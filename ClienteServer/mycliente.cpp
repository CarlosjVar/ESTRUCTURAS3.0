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
        else if(data.toStdString().substr(2,2)=="CO")
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
                std::cout<<marca->cantidadGondola<<std::endl;
                string arbol=std::to_string(marca->cantidadGondola);
                send.append(arbol);
                std::cout<<send<<std::endl;
                this->write(QByteArray::fromStdString(send));
            }
            else
            {
                QByteArray validacion="VAMA";
                this->write(validacion);
            }
        }
        else if(data.toStdString().substr(2,2)=="AG")
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
            clienodo aux=colaclientes.primero;
            while(aux!=nullptr)
            {
                if(aux->cedula==std::to_string(cedula))
                {
                    std::cout<<aux->nombre<<std::endl;
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
                    aux=aux->siguiente;
                }
            }
        }
    }
}

void Mycliente::write(QByteArray data)
{
        // Must always be called on thread 1
        this->socket->write(data);
}
void Mycliente::enviov(QByteArray data)
{
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
    cout<<this->socket->socketDescriptor()<<endl;
    socket->write("LOS");
    PilaC*carrito=new PilaC;
    colaclientes.insertarFinal(cedula,cliente->obtenerDato(k,0),cliente->obtenerDato(k,1),cliente->obtenerDato(k,2),carrito,0,this->socket->socketDescriptor());
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
{
    if(nodo==NULL){
            return "";
    }else
    {   string aux;
        aux.append("Nombre: ");
        aux.append(nodo->nombre);
        aux.append(" Codigo: ");
        aux.append(std::to_string(nodo->data));
        aux.append("Precio: ");
        aux.append(std::to_string(nodo->precio));
        aux.append("\n");
        aux+=inordenMandarM(nodo->left);
        aux+=inordenMandarM(nodo->right);
        return aux;
    }
}
void Mycliente::FacturarCliente()
///In:listaDCPas super,inventario inventariop
///Out:None
///Funci�n: Se encarga de realizar facturas en funci�n de la pila de productos del cliente, esta pila pasa a una lista, la cual se ordena con quicksort para luego ser recorrida con el fin de poner cada producto en la factura
{
    connect(this,SIGNAL(envio(QByteArray)),this,SLOT(enviov(QByteArray)));
    float totalT;
    string enviar;
    enviar.append("FA");
    clienodo atendido=colaclientes.obtenercliente();
    listasort ordenada;
    while(atendido->carrito->primero!=NULL)
    {
        conodo inserto=atendido->carrito->primero;
        ordenada.insert(inserto->pasillo,inserto->producto,inserto->marca,inserto->nombre,inserto->cantidad);
        atendido->carrito->primero=atendido->carrito->primero->siguiente;

    }
    MergeSort(&ordenada.first);
    ofstream outfile(atendido->cedula+".txt",ios_base::app);
    outfile<<"Cedula: "<<atendido->cedula<<"-"<<atendido->facturas<<endl;
    enviar=enviar+"Cedula"+atendido->cedula+"-"+std::to_string(atendido->facturas)+"\n";
    outfile<<"Nombre: "<<atendido->nombre<<endl;
    enviar=enviar+"Nombre: "+atendido->nombre+"\n";
    outfile<<"Número: "<<atendido->telefono<<"\n"<<endl;
    enviar=enviar+"Numero: "+atendido->telefono+"\n";
    outfile<<"Correo: "<<atendido->correo<<"\n \n"<<endl;
    enviar=enviar+"Correo: "+atendido->correo+"\n \n";
    conodo item=ordenada.first;

    while(item!=NULL)
    {
        int precios=precio(item);
        string codigo=item->pasillo+item->producto+item->marca;
        nodoAA*impuesto=inventario.buscarNodoAA(inventario.raiz,stoi(codigo));
        int total=precios*item->cantidad;
        cout<<"total"<<total<<endl;
        if(impuesto->canastaB==1)
        {
            float aplic=total*(impuesto->impuesto/100);
            outfile<<"Cantidad: "<<item->cantidad<<" Codigo: "<<item->marca<<" Nombre: "<<item->nombre<<" Precio: "<<precios<<" Impuesto:"<<aplic<<" Total: "<<total+aplic<<endl;
            enviar=enviar+"Cantidad: "+std::to_string(item->cantidad)+" Codigo: "+item->marca+" Nombre: "+item->nombre+" Precio: "+std::to_string(precios)+" Impuestos: "+std::to_string(aplic)+" Total: "+std::to_string(total+aplic)+"\n";
            totalT=totalT+total+aplic;
        }
        else
        {
            float aplic=total*0.1f;
            outfile<<"Cantidad: "<<item->cantidad<<" Codigo: "<<item->marca<<" Nombre: "<<item->nombre<<" Precio: "<<precios<<" Impuesto:"<<aplic<<" Total: "<<total+aplic<<endl;
            cout<<"Cantidad: "<<item->cantidad<<" Codigo: "<<item->marca<<" Nombre: "<<item->nombre<<" Precio: "<<precios<<" Impuesto:"<<aplic<<" Total: "<<total+aplic<<endl;
            enviar=enviar+"Cantidad: "+std::to_string(item->cantidad)+" Codigo: "+item->marca+" Nombre: "+item->nombre+" Precio: "+std::to_string(precios)+" Impuestos: "+std::to_string(aplic)+" Total: "+std::to_string(total+aplic)+"\n";
            totalT=totalT+total+aplic;
        }
        item=item->siguiente;
    }
//            listaventasI.insert(item->pasillo,item->producto,item->marca,item->producto,item->cantidad);
//            listaventasG.insert(item->pasillo,item->producto,item->marca,item->producto,item->cantidad);
    outfile<<"                      Total a pagar: "<<totalT<<"\n \n \n \n"<<endl;
    outfile.close();
    QList<Mycliente*>::iterator i;
    foreach (Mycliente*sok,lisSock)
    {
        cout<<"Socket: "<<sok->socket->socketDescriptor()<<" Este cliente: "<<atendido->socket<<endl;
        if(sok->socket->socketDescriptor()==atendido->socket)
        {
            QByteArray asd;
            emit envio(asd);
        }
    }

    colaclientes.BorrarInicio();
    return;
}
int Mycliente::precio(conodo compremix)
{
    pNodoBinario pas=buscarNodo(supermercado.raiz,stoi(compremix->pasillo));
    pNodoBinarioAVL pro=buscarNodoAVL(pas->productos,stoi(compremix->producto));
    RBTree rojo=RBTree(pro->marcas);
    NodePtr marca=rojo.searchTree(stoi(compremix->marca));
    return marca->precio;

}
