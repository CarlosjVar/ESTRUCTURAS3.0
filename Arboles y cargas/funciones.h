/*
Tarea programada #1 - Grupo 01 de Estructuras de datos
Joseph Tenorio Pereira, 2019064588
Fecha de entrega: 19/9/2019
Header de funciones
*/

//Importacion de librearias y headers
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Prototipos de funciones
nodoCompra* SortedMerge(nodoCompra* a, nodoCompra* b);
void FrontBackSplit(nodoCompra* source,nodoCompra** frontRef, nodoCompra** backRef);


//Definicion de funciones

/*
Funcionamiento: Verifica que un string dado esta compuesto solo por caracteres numericos
Entrada: pString (string)
Salida: Un booleano de true/false
*/

/*
Funcionamiento: Muestra los datos de todos los nodos enlazados a partir de un puntero a un nodoMarca dado
Entrada: puntero a un nodoMarca
Salida: N/A
*/


/*
Funcionamiento: Muestra el precio, codigo y nombre de todos los nodos enlazados a partir de un puntero a un nodoMarca dado
Entrada: puntero a un nodoMarca
Salida: N/A
*/


/*
Funcionamiento: Muestra el codigo y nombre de todos los nodos enlazados a partir de un puntero a un nodoProducto dado
Entrada: puntero a un nodoProducto
Salida: N/A
*/


/*
Funcionamiento: Cuenta la cantidad de nodos enlazados a partir de un nodoProducto dado
Entrada: puntero a un nodoProducto
Salida: cont (int)
*/

/*
Funcionamiento: Cuenta la cantidad de nodos enlazados a partir de un nodoMarca dado
Entrada: puntero a un nodoMarca
Salida: cont (int)
*/

/*
Funcionamiento: Cuenta la cantidad de nodos enlazados a partir de un nodoCompra dado
Entrada: puntero a un nodoCompra
Salida: cont (int)
*/

/*
Funcionamiento: Carga los productos a la estructura de datos (lista de pasillos)
Entrada: El archivo a cargar pNombreArchivo (string) y la lista de pasillos destino pLPasillos (listaPasillos)
Salida: N/A
*/

/*
Funcionamiento: Realiza el procedimiento de compra de un cliente dado
Entrada: Puntero al cliente que compra pCliente (pnodoCliente), cola de facturacion pColaFacturacion colaClientes y  la lista de pasillos
en la cual se compra pListaPasillos (listaPasillos)
Salida: Booleano de repeticion True/False
*/
bool comprarCliente (Binario pListaPasillos, clienodo &pCliente, ColaS &pColaFacturacion){
    int cantidad;
    string cantidadS;
    string codigoMarcaS;
    int codigoMarca;
    string codigoProductoS;
    int codigoProducto;
    int codigoPasillo;
    string codigoPasilloS;
         cout<<"Bienvenid@, "<<pCliente->nombre<<endl;
            pListaPasillos.Mostrar();
            cout<<"Por favor digite el numero del pasillo en el que desea comprar: ";
            cin>>codigoPasilloS;
            if(esNumerico(codigoPasilloS)){
                codigoPasillo= stoi (codigoPasilloS);
            }else{
                cout<<"Debe digitar un codigo de pasillo valido"<<endl;
                return false;
            }
            pnodoPasillo aux2 = pListaPasillos.primero;
            for (int i2 = 1; i2<=pListaPasillos.largoLista();i2++,aux2=aux2->siguiente){
                if (aux2->codigo==codigoPasillo){
                    aux2->cantidadVisitas+=1;
                    cout<<"Los productos disponibles en este pasillo son: "<<endl;
                    mostrarNodosProductoCodigo(aux2->pproductos);
                    cout<<"Por favor digite el codigo del producto que desea comprar: ";
                    cin>>codigoProductoS;
                    if(esNumerico(codigoProductoS)){
                        codigoProducto= stoi (codigoProductoS);
                    }else{
                        cout<<"Debe digitar un codigo de producto valido"<<endl;
                        return false;
                    }
                    pnodoProducto aux3 = (aux2->pproductos);
                    int lim2 = cantidadNodosProducto(aux3);
                    for (int i3 = 1; i3<=lim2;i3++,aux3=aux3->siguiente){
                        if (aux3->codigo==codigoProducto){
                            cout<<"Las marcas disponibles de este producto son: "<<endl;
                            mostrarNodosMarcaCodigo(aux3->pmarcas);
                            cout<<"Por favor digite el codigo de la marca que desea comprar: ";
                            cin>>codigoMarcaS;
                            if(esNumerico(codigoMarcaS)){
                            codigoMarca= stoi (codigoMarcaS);
                            }else{
                                cout<<"Debe digitar un codigo de marca valido"<<endl;
                                return false;
                            }
                            pnodoMarca aux4 = (aux3->pmarcas);
                            int lim4 = cantidadNodosMarca(aux4);
                            for (int i4 = 1; i4<=lim4;i4++,aux4=aux4->siguiente){
                                if (aux4->codigo==codigoMarca){
                                    cout<<"Usted ha escogido la marca: "<<aux4->nombre<<endl;
                                    cout<<"Por favor digite la cantidad que desea comprar: ";
                                    cin>>cantidadS;
                                    if(esNumerico(cantidadS)){
                                        cantidad = stoi (cantidadS);
                                        if (aux4->cantidadGondola>=cantidad){
                                            string opcion;
                                            if (pCliente->carrito==NULL){
                                                pCliente->carrito=new listaCompras ();
                                                (*(pCliente->carrito)).InsertarInicio (aux4->codigoPasillo,aux4->codigoProducto,aux4->codigo,aux4->nombre,cantidad);
                                            }else{
                                                (*(pCliente->carrito)).InsertarInicio (aux4->codigoPasillo,aux4->codigoProducto,aux4->codigo,aux4->nombre,cantidad);
                                            }
                                            aux4->cantidadGondola-= cantidad;
                                            cout<<"Digite 1 para seguir comprando u otra tecla para salir: ";
                                            cin>>opcion;
                                            if (opcion=="1"){
                                                return true;
                                            }else{
                                                pCliente->enCola = true;
                                                pColaFacturacion.InsertarFinal(pCliente);
                                                return false;
                                            }
                                        }else{
                                            if (aux4->cantidadGondola==0){
                                                string opcion2;
                                                cout<<"Lo sentimos, no quedan existencias en gondola de esta marca"<<endl;
                                                cout<<"Digite 1 para seguir comprando u otra tecla para salir: ";
                                                cin>>opcion2;
                                                if (opcion2=="1"){
                                                    return true;
                                                }else{
                                                    if (pCliente->carrito==NULL||(*(pCliente->carrito)).ListaVacia()==true){
                                                        return false;
                                                    }else{
                                                        pCliente->enCola = true;
                                                        pColaFacturacion.InsertarFinal(pCliente);
                                                        return false;
                                                    }
                                                }
                                            }else{
                                                string opcion2;
                                                string opcion;
                                                cout<<"Lo sentimos, solo quedan "<<aux4->cantidadGondola<<" existencias de esta marca"<<endl;
                                                cout<<"Digite un 1 para llevarselas o cero para salir: ";
                                                cin>>opcion;
                                                if (opcion=="1"){
                                                    if (pCliente->carrito==NULL){
                                                        pCliente->carrito=new listaCompras ();
                                                        (*(pCliente->carrito)).InsertarInicio (aux4->codigoPasillo,aux4->codigoProducto,aux4->codigo,aux4->nombre,aux4->cantidadGondola);
                                                    }else{
                                                        (*(pCliente->carrito)).InsertarInicio (aux4->codigoPasillo,aux4->codigoProducto,aux4->codigo,aux4->nombre,aux4->cantidadGondola);
                                                    }
                                                    aux4->cantidadGondola = 0;
                                                    cout<<"Digite 1 para seguir comprando u otra tecla para salir: ";
                                                    cin>>opcion2;
                                                    if (opcion2=="1"){
                                                        return true;
                                                    }else{
                                                        pCliente->enCola = true;
                                                        pColaFacturacion.InsertarFinal(pCliente);
                                                        return false;
                                                    }
                                                }else{
                                                    if (pCliente->carrito==NULL||(*(pCliente->carrito)).ListaVacia()==true){
                                                        return false;
                                                    }else{
                                                        pCliente->enCola = true;
                                                        pColaFacturacion.InsertarFinal(pCliente);
                                                        return false;
                                                    }
                                                }
                                            }
                                        }
                                    }else{
                                        cout<<"La cantidad a tomar debe ser un valor entero"<<endl;
                                        return false;
                                    }
                                }
                            }
                            cout<<"Debe digitar un codigo de marca valido"<<endl;
                            return false;
                        }
                    }
                    cout<<"Debe digitar un codigo de producto valido"<<endl;
                    return false;
                }
            }
            cout<<"Debe digitar un codigo de pasillo valido"<<endl;
            return false;
}

/*
Funcionamiento: Auxiliar de la funcion comprarCliente
Entrada: Lista de cliente pListaClientes (listaClientes), cola de facturacion pColaFacturacion colaClientes y  la lista de pasillos
en la cual se compra pListaPasillos (listaPasillos)
Salida: N/A
*/
void AuxComprarCliente(listaPasillos pListaPasillos, listaClientes pListaClientes, colaClientes &pColaFacturacion){
    bool rep=true;
    string cedula;
    cout<<"Para comprar, debe brindar un numero de cedula valido"<<endl;
    cout<<"Digite su cedula: ";
    cin>>cedula;
    pnodoCliente aux = pListaClientes.primero;
    for (int i = 1; i<=pListaClientes.largoLista();i++,aux=aux->siguiente){
        if (aux->cedula==cedula){
            if (aux->enCola){
                cout<<"Debe esperar a ser facturado para volver a comprar"<<endl;
                return;
            }
            while (rep){
                rep = comprarCliente(pListaPasillos,aux,pColaFacturacion);

            }
            return;
        }
    }
    cout<<"Debe introducir una cedula valida para comprar"<<endl;
    return;
}

/*
Funcionamiento: Funcion recursiva del metodo de ordenamiento mergeSort
Entrada: Referencia al primero de nodosCompra enlazados headRef (nodoCompra)
Salida: N/A
Nota: Codigo original tomado de: https://www.geeksforgeeks.org/merge-sort/, adaptado a la estructura de datos del proyecto
*/
void MergeSort(nodoCompra** headRef)
{
    nodoCompra* head = *headRef;
    nodoCompra* a;
    nodoCompra* b;
    if ((head == NULL) || (head->siguiente == NULL)) {
        return;
    }
    FrontBackSplit(head, &a, &b);
    MergeSort(&a);
    MergeSort(&b);
    *headRef = SortedMerge(a, b);
}

/*
Funcionamiento: Funcion auxiliar de mergeSort
Entrada: Punteros a dos nodos a los cuales sortear a y b
Salida: puntero a nodoCompra
Nota: Codigo original tomado de: https://www.geeksforgeeks.org/merge-sort/, adaptado a la estructura de datos del proyecto
*/
nodoCompra* SortedMerge(nodoCompra* a, nodoCompra* b)
{
    nodoCompra* result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->cantidad >= b->cantidad) {
        result = a;
        result->siguiente = SortedMerge(a->siguiente, b);
    }
    else {
        result = b;
        result->siguiente = SortedMerge(a, b->siguiente);
    }
    return (result);
}

/*
Funcionamiento: Funcion recursiva del metodo de ordenamiento mergeSort, invierte dos nodos
Entrada: Punteros a dos nodos a los cuales cambiar a y b
Salida: N/A
Nota: Codigo original tomado de: https://www.geeksforgeeks.org/merge-sort/, adaptado a la estructura de datos del proyecto
*/
void FrontBackSplit(nodoCompra* source,nodoCompra** frontRef, nodoCompra** backRef)
{
    nodoCompra* fast;
    nodoCompra* slow;
    slow = source;
    fast = source->siguiente;
    while (fast != NULL) {
        fast = fast->siguiente;
        if (fast != NULL) {
            slow = slow->siguiente;
            fast = fast->siguiente;
        }
    }
    *frontRef = source;
    *backRef = slow->siguiente;
    slow->siguiente = NULL;
}

/*
Funcionamiento: Verifica, contra la lista de ventas, que todas las marcas tengan mas de 20 productos en stock
Entrada: Inventario a analizar pInventario (listaMarcasInventario), lista de ventas contra la cual buscar pListaVentasI (listaCompras)
Salida: N/A
*/
void verificarInventario (listaMarcasInventario &pInventario, listaCompras &pListaVentasI){
    if (pListaVentasI.ListaVacia()){
        cout<<"No se han registrado nuevas ventas aun"<<endl;
        return;
    }
    pnodoCompra aux2 = pListaVentasI.primero;
    int lim = cantidadNodosCompra(aux2);
    for (int i2 = 1;i2<=lim;i2++,aux2=aux2->siguiente){
         pnodoMarca aux = pInventario.primero;
         for (int i = 1;i<=pInventario.largoLista();i++,aux=aux->siguiente){
                if ((aux->cantidadGondola<20)&&(aux2->codigoPasillo==aux->codigoPasillo)&&(aux2->codigoProducto==aux->codigoProducto)&&aux2->codigo==aux->codigo){
                    int cantidad;
                    string cantidadS;
                    cout<<"Solo quedan ";
                    cout<<aux->cantidadGondola;
                    cout<<" existencias de la marca "+aux->nombre+" en el inventario"<<endl;
                    while (true){
                        cout<<"Digite la cantidad de productos a comprar para guardar en el inventario: ";
                        cin>>cantidadS;
                        if (esNumerico(cantidadS)){
                            cantidad = stoi (cantidadS);
                            break;
                        }else{
                            cout<<"La cantidad de productos a traer debe ser un numero entero"<<endl;
                        }
                    }
                    aux->cantidadGondola+=cantidad;
                    cout<<"Carga exitosa"<<endl;
                }
        }
    }
    pListaVentasI.primero = NULL;
    cout<<"Ya se han verificado las reservas de cada marca con ventas"<<endl;
    return;
}

/*
Funcionamiento: Genera la factura del cliente mas antiguo de la cola de facturacion
Entrada: Pasillos a analizar pListaPasillos (listaPasillos), lista de ventas en la cual guardar las ventas pListaVentas,pLista
VentasI,pListaVentasG(listaCompras), inventario del cual tomar el impuesto pInventario (listaMarcasInventario) y
cola de facturacion pCola (colaClientes)
Salida: N/A
*/
void FacturarFinal (colaClientes &pCola, listaMarcasInventario pInventario, listaPasillos pPasillos, listaCompras &pListaVentas, listaCompras &pListaVentasG, listaCompras &pListaVentasI){
    if (pCola.ListaVacia()){
        cout<<"No hay clientes en la cola de facturacion"<<endl;
        return;
    }
    float totalPagar=0;
    pnodoCliente cliente = pCola.BorrarInicio();
    listaCompras  listaSortear;
    pnodoCompra aux = (*(cliente->carrito)).primero;
    while ((*(cliente->carrito)).ListaVacia()==false){
        aux=(*(cliente->carrito)).BorrarInicio();
        if (listaSortear.ListaVacia()){
            listaSortear.InsertarInicio(aux->codigoPasillo,aux->codigoProducto,aux->codigo,aux->nombre,aux->cantidad);
        }else{
            bool repetido = false;
            pnodoCompra aux5 = listaSortear.primero;
            while (aux5!=NULL){
                if ((aux5->codigoPasillo==aux->codigoPasillo)&&(aux5->codigoProducto==aux->codigoProducto)&&(aux5->codigo==aux->codigo)){
                    repetido=true;
                    break;
                }
                aux5=aux5->siguiente;
            }
            if (repetido){
                aux5->cantidad+=aux->cantidad;
            }else{
                listaSortear.InsertarInicio(aux->codigoPasillo,aux->codigoProducto,aux->codigo,aux->nombre,aux->cantidad);
            }
        }
    }
    cliente->enCola = false;
    MergeSort(&(listaSortear.primero));
    ofstream archivo (cliente->cedula+".txt",ios_base::app);
    archivo<<"Cedula: "<<cliente->cedula<<endl;
    archivo<<"Nombre: "<<cliente->nombre<<endl;
    archivo<<"Telefono: "<<cliente->telefono<<endl;
    archivo<<endl;
    archivo<<"Cantidad";
    archivo<<"          ";
    archivo<<"Codigo de producto";
    archivo<<"      ";
    archivo<<"Nombre";
    archivo<<"      ";
    archivo<<"Precio por unidad";
    archivo<<"      ";
    archivo<<"Precio bruto";
    archivo<<"      ";
    archivo<<"Impuesto";
    archivo<<"      ";
    archivo<<"Total"<<endl;
    aux = listaSortear.primero;
    while (aux!=NULL){
        int precioBruto = 0;
        int precioEnGondola = 0;
        bool impuesto = false;
        float totalProducto = 0;
        float cobroImpuesto = 0;
        archivo<<aux->cantidad;
        archivo<<"                        ";
        archivo<<aux->codigo;
        archivo<<"              ";
        archivo<<aux->nombre+"             ";
        pnodoMarca aux2 = pInventario.primero;
        for (int i = 1;i<=pInventario.largoLista();aux2=aux2->siguiente,i++){
            if ((aux2->codigoPasillo==aux->codigoPasillo)&&(aux2->codigoProducto==aux->codigoProducto)&&(aux2->codigo==aux->codigo)){
                if (aux2->precio==1){
                    impuesto = true;
                }else{
                    impuesto = false;
                }
                break;
            }
        }
        pnodoPasillo aux3 = pPasillos.primero;
        for (int i2 = 1;i2<=pPasillos.largoLista();i2++,aux3=aux3->siguiente){
            if (aux->codigoPasillo==aux3->codigo){
                pnodoProducto aux4 = aux3->pproductos;
                int lim = cantidadNodosProducto(aux4);
                for (int i3 = 1;i3<=lim;i3++,aux4=aux4->siguiente){
                    if (aux4->codigo==aux->codigoProducto){
                        pnodoMarca aux5 = aux4->pmarcas;
                        int lim2 = cantidadNodosMarca(aux5);
                        for (int i4 = 1;i4<=lim2;i4++,aux5=aux5->siguiente){
                            if (aux5->codigo==aux->codigo){
                                precioEnGondola = aux5->precio;
                                aux4->ventasProducto+=aux->cantidad;
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
        precioBruto = aux->cantidad*precioEnGondola;
        if (impuesto){
            cobroImpuesto = precioBruto*0.13;
        }else{
            cobroImpuesto = precioBruto*0.01;
        }
        totalProducto = precioBruto+cobroImpuesto;
        totalPagar+=totalProducto;
        archivo<<precioEnGondola;
        archivo<<"               ";
        archivo<<precioBruto;
        archivo<<"             ";
        archivo<<cobroImpuesto;
        archivo<<"          ";
        archivo<<totalProducto<<endl;
        pnodoCompra aux8 = pListaVentas.primero;
        bool repet=false;
        while (aux8!=NULL){
            if ((aux8->codigoPasillo==aux->codigoPasillo)&&(aux8->codigoProducto==aux->codigoProducto)&&(aux8->codigo==aux->codigo)){
                repet = true;
                break;
            }
            aux8=aux8->siguiente;
        }
        if (repet){
            aux8->cantidad+=aux->cantidad;
        }else{
            pListaVentas.InsertarInicio(aux->codigoPasillo,aux->codigoProducto,aux->codigo,aux->nombre,aux->cantidad);
        }
        aux8 = pListaVentasI.primero;
        repet=false;
        while (aux8!=NULL){
            if ((aux8->codigoPasillo==aux->codigoPasillo)&&(aux8->codigoProducto==aux->codigoProducto)&&(aux8->codigo==aux->codigo)){
                repet = true;
                break;
            }
            aux8=aux8->siguiente;
        }
        if (repet){
            aux8->cantidad+=aux->cantidad;
        }else{
            pListaVentasI.InsertarInicio(aux->codigoPasillo,aux->codigoProducto,aux->codigo,aux->nombre,aux->cantidad);
        }
        aux8 = pListaVentasG.primero;
        repet=false;
        while (aux8!=NULL){
            if ((aux8->codigoPasillo==aux->codigoPasillo)&&(aux8->codigoProducto==aux->codigoProducto)&&(aux8->codigo==aux->codigo)){
                repet = true;
                break;
            }
            aux8=aux8->siguiente;
        }
        if (repet){
            aux8->cantidad+=aux->cantidad;
        }else{
            pListaVentasG.InsertarInicio(aux->codigoPasillo,aux->codigoProducto,aux->codigo,aux->nombre,aux->cantidad);
        }
        aux=aux->siguiente;
    }
    archivo<<endl;
    archivo<<"                                                                                               ";
    archivo<<"Total a pagar: ";
    archivo<<totalPagar<<endl<<endl<<endl;
    if (totalPagar>cliente->mayorFactura){
        cliente->mayorFactura=totalPagar;
    }
    if (cliente->menorFactura==0){
        cliente->menorFactura=totalPagar;
    }else{
        if (cliente->menorFactura<totalPagar){
            cliente->menorFactura=totalPagar;
        }
    }
    MergeSort(&(pListaVentas.primero));
    cliente->cantidadFacturas+=1;
    cout<<"Se ha atendido al cliente: "+cliente->nombre<<endl;
    archivo.close();
    return;
}

/*
Funcionamiento: Verifica, contra la lista de ventas, que todas las marcas tengan mas de 2 productos en gondola
Entrada: Pasillos a analizar pListaPasillos (listaPasillos), lista de ventas contra la cual buscar pListaVentasI (listaCompras),
inventario del cual tomar pInventario (listaMarcasInventario)
Salida: N/A
*/

//A continuacion se definen las funciones de los reportes, todas ellas devuelven un bool de repetecion y
//generan las facturas
void revisarGondola (listaCompras &pListaVentasG, listaPasillos &pListaPasillos, listaMarcasInventario &pInventario){
    if (pListaVentasG.ListaVacia()){
        cout<<"No se han facturado nuevos productos aun"<<endl;
        return;
    }
    pnodoCompra aux = pListaVentasG.primero;
    int lim = cantidadNodosCompra(aux);
    for (int i = 1;i<=lim;i++,aux=aux->siguiente){
        pnodoPasillo aux2 = pListaPasillos.primero;
        for (int i2=1;i2<=pListaPasillos.largoLista();i2++,aux2=aux2->siguiente){
            if (aux2->codigo==aux->codigoPasillo){
                pnodoProducto aux3 = aux2->pproductos;
                int lim2 = cantidadNodosProducto(aux3);
                for (int i3 = 1;i3<=lim2;i3++,aux3=aux3->siguiente){
                    if (aux3->codigo==aux->codigoProducto){
                        pnodoMarca aux4 = aux3->pmarcas;
                        int lim3 = cantidadNodosMarca(aux4);
                        for (int i4 = 1;i4<=lim3;i4++,aux4=aux4->siguiente){
                            if (aux4->codigo==aux->codigo){
                                if (aux4->cantidadGondola<=2){
                                    int recarga;
                                    string opcion;
                                    cout<<"Quedan ";
                                    cout<<aux4->cantidadGondola;
                                    cout<<" unidades en gondola de la marca "+aux4->nombre<<endl;
                                    while (true){
                                        cout<<"Digite la cantidad de existencias a tomar del inventario para colocar en gondola: ";
                                        cin>>opcion;
                                        if (esNumerico(opcion)==true){
                                            recarga=stoi (opcion);
                                            break;
                                        }else{
                                            cout<<"La cantidad de existencias a tomar debe ser un numero entero"<<endl;
                                        }
                                    }
                                    pnodoMarca aux5 = pInventario.primero;
                                    pnodoMarca aux6 = NULL;
                                    for (int i5 = 1;i5<=pInventario.largoLista();aux5=aux5->siguiente,i5++){
                                        if ((aux4->codigoPasillo==aux5->codigoPasillo)&&(aux4->codigoProducto==aux5->codigoProducto)&&(aux4->codigo==aux5->codigo)){
                                            aux6 = aux5;
                                            break;
                                        }
                                    }
                                    if (aux6!=NULL){
                                        if (aux6->cantidadGondola>=recarga){
                                            aux3->cantidadCargaGondola+=recarga;
                                            aux4->cantidadGondola+=recarga;
                                            aux6->cantidadGondola-=recarga;
                                            cout<<"Recarga completa"<<endl;
                                            break;
                                        }else{
                                            if (aux6->cantidadGondola==0){
                                                cout<<"No quedan existencias de esta marca en el inventario"<<endl;
                                                break;
                                            }else{
                                                string opcion2;
                                                cout<<"Solo quedan ";
                                                cout<<aux6->cantidadGondola;
                                                cout<<" existencias en inventario de esta marca"<<endl;
                                                cout<<"Digite 1 para mover dichas unidades a la gondola u otra tecla para salir: ";
                                                cin>>opcion2;
                                                if (opcion2=="1"){
                                                    aux3->cantidadCargaGondola+=aux6->cantidadGondola;
                                                    aux4->cantidadGondola+=aux6->cantidadGondola;
                                                    aux6->cantidadGondola=0;
                                                    cout<<"Recarga completa"<<endl;
                                                    break;
                                                }else{
                                                    break;
                                                }
                                            }
                                        }
                                    }else{
                                        cout<<"No se ha encontrado en el inventario la informacion correspondiente a esta marca"<<endl;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    pListaVentasG.primero=NULL;
    cout<<"Todas las gondolas han sido recargadas o no han sido vaciadas aun"<<endl;
    return;
}

//A continuacion se definen las funciones de los reportes, todas ellas devuelven un bool de repetecion y
//generan las facturas en un archivo de texto, el cual se abre al momento de la ejecucion
void reportePasilloMasVisitado (listaPasillos pListaPasillos){
    if (pListaPasillos.ListaVacia()){
        cout<<"No hay pasillos registrados aun";
        return;
    }
    int mayor;
    pnodoPasillo aux = pListaPasillos.primero;
    mayor = aux->cantidadVisitas;
    for (int i = 1;i<=pListaPasillos.largoLista();i++,aux=aux->siguiente){
        if (aux->cantidadVisitas>mayor){
            mayor = aux->cantidadVisitas;
        }
    }
    if (mayor==0){
        cout<<"No se ha visitado ningun pasillo aun"<<endl;
        return;
    }
    listaPasillos listaResultado;
    aux = pListaPasillos.primero;
    for (int i2 = 1;i2<=pListaPasillos.largoLista();i2++,aux=aux->siguiente){
        if (aux->cantidadVisitas == mayor){
            listaResultado.InsertarInicio(aux->codigo,aux->nombre);
        }
    }
    ofstream archivo ("PasilloMasVisitado.txt");
    archivo<<"Pasillo(s) mas visitado(s): "<<endl;
    aux = listaResultado.primero;
    for (int i3 = 1;i3<=listaResultado.largoLista();i3++,aux=aux->siguiente){
        archivo<<"-Codigo: ";
        archivo<<aux->codigo;
        archivo<<", Nombre de pasillo: "<<aux->nombre<<endl;
    }
    string nombreArchivo ="PasilloMasVisitado";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reportePasilloMenosVisitado (listaPasillos pListaPasillos){
    if (pListaPasillos.ListaVacia()){
        cout<<"No hay pasillos registrados aun";
        return;
    }
    int menor;
    pnodoPasillo aux = pListaPasillos.primero;
    menor = aux->cantidadVisitas;
    for (int i = 1;i<=pListaPasillos.largoLista();i++,aux=aux->siguiente){
        if (aux->cantidadVisitas<menor){
            menor = aux->cantidadVisitas;
        }
    }
    listaPasillos listaResultado;
    aux = pListaPasillos.primero;
    for (int i2 = 1;i2<=pListaPasillos.largoLista();i2++,aux=aux->siguiente){
        if (aux->cantidadVisitas == menor){
            listaResultado.InsertarInicio(aux->codigo,aux->nombre);
        }
    }
    ofstream archivo ("PasilloMenosVisitado.txt");
    archivo<<"Pasillo(s) menos visitado(s): "<<endl;
    aux = listaResultado.primero;
    for (int i3 = 1;i3<=listaResultado.largoLista();i3++,aux=aux->siguiente){
        archivo<<"-Codigo: ";
        archivo<<aux->codigo;
        archivo<<", Nombre de pasillo: "<<aux->nombre<<endl;
    }
    string nombreArchivo ="PasilloMenosVisitado";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteProductoPasilloMasVendido (listaPasillos pListaPasillos, listaCompras pListaVentas){
    if (pListaPasillos.ListaVacia()){
        cout<<"No hay pasillos registrados aun"<<endl;
        return;
    }
    if (pListaVentas.ListaVacia()){
        cout<<"No se han registrado ventas aun"<<endl;
        return;
    }
    int codigoPasillo;
    string codigoPasilloS;
    pListaPasillos.Mostrar();
    pnodoPasillo aux = pListaPasillos.primero;
    bool x = true;
    while (x){
        cout<<"Por favor digite el codigo del pasillo cuyo producto mas vendido desea conocer: ";
        cin>>codigoPasilloS;
        if(!esNumerico(codigoPasilloS)){
            cout<<"Debe digitar un codigo de pasillo valido"<<endl;
            continue;
        }
        codigoPasillo = stoi(codigoPasilloS);
        for (int i2 = 1;i2<=pListaPasillos.largoLista();i2++,aux=aux->siguiente){
            if (codigoPasillo==aux->codigo){
                x = false;
                break;
            }
        }
        if (x==false){
            break;
        }else{
            cout<<"Debe digitar un codigo de pasillo valido"<<endl;
        }
    }
    pnodoProducto aux2 = aux->pproductos;
    int mayor = 0;
    int lim = cantidadNodosProducto(aux2);
    for (int cont = 1;cont<=lim;cont++,aux2=aux2->siguiente){
        if (aux2->ventasProducto>mayor){
            mayor=aux2->ventasProducto;
        }
    }
    if (mayor==0){
        cout<<"Ningun producto de este pasillo tiene ventas registradas aun"<<endl;
        return;
    }
    listaProductos listaResultado;
    aux2 = aux->pproductos;
    lim = cantidadNodosProducto(aux2);
    for (int cont = 1;cont<=lim;cont++,aux2=aux2->siguiente){
        if (aux2->ventasProducto==mayor){
            listaResultado.InsertarFinal(aux2->codigoPasillo,aux2->codigo,aux2->nombre);
        }
    }
    ofstream archivo ("ProductoEnPasilloMasVendido.txt");
    archivo<<"Producto(s) mas vendido(s): "<<endl;
    aux2 = listaResultado.primero;
    for (int i3 = 1;i3<=listaResultado.largoLista();i3++,aux2=aux2->siguiente){
        archivo<<"-Codigo: ";
        archivo<<aux2->codigo;
        archivo<<", Nombre de producto: "<<aux2->nombre<<endl;
    }
    string nombreArchivo ="ProductoEnPasilloMasVendido";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteMarcasMasVendidas (listaCompras pListaVentas){
    if (pListaVentas.ListaVacia()){
        cout<<"No se han registrado ventas aun"<<endl;
        return;
    }
    pListaVentas.Mostrar();
    pnodoCompra aux = pListaVentas.primero;
    int lim = cantidadNodosCompra(aux);
    int mayor = 0;
    for (int i = 1;i<=lim;i++,aux=aux->siguiente){
        if (aux->cantidad>mayor){
            mayor = aux->cantidad;
        }
    }
    listaCompras listaResultado;
    aux = pListaVentas.primero;
    for (int i2 = 1;i2<=lim;i2++,aux=aux->siguiente){
        if (aux->cantidad == mayor){
            listaResultado.InsertarInicio(aux->codigoPasillo,aux->codigoProducto,aux->codigo,aux->nombre,aux->cantidad);
        }
    }
    ofstream archivo ("MarcaMasComprada.txt");
    archivo<<"Marca(s) mas comprada(s): "<<endl;
    aux = listaResultado.primero;
    int lim2 = cantidadNodosCompra(aux);
    for (int i3 = 1;i3<=lim2;i3++,aux=aux->siguiente){
        archivo<<"-Codigo de Pasillo: ";
        archivo<<aux->codigoPasillo;
        archivo<<", Codigo de Producto: ";
        archivo<<aux->codigoProducto;
        archivo<<" Codigo de Marca: ";
        archivo<<aux->codigo;
        archivo<<", Nombre de la marca: "<<aux->nombre<<endl;
    }
    string nombreArchivo ="MarcaMasComprada";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteClienteQueMasCompro (listaClientes pListaClientes, listaCompras pListaVentas){
    if (pListaVentas.ListaVacia()){
        cout<<"No se ha facturado a ningun cliente aun"<<endl;
        return;
    }
    int mayor;
    pnodoCliente aux = pListaClientes.primero;
    mayor = aux->mayorFactura;
    for (int i = 1;i<=pListaClientes.largoLista();i++,aux=aux->siguiente){
        if (aux->mayorFactura>mayor){
            mayor = aux->mayorFactura;
        }
    }
    if (mayor==0){
        cout<<"Ningun cliente ha facturado aun"<<endl;
        return;
    }
    listaClientes listaResultado;
    aux = pListaClientes.primero;
    for (int i2 = 1;i2<=pListaClientes.largoLista();i2++,aux=aux->siguiente){
        if (aux->mayorFactura == mayor){
            listaResultado.InsertarInicio(aux->cedula,aux->nombre,aux->telefono,aux->correo);
        }
    }
    ofstream archivo ("ClienteQueMasCompro.txt");
    archivo<<"Cliente(s) que mas compraron(s): "<<endl;
    aux = listaResultado.primero;
    for (int i3 = 1;i3<=listaResultado.largoLista();i3++,aux=aux->siguiente){
        archivo<<"-Cedula: ";
        archivo<<aux->cedula;
        archivo<<", Nombre del cliente: "<<aux->nombre<<endl;
    }
    string nombreArchivo ="ClienteQueMasCompro";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteClienteQueMenosCompro (listaClientes pListaClientes, listaCompras pListaVentas){
    if (pListaVentas.ListaVacia()){
        cout<<"No se ha facturado ningun cliente aun"<<endl;
        return;
    }
    int menor = 0;
    pnodoCliente aux = pListaClientes.primero;
    menor = aux->menorFactura;
    for (int i = 1;i<=pListaClientes.largoLista();i++,aux=aux->siguiente){
        if (aux->menorFactura<menor){
            menor = aux->menorFactura;
        }
    }
    listaClientes listaResultado;
    aux = pListaClientes.primero;
    for (int i2 = 1;i2<=pListaClientes.largoLista();i2++,aux=aux->siguiente){
        if (aux->menorFactura == menor){
            listaResultado.InsertarInicio(aux->cedula,aux->nombre,aux->telefono,aux->correo);
        }
    }
    ofstream archivo ("ClienteQueMenosCompro.txt");
    archivo<<"Cliente(s) que menos compraron(s): "<<endl;
    aux = listaResultado.primero;
    for (int i3 = 1;i3<=listaResultado.largoLista();i3++,aux=aux->siguiente){
        archivo<<"-Cedula: ";
        archivo<<aux->cedula;
        archivo<<", Nombre del cliente: "<<aux->nombre<<endl;
    }
    string nombreArchivo ="ClienteQueMenosCompro";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteProductoGondola (listaPasillos pListaPasillos){
    int mayor = 0;
    pnodoPasillo aux2 = pListaPasillos.primero;
    for (int i2=1;i2<=pListaPasillos.largoLista();i2++,aux2=aux2->siguiente){
        pnodoProducto aux3 = aux2->pproductos;
        int lim2 = cantidadNodosProducto(aux3);
        for (int i3 = 1;i3<=lim2;i3++,aux3=aux3->siguiente){
            if (aux3->cantidadCargaGondola>mayor){
                mayor=aux3->cantidadCargaGondola;
            }
        }
    }
    if (mayor==0){
        cout<<"Ninguna gondola ha sido cargada aun"<<endl;
        return;
    }
    listaProductos listaResultado;
    aux2 = pListaPasillos.primero;
    for (int i2=1;i2<=pListaPasillos.largoLista();i2++,aux2=aux2->siguiente){
        pnodoProducto aux3 = aux2->pproductos;
        int lim2 = cantidadNodosProducto(aux3);
        for (int i3 = 1;i3<=lim2;i3++,aux3=aux3->siguiente){
            if (aux3->cantidadCargaGondola==mayor){
                listaResultado.InsertarInicio(aux3->codigoPasillo,aux3->codigo,aux3->nombre);
            }
        }
    }
    ofstream archivo ("ProductoMasRecargado.txt");
    archivo<<"Producto(s) mas recargados(s): "<<endl;
    pnodoProducto aux3 = listaResultado.primero;
    for (int i3 = 1;i3<=listaResultado.largoLista();i3++,aux3=aux3->siguiente){
        archivo<<"-Codigo: ";
        archivo<<aux3->codigo;
        archivo<<", Nombre de producto: "<<aux3->nombre<<endl;
    }
    string nombreArchivo ="ProductoMasRecargado";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteClienteMasFacturas (listaClientes pListaClientes, listaCompras pListaVentas){
    if (pListaVentas.ListaVacia()){
        cout<<"No se ha facturado a ningun cliente aun"<<endl;
        return;
    }
    int mayor;
    pnodoCliente aux = pListaClientes.primero;
    mayor = aux->cantidadFacturas;
    for (int i = 1;i<=pListaClientes.largoLista();i++,aux=aux->siguiente){
        if (aux->cantidadFacturas>mayor){
            mayor = aux->cantidadFacturas;
        }
    }
    if (mayor==0){
        cout<<"Ningun cliente ha facturado aun"<<endl;
        return;
    }
    listaClientes listaResultado;
    aux = pListaClientes.primero;
    for (int i2 = 1;i2<=pListaClientes.largoLista();i2++,aux=aux->siguiente){
        if (aux->cantidadFacturas == mayor){
            listaResultado.InsertarInicio(aux->cedula,aux->nombre,aux->telefono,aux->correo);
        }
    }
    ofstream archivo ("ClienteConMasFacturas.txt");
    archivo<<"Cliente(s) con mayor cantidad de facturas: "<<endl;
    aux = listaResultado.primero;
    for (int i3 = 1;i3<=listaResultado.largoLista();i3++,aux=aux->siguiente){
        archivo<<"-Cedula: ";
        archivo<<aux->cedula;
        archivo<<", Nombre del cliente: "<<aux->nombre<<endl;
    }
    string nombreArchivo ="ClienteConMasFacturas";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteMarcasProducto (listaPasillos pListaPasillos){
    if (pListaPasillos.ListaVacia()){
        cout<<"No hay pasillos registrados aun"<<endl;
        return;
    }
    int codigoPasillo;
    string codigoPasilloS;
    pListaPasillos.Mostrar();
    pnodoPasillo aux = pListaPasillos.primero;
    bool x = true;
    while (x){
        cout<<"Por favor digite el codigo del pasillo en el cual se encuentra el producto cuyas marcas desea conocer: ";
        cin>>codigoPasilloS;
        if(!esNumerico(codigoPasilloS)){
            cout<<"Debe digitar un codigo de pasillo valido"<<endl;
            continue;
        }
        codigoPasillo = stoi(codigoPasilloS);
        for (int i2 = 1;i2<=pListaPasillos.largoLista();i2++,aux=aux->siguiente){
            if (codigoPasillo==aux->codigo){
                x = false;
                break;
            }
        }
        if (x==false){
            break;
        }else{
            cout<<"Debe digitar un codigo de pasillo valido"<<endl;
        }
    }
    pnodoProducto aux2 = aux->pproductos;
    mostrarNodosProductoCodigo(aux2);
    int codigoProducto;
    string codigoProductoS;
    bool x2 = true;
    int lim = cantidadNodosProducto(aux2);
    while (x2){
        cout<<"Por favor digite el codigo del producto cuyas marcas desea conocer desea conocer: ";
        cin>>codigoProductoS;
        if(!esNumerico(codigoProductoS)){
            cout<<"Debe digitar un codigo de producto valido"<<endl;
            continue;
        }
        codigoProducto = stoi(codigoProductoS);
        for (int i2 = 1;i2<=lim;i2++,aux2=aux2->siguiente){
            if (codigoProducto==aux2->codigo){
                x2 = false;
                break;
            }
        }
        if (x2==false){
            break;
        }else{
            cout<<"Debe digitar un codigo de producto valido"<<endl;
        }
    }
    ofstream archivo ("MarcasDeProducto.txt");
    archivo<<"Marca(s) del producto "+aux2->nombre<<endl;
    pnodoMarca aux3 = aux2->pmarcas;
    int lim2 = cantidadNodosMarca(aux3);
    for (int i3 = 1;i3<=lim2;i3++,aux3=aux3->siguiente){
        archivo<<"-Codigo: ";
        archivo<<aux3->codigo;
        archivo<<", Nombre del marca: "<<aux3->nombre<<endl;
    }
    string nombreArchivo ="MarcasDeProducto";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteFacturaMayor (listaClientes pListaClientes, listaCompras pListaVentas){
    if (pListaVentas.ListaVacia()){
        cout<<"No se ha facturado a ningun cliente aun"<<endl;
        return;
    }
    int mayor;
    pnodoCliente aux = pListaClientes.primero;
    mayor = aux->mayorFactura;
    for (int i = 1;i<=pListaClientes.largoLista();i++,aux=aux->siguiente){
        if (aux->mayorFactura>mayor){
            mayor = aux->mayorFactura;
        }
    }
    if (mayor==0){
        cout<<"Ningun cliente ha facturado aun"<<endl;
        return;
    }
    listaClientes listaResultado;
    aux = pListaClientes.primero;
    for (int i2 = 1;i2<=pListaClientes.largoLista();i2++,aux=aux->siguiente){
        if (aux->mayorFactura == mayor){
            listaResultado.InsertarInicio(aux->cedula,aux->nombre,aux->telefono,aux->correo);
        }
    }
    ofstream archivo ("FacturaMayor.txt");
    archivo<<"Cliente(s) con la(s) factura(s) de mayor monto: "<<endl;
    aux = listaResultado.primero;
    for (int i3 = 1;i3<=listaResultado.largoLista();i3++,aux=aux->siguiente){
        archivo<<"-Cedula: ";
        archivo<<aux->cedula;
        archivo<<", Nombre del cliente: "<<aux->nombre<<endl;
    }
    string nombreArchivo ="FacturaMayor";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteProductoPasillo (listaPasillos pListaPasillos){
    if (pListaPasillos.ListaVacia()){
        cout<<"No hay pasillos registrados aun"<<endl;
        return;
    }
    int codigoPasillo;
    string codigoPasilloS;
    pListaPasillos.Mostrar();
    pnodoPasillo aux = pListaPasillos.primero;
    bool x = true;
    while (x){
        cout<<"Por favor digite el codigo del pasillo cuyos productos desea ver: ";
        cin>>codigoPasilloS;
        if(!esNumerico(codigoPasilloS)){
            cout<<"Debe digitar un codigo de pasillo valido"<<endl;
            continue;
        }
        codigoPasillo = stoi(codigoPasilloS);
        for (int i2 = 1;i2<=pListaPasillos.largoLista();i2++,aux=aux->siguiente){
            if (codigoPasillo==aux->codigo){
                x = false;
                break;
            }
        }
        if (x==false){
            break;
        }else{
            cout<<"Debe digitar un codigo de pasillo valido"<<endl;
        }
    }
    pnodoProducto aux2 = aux->pproductos;
    int lim2 = cantidadNodosProducto(aux2);
    ofstream archivo ("ProductosDePasillo.txt");
    archivo<<"Productos del pasillo: "+aux->nombre<<endl;
    for (int i3 = 1;i3<=lim2;i3++,aux2=aux2->siguiente){
        archivo<<"-Codigo: ";
        archivo<<aux2->codigo;
        archivo<<", Nombre de producto: "<<aux2->nombre<<endl;
    }
    string nombreArchivo ="ProductosDePasillo";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteClientes (listaClientes pListaClientes){
    if (pListaClientes.ListaVacia()){
        cout<<"No se han registrado clientes aun"<<endl;
        return;
    }
    ofstream archivo ("reporteClientes.txt");
    archivo<<"Cliente(s) del supermercado: "<<endl;
    pnodoCliente aux = pListaClientes.primero;
    for (int i3 = 1;i3<=pListaClientes.largoLista();i3++,aux=aux->siguiente){
        archivo<<"-Cedula: ";
        archivo<<aux->cedula;
        archivo<<", Nombre del cliente: "<<aux->nombre;
        archivo<<", Telefono: "<<aux->telefono;
        archivo<<", Correo: "<<aux->correo<<endl;
    }
    string nombreArchivo ="reporteClientes";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reportePasillos (listaPasillos pListaPasillos){
    if (pListaPasillos.ListaVacia()){
        cout<<"No hay pasillos registrados aun";
        return;
    }
    ofstream archivo ("reportePasillos.txt");
    archivo<<"Pasillo(s) del supermercado: "<<endl;
    pnodoPasillo aux = pListaPasillos.primero;
    for (int i3 = 1;i3<=pListaPasillos.largoLista();i3++,aux=aux->siguiente){
        archivo<<"-Codigo: ";
        archivo<<aux->codigo;
        archivo<<", Nombre de pasillo: "<<aux->nombre<<endl;
    }
    string nombreArchivo ="reportePasillos";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void reporteInventario (listaMarcasInventario pInventario){
    if (pInventario.ListaVacia()){
        cout<<"No hay datos disponibles sobre el inventario";
        return;
    }
    ofstream archivo ("reporteInventario.txt");
    archivo<<"Inventario del supermercado: "<<endl;
    pnodoMarca aux = pInventario.primero;
    for (int i3 = 1;i3<=pInventario.largoLista();i3++,aux=aux->siguiente){
        archivo<<"-Codigo de pasillo: ";
        archivo<<aux->codigoPasillo;
        archivo<<", Codigo de producto: ";
        archivo<<aux->codigoProducto;
        archivo<<", Codigo de marca: ";
        archivo<<aux->codigo;
        archivo<<", Nombre de marca: "<<aux->nombre;
        archivo<<", Cantidad en stock: ";
        archivo<<aux->cantidadGondola<<endl;
    }
    string nombreArchivo ="reporteInventario";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

//A continuacion se definen las funciones de los menus, ambas llaman a las demas funciones descritas y mantienen el ciclo de entradas
//de ser necesario. Además, permiten el paso de parametros por referencia a las funciones que asi lo requieren
int menuReportes (listaClientes pListaClientes, listaPasillos pListaPasillos, listaMarcasInventario pInventario, listaCompras pListaVentas){
    int opcion;
    string opcionS;
    cout<<"*****************Reportes******************"<<endl;
    cout<<"1-Pasillo mas visitado"<<endl;
    cout<<"2-Pasillo menos visitado"<<endl;
    cout<<"3-Productos en pasillo mas vendidos"<<endl;
    cout<<"4-Marca mas vendida"<<endl;
    cout<<"5-Cliente que mas compro"<<endl;
    cout<<"6-Cliente que menos compro"<<endl;
    cout<<"7-Producto que mas se cargo en gondolas"<<endl;
    cout<<"8-Cliente que mas facturo"<<endl;
    cout<<"9-Marcas de un producto"<<endl;
    cout<<"10-Factura de mayor monto"<<endl;
    cout<<"11-Productos en un pasillo"<<endl;
    cout<<"12-Clientes del supermercado"<<endl;
    cout<<"13-Pasillos del supermercado"<<endl;
    cout<<"14-Inventario del supermercado"<<endl;
    cout<<"15-Volver al menu principal"<<endl;
    cout<<"Digite el numero de la opcion deseada: ";
    cin>> opcionS;
    if (!esNumerico(opcionS)){
        cout<<"La opcion digitada es invalida"<<endl;
        return 0;
    }
    opcion = stoi (opcionS);
    switch (opcion){
        case 1: reportePasilloMasVisitado(pListaPasillos);
        break;
        case 2: reportePasilloMenosVisitado(pListaPasillos);
        break;
        case 3: reporteProductoPasilloMasVendido(pListaPasillos,pListaVentas);
        break;
        case 4: reporteMarcasMasVendidas(pListaVentas);
        break;
        case 5: reporteClienteQueMasCompro(pListaClientes,pListaVentas);
        break;
        case 6: reporteClienteQueMenosCompro(pListaClientes,pListaVentas);
        break;
        case 7: reporteProductoGondola(pListaPasillos);
        break;
        case 8: reporteClienteMasFacturas(pListaClientes, pListaVentas);
        break;
        case 9: reporteMarcasProducto(pListaPasillos);
        break;
        case 10: reporteFacturaMayor(pListaClientes,pListaVentas);
        break;
        case 11: reporteProductoPasillo(pListaPasillos);
        break;
        case 12: reporteClientes(pListaClientes);
        break;
        case 13: reportePasillos(pListaPasillos);
        break;
        case 14: reporteInventario(pInventario);
        break;
        case 15: return 1;
        break;
        default:
            cout<<"La opcion escogida es invalida"<<endl;
        break;
    }
    return 0;
}

int menu (listaClientes &pListaClientes, listaPasillos &pListaPasillos, colaClientes &pColaFacturacion,
          listaMarcasInventario &pInventario, listaCompras &pListaVentas, listaCompras &pListaVentasI, listaCompras &pListaVentasG){
    int opcion;
    string opcionS;
    cout<<"*****************Tarea Programada 1: Supermercado******************"<<endl;
    cout<<"1-Comprar"<<endl;
    cout<<"2-Facturar"<<endl;
    cout<<"3-Revisar Gondolas"<<endl;
    cout<<"4-Revisar Inventario"<<endl;
    cout<<"5-Reportes"<<endl;
    cout<<"6-Salir"<<endl;
    cout<<"Digite el numero de la opcion deseada: ";
    cin>> opcionS;
    if (!esNumerico(opcionS)){
        cout<<"La opcion digitada es invalida"<<endl;
        return 0;
    }
    opcion = stoi (opcionS);
    switch (opcion){
        case 1: AuxComprarCliente(pListaPasillos, pListaClientes, pColaFacturacion);
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:{ int x = 0;
        while (x!=1){

        }
        break;
        }
        case 6: return 1;
        break;
        default:
            cout<<"La opcion escogida es invalida"<<endl;
        break;
    }
    return 0;
}
