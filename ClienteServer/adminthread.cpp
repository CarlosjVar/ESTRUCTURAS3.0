#include "adminthread.h"
#include "menu.h"
using namespace std;
adminThread::adminThread(QObject*parent)
{

}
void adminThread::run()
{
    cout<<"Bienvenido a la interfaz del administrador"<<endl;
    cout<<"Por favor ingrese sus credenciales de administrador: "<<endl;
    int cedula;
    cin>>cedula;
    Pagina*pag=new Pagina(5);
    int k;
    pag=administradores.buscar(cedula,k);
    if(pag!=nullptr)
    {
        cout<<"Bienvenido: "<<pag->obtenerDato(k,0)<<endl;
        Menu menu1 = Menu();
        menu1.menu();
    }
    else
    {
        cout<<"Codigo incorrecto"<<endl;
        return run();
    }
}
void adminThread::FacturarCliente()
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
