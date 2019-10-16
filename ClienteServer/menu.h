#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "Globales.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


class Menu{
public:
    Menu()
    {
        Cola*espera=new Cola;
    }
//void rellenarInventario(inventario inven,listasort listaventas);
//int traerInventario(inventario inventario,int solicita,conodo compra);
//void rellenarGondolasMarc(inventario inventario,pNodoBinarioAVL pasillo,pNodoBinarioAVL producto,conodo compra);
//void rellenarGondolasProd(inventario inventario,pNodoBinarioAVL pasillo,conodo compra);
//void rellenarGondolas(Binario B1,inventario inventario,listasort listaventas);
//void comprar(listaClientes clientes,Binario B1);
//void facturarCliente(Binario B1,inventario inventariop,listaClientes clientes);
void menu();
void menuAgregar ();
void menuModificar ();
void agregarPasillo ();
void agregarProducto ();
void agregarMarca ();
void agregarCliente ();
void modificarPrecio ();
void modificarImpuesto ();
void modificarPertenencia ();
//void menucompra(Binario B1,clienodo persona);
//void agregarcarrito(Binario B1,clienodo persona);
//void agregarcarrito2(Binario B1,clienodo persona,pNodoBinarioAVL pasillop);
//void agregarcarrito3(Binario B1,clienodo persona,pNodoBinarioAVL pasillop,pNodoBinarioAVL productop);
//void agregarcarrito4(Binario B1,clienodo persona,pNodoBinarioAVL pasillop,pNodoBinarioAVL productop,Node*marcap);
//void getPrecio(string pasillo,string producto,string marca);
//void reportes(Binario B1,listaClientes clientes,inventario inven);
private:
    Cola*espera;
    float impuestoEnCanasta = 1.0;
    float impuestoFueraDeCanasta = 13.0;
//    listasort listaventasG;
//    listasort listaventasI;
};


//void Menu::reportes(Binario B1,ArbolB cliente,inventario inven)
/////Input: ListaDC Supermercado, listaClientes
/////output: Funci�n que genera un reporte
/////Funci�n: Sirve de men� para generar reportes
//{
//    int opcion;
//    cout<<"Que desea hacer?"<<endl;
//    cout<<"1. Pasillo mas visitado \n";
//    cout<<"2. Pasillo menos visitado \n";
//    cout<<"3. Productos por pasillo m�s vendidos \n";
//    cout<<"4. Marca mas vendida \n";
//    cout<<"5. Cliente que mas compro \n";
//    cout<<"6. Cliente que menos compro \n";
//    cout<<"7. Producto mas cargado en gondolas \n";
//    cout<<"8. Cliente que más facturó \n";
//    cout<<"9. Marcas de un producto \n";
//    cout<<"10.Productos de un pasillo \n";
//    cout<<"11.Clientes del supermercado \n";
//    cout<<"12.Pasillos del supermercado \n";
//    cout<<"13.Inventario del supermercado \n";
//    cout<<"Opcion: ";
//    cin>>opcion;
//    if(cin.fail())
//    {
//        cout<<"Entrada invalida,por favor ingrese numeros"<<endl;
//        cin.clear();
//        cin.ignore(256,'\n');
//        return reportes(super,cliente,inven);
//    }
//    if(opcion<14 || opcion>0)
//    {
//        switch(opcion)
//        {
//        case 1:
//            {
//            super.pasilloMV(super);
//            string topicname="Pasillo+Visitado";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//            }
//        case 2:
//            {
//
//            super.pasilloLV(super);
//            string topicname="Pasillo-Visitado";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//            }
//        case 3:
//            {
//            super.prodPasillMv(super);
//            string topicname="ProductoPas";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            }
//            break;
//        case 4:
//            {
//
//            super.marcasV(super);
//            string topicname="Marcas+V";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//            }
//
//        case 5:
//            {
//            cliente.clienteMas(cliente);
//            string topicname="ClienteMas";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//            }
//        case 6:
//        {
//            cliente.clienteMenos(cliente);
//            string topicname="ClienteMenos";
//     #include  "Pila.h"       topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//        }
//        case 7:
//        {
//            super.sacarMR(super);
//            string topicname="Marcas+R";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//        }
//        case 8:
//        {
//            cliente.masfacturas(cliente);
//            string topicname="ClienteMasF";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//        }
//
//        case 9:
//        {
//        super.marcasPasProd(super);
//        string topicname="MarcxProdxPas";
//        topicname="notepad \""+topicname+"\"";
//        system(topicname.c_str());
//        break;
//        }
//
//        case 10:
//        {
//        super.productosPas(super);
//        string topicname="ProdxPas";
//        topicname="notepad \""+topicname+"\"";
//        system(topicname.c_str());
//        break;
//        }
//
//        case 11:
//            {
//            cliente.sacarClientes(cliente);
//            string topicname="ClientesR";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//            }
//        case 12:
//            {
//            super.sacarPas(super);
//            string topicname="PasillosR";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//            }
//
//        case 13:
//        {
//            inven.sacarInv(inven);
//            string topicname="InventarioR";
//            topicname="notepad \""+topicname+"\"";
//            system(topicname.c_str());
//            break;
//        }
//        }
//    }
//    else
//    {
//        cout<<"Digite una opci�n del 1 al 13"<<endl;
//        return reportes(super,cliente,inven);
//    }
//
//
//
//
//}

//void Menu::agregarcarrito4(Binario super,clienodo persona,pNodoBinarioAVL pasillop,pNodoBinarioAVL productop,Node*marcap)
/////In:Binario B1,clienodo persona,pNodoBinarioAVL pasillop,pNodoBinarioAVL productop,pNodoBinarioAVL marcap
/////out:None
/////Funci�n se encarga de pedir la cantidad de productos que quiere adquirir al carrito
//{
// int cantidad;
// if(marcap->cantidadGondola==0)
// {
//     cout<<"Actualmente no hay stock de este producto, por favor esperar a que la administraci�n recargue las gondolas"<<endl;
//     return menucompra(super,persona);
// }
// cout<<"Actualmente hay "<<marcap->cantidadGondola<<" productos"<<endl;
// cout<<"Cuantos productos desea llevar? ";
// cin>>cantidad;
// if(cin.fail())
//{
//    cout<<"Entrada invalida,por favor ingrese una cantidad valida"<<endl;
//    cin.clear();
//    cin.ignore(256,'\n');
//    return agregarcarrito4(super,persona,pasillop,productop,marcap);
//}
//if(cantidad>marcap->cantidadGondola)
//{
//    string vrfc;
//    cout<<"Actualmente solo hay "<<marcap->cantidadGondola<<" productos, desea llevarse lo que hay?"<<endl;
//    cout<<"1=Si \n 0=No"<<endl;
//    cin>>vrfc;
//    if (vrfc=="1")
//    {
//    cantidad=marcap->cantidadGondola;
//    marcap->cantidadGondola=marcap->cantidadGondola-marcap->cantidadGondola;
//    }
//    else
//    {
//        return menucompra(super,persona);
//    }
//}
//else
//{
//  marcap->cantidadGondola=marcap->cantidadGondola-cantidad;
//}
//if(persona->carrito->PilaVacia())
//{
//    persona->carrito->InsertarInicio(pasillop->valor,productop->valor,marcap->data,marcap->nombre,cantidad);
//}
//else
//{
//    conodo aux=persona->carrito->primero;
//    while(aux!=NULL)
//    {
//        if(aux-==marcap->marca)
//        {
//            aux->cantidad=aux->cantidad+cantidad;
//        }
//        aux=aux->siguiente;
//    }
//    persona->carrito->InsertarInicio(pasillop->valor,productop->valor,marcap->valor,marcap->nombre,cantidad);
//}
////pasillop->visitas++;
////productop->visitas++;
////marcap->visitas=marcap->visitas+cantidad;
//return menucompra(super,persona);
//}
//void Menu::agregarcarrito3(Binario super,clienodo persona,pNodoBinarioAVL pasillop,pNodoBinarioAVL productop)
/////In:Binario B1,clienodo persona,pNodoBinarioAVL pasillop,pNodoBinarioAVL productop
/////Out:None
/////Funci�n: Da a elegir entre las marcas
//{

//    string marcap;
//    Node*marcas=productop->marcas;
//    cout<<"Indique cual el c�digo de la marca a comprar: "<<"\n"<<endl;
//    cout<<"Ingrese 0 si quiere volver a la secci�n de productos"<<"\n"<<endl;
//    //Aquí va impresión
//    cout<<"Marca: ";
//    cin>>marcap;
//    cout<<""<<endl;
//    marcas=productop->marcas;
//    //buscarnodo
//    if(marcap==marcas->data.toString)
//    {
//    }
//    else if(marcap=="0")
//    {
//        return agregarcarrito2(super,persona,pasillop);
//    }
//    else
//    {
//        cout<<"Ese producto no existe"<<endl;
//        return agregarcarrito3(super,persona,pasillop,productop);
//    }
//    return agregarcarrito4(super,persona,pasillop,productop,marcas);
//}
//void Menu::agregarcarrito2(Binario B1,clienodo persona,pNodoBinarioAVL pasillop)
/////In:Binario B1,clienodo persona,pNodoBinarioAVL pasillop
/////None_
/////Funci�n: Da a elegir entre productos
//{
//    string productop;
//    pNodoBinarioAVL productos=pasillop->producto;
//    cout<<"Indique cual el c�digo del que producto quiere revisar: "<<"\n"<<endl;
//    cout<<"Ingrese 0 si quiere volver a la secci�n de pasillos"<<"\n"<<endl;
//    cout<<productos->nombre<<"    Codigo: "<<productos->valor<<"\n"<<endl;
//    cout<<"Producto: ";
//    cin>>productop;
//    cout<<""<<endl;
//    productos=pasillop->producto;
//    while(productos->siguiente!=pasillop->producto)
//    {   cout<<productos->codigoProd<<endl;
//        if(productop==productos->codigoProd)
//            break;
//        productos=productos->siguiente;
//    }
//    if(productop==productos->valor.tostring())
//    {
//    }
//    else if(productop=="0")
//    {
//        return agregarcarrito(super,persona);
//    }
//    else
//    {
//        cout<<"Ese producto no existe"<<endl;
//        return agregarcarrito2(super,persona,pasillop);
//    }
//    return agregarcarrito3(super,persona,pasillop,productos);

//}
//void Menu::agregarcarrito(Binario B1,clienodo persona)
/////In:Binario B1,clienodo persona
/////None_
/////Funci�n: Da a elegir entre pasillos
//{
//    string pasillop;
//    cout<<"Indique el codigo del pasillo que quiere recorrer: "<<"\n"<<endl;
//    cout<<"Ingrese 0 si quiere volver al menu de compra"<<"\n"<<endl;
//    pNodoBinarioAVL pasillo=super.primero;
//    while(pasillo->siguiente!=super.primero)
//    {
//        cout<<pasillo->nombreP<<"    Codigo: "<<pasillo->codigoP<<endl;
//        pasillo=pasillo->siguiente;
//    }
//    cout<<pasillo->nombreP<<"    Codigo: "<<pasillo->codigoP<<endl;
//    cout<<"Pasillo: ";
//    cin>>pasillop;
//    cout<<""<<endl;
//    pasillo=super.primero;
//    while(pasillo->siguiente!=super.primero)
//    {
//        if(pasillop==pasillo->codigoP)
//            break;
//        pasillo=pasillo->siguiente;
//    }
//    if(pasillop==pasillo->codigoP)
//    {
//    }
//    else if(pasillop=="0")
//    {
//        return menucompra(super,persona);
//    }
//    else
//    {
//        cout<<"Ese pasillo no existe"<<endl;
//        return agregarcarrito(super,persona);
//    }
//    return agregarcarrito2(super,persona,pasillo);
//}
//void Menu::menucompra(Binario super,clienodo persona)
/////In:ListaDC super,clienodo persona
/////Out:None
/////Funci�n: permite al usuario elegir entre seguir comprando o irse a la cola de espera
//{   int opcion;
//    cout<<"Que desea realizar?"<<"\n"<<endl;
//    cout<<"1.  Añadir compra al carrito"<<endl;
//    cout<<"2.  Pagar"<<"\n"<<endl;
//    cout<<"Recuerde que una vez en la cola de espera no podra realizar mas compras hasta que vuelva a entrar al supermercado"<<"\n"<<endl;
//    cout<<"Opcion: ";
//    cin>>opcion;
//    cout<<" "<<endl;

//    if(cin.fail())
//{
//    cout<<"Entrada invalida,por favor ingrese numeros"<<endl;
//    cin.clear();
//    cin.ignore(256,'\n');
//    return menucompra(super,persona);
//}
//    if (opcion==1)
//    {
//       agregarcarrito(super,persona);
//    }
//    else if (opcion==2)
//    {
//        int consecutivo=persona->facturas;
//        persona->facturas++;
//        espera->insertarFinal(persona->cedula,persona->nombre,persona->telefono,persona->correo,persona->carrito,consecutivo);
//        return;
//    }
//    else
//    {
//        return menucompra(super,persona);
//    }
//}
//void Menu::comprar(ArbolB clientes,Binario super)
/////In:ListaDC super,clienodo persona
/////Out:None
/////Funci�n: Solicita cedula y verifica contra listacliente/colaespera
//{
//string cedula;
//cout<<"Por favor ingrese su numero de cedula:  "<<endl;
//cout<<"Cedula: ";
//cin>>cedula;
//cout<<" "<<endl;
//clienodo aux=clientes.primero;
//while(aux->siguiente!=clientes.primero)
//{
//    if(cedula==aux->cedula)
//    {
//        break;
//    }
//    aux=aux->siguiente;
//}
//if(cedula==aux->cedula)
//{
//    clienodo validar=espera->primero;
//    while(validar!=NULL)
//    {
//        if(validar->cedula==aux->cedula)
//        {
//            cout<<"Esta cedula se encuentra en el supermercado"<<endl;
//            return;
//        }
//        validar=validar->siguiente;
//    }
//    cout<<"Bienvenido :"<<aux->nombre<<"\n"<<endl;
//    aux->carrito=new Pila;
//    menucompra(super,aux);
//}
//else{
//    cout<<"No se encuentra afiliado"<<endl;
//    return;
//}
//}
//int Menu::traerInventario(int solicita,conodo compra)
/////In: inventario inventario,int solicita,conodo compra
/////Out: Solicita
/////Funci�n: Intenta retornar el valor deseado por el usuario para rellenar las g�ndolas
//{
//    inodo inventa=inventario.primero;
//    while(inventa->siguiente!=NULL)
//    {
//        if(inventa->pasillo==compra->pasillo)
//        {
//            if(inventa->producto==compra->producto)
//            {
//                if (inventa->marca==compra->marca)
//                {
//                    break;
//                }
//            }
//        }
//        inventa=inventa->siguiente;
//    }
//    if(inventa->pasillo==compra->pasillo)
//        {
//            if(inventa->producto==compra->producto)
//            {
//                if (inventa->marca==compra->marca)
//                {
//                    if(inventa->cantidad>solicita)
//                    {
//                        inventa->cantidad=inventa->cantidad-solicita;
//                        return solicita;
//                    }
//                    else if(inventa->cantidad==0)
//                    {
//                        cout<<"No hay de este producto en inventario"<<endl;
//                        return 0;
//                    }
//                    else
//                    {
//                       solicita=inventa->cantidad;
//                       inventa->cantidad=0;
//                       return solicita;
//                    }
//                }
//
//            }
//        }
//
//}
//void Menu::rellenarGondolasMarc(inventario inventario,pNodoBinarioAVL pasillo,pNodoBinarioAVL producto,conodo compra)
/////In:inventario inventario,pNodoBinarioAVL pasillo,pNodoBinarioAVL producto,conodo compra
/////Out:None
/////Funci�n:Verifica que exista la marca y solicita cuanto quiere recargar
//{
//    int relleno;
//    int entrada;
//    pNodoBinarioAVL marca=producto->marca;
//    while(marca->siguiente!=producto->marca)
//    {
//        if(marca->marca==compra->marca)
//        {
//            break;
//        }
//        marca=marca->siguiente;
//    }
//    if(marca->marca==compra->marca)
//    {
//        if (marca->cantidadGondola<=2)
//        {
//            cout<<"Digite el cuantos productos de "<<marca->nombre<<" desea rellenar: ";
//            cin>>entrada;
//            cout<<""<<endl;
//            if(cin.fail())
//            {
//                cout<<"Entrada invalida,por favor ingrese numeros"<<endl;
//                cin.clear();
//                cin.ignore(256,'\n');
//                return rellenarGondolasMarc(inventario,pasillo,producto,compra);
//            }
//            if(entrada<1)
//            {
//                cout<<"Digite un n�mero mayor que 0"<<endl;
//                return rellenarGondolasMarc(inventario,pasillo,producto,compra);
//            }
//            else
//            {
//                relleno=traerInventario(inventario,entrada,compra);
//                marca->recarga=marca->recarga+relleno;
//                marca->cantidadGondola=marca->cantidadGondola+relleno;
//            }
//
//        }
//
//
//    }
//
//}
//void Menu::rellenarGondolasProd(inventario inventario,pNodoBinarioAVL pasillo,conodo compra)
/////In: inventario inventario,pNodoBinarioAVL pasillo,conodo compra
/////Out:None
/////Funci�n: Busca coincidencias de productos
//{
//    pNodoBinarioAVL producto=pasillo->producto;
//    while(producto->siguiente!=pasillo->producto)
//    {
//        if(producto->codigoProd==compra->producto)
//        {
//            break;
//        }
//        producto=producto->siguiente;
//    }
//    if(producto->codigoProd==compra->producto)
//    {
//    rellenarGondolasMarc(inventario,pasillo,producto,compra);
//    }
//
//
//}
//void Menu::rellenarGondolas(Binario B1,inventario inventario,listasort listaventas)
/////In: Binario B1,inventario inventario,listasort listaventas
/////Out: None
/////Funci�n: Revisa que listaventas no est� vac�a y revisa si hay coincidencia de pasillos entre listaventas y pasillos del supermercado
//{
//    conodo check=listaventas.first;
//    if (listaventas.empty())
//    {
//        cout<<"No hay nada en la lista de ventas para revisar"<<endl;
//        return;
//    }
//
//    else
//    {
//        while(check!=NULL)
//        {
//            pNodoBinarioAVL pasillo=super.primero;
//            while(pasillo->siguiente!=super.primero)
//            {
//                if(check->pasillo==pasillo->codigoP)
//                {
//                    break;
//                }
//                pasillo=pasillo->siguiente;
//            }
//            if(check->pasillo==pasillo->codigoP)
//            {
//              rellenarGondolasProd(inventario,pasillo,check);
//            }
//
//            check=check->siguiente;
//        }
//    }
//
//
//}
//void Menu::facturarCliente(Binario B1,inventario inventariop,listaClientes clientes)
/////In:Binario B1,inventario inventariop
/////Out:None
/////Funci�n: Se encarga de realizar facturas en funci�n de la pila de productos del cliente, esta pila pasa a una lista, la cual se ordena con quicksort para luego ser recorrida con el fin de poner cada producto en la factura
//{
//    float totalT
//    ;
//    clienodo atendido=espera->obtenercliente();
//    listasort ordenada;
//    while(atendido->carrito->primero!=NULL)
//    {
//        conodo inserto=atendido->carrito->primero;
//        ordenada.insert(inserto->pasillo,inserto->producto,inserto->marca,inserto->nombre,inserto->cantidad);
//        atendido->carrito->primero=atendido->carrito->primero->siguiente;

//    }
//    MergeSort(&ordenada.first);
//    ofstream outfile(atendido->cedula+".txt",ios_base::app);
//    outfile<<"Cedula: "<<atendido->cedula<<"-"<<atendido->facturas<<endl;
//    outfile<<"Nombre: "<<atendido->nombre<<endl;
//    outfile<<"Número: "<<atendido->telefono<<"\n \n"<<endl;
//    conodo item=ordenada.first;
//    while(item!=NULL)
//    {
//        int precio=super.preciomarca(item->pasillo,item->producto,item->marca);
//        bool canasta=inventariop.canasta(item->pasillo,item->producto,item->marca);
//        int total=precio*item->cantidad;
//        if(canasta)
//        {
//            float aplic=total*0.13f;
//            outfile<<"Cantidad: "<<item->cantidad<<" Codigo: "<<item->marca<<" Nombre: "<<item->nombre<<" Precio: "<<precio<<" Impuesto:"<<aplic<<" Total: "<<total+aplic<<endl;
//            totalT=totalT+total+aplic;
//        }
//        else
//        {
//            float aplic=total*0.01f;
//            outfile<<"Cantidad: "<<item->cantidad<<" Codigo: "<<item->marca<<" Nombre: "<<item->nombre<<" Precio: "<<precio<<" Impuesto:"<<aplic<<" Total: "<<total+aplic<<endl;
//            totalT=totalT+total+aplic;
//        }
//        listaventasI.insert(item->pasillo,item->producto,item->marca,item->producto,item->cantidad);
//        listaventasG.insert(item->pasillo,item->producto,item->marca,item->producto,item->cantidad);
//        item=item->siguiente;
//    }


//    outfile<<"                      Total a pagar: "<<totalT<<"\n \n \n \n"<<endl;
//    outfile.close();
//    clienodo pers=clientes.primero;
//    while (pers->siguiente!=clientes.primero)
//    {
//        if(pers->cedula==atendido->cedula)
//        {
//            break;
//        }
//        pers=pers->siguiente;
//    }
//    if(pers->cedula==atendido->cedula)
//    {
//        if(pers->mayor<totalT)
//        {
//            pers->mayor=totalT;
//        }
//        pers->total=pers->total+totalT;
//    }

//    espera->BorrarInicio();
//    return;
//}

#endif // MENU_H_INCLUDED
