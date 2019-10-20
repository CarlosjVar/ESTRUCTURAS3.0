#include "menu.h"
#include "mycliente.h"

bool esNumerico (string pstring){
    int lim = pstring.length();
    for (int i = 0;i<lim;i++){
        char temp = pstring[i];
        if(!isdigit(temp)){
            return false;
        }
    }
    return true;
}



Menu::Menu(QObject*parent)
{
    connect(this,SIGNAL(enviart(qintptr* ,QByteArray )),&servidor,SLOT(facturaV(qintptr* ,QByteArray )));
    connect(this,SIGNAL(blockAll()),&servidor,SLOT(blockall()));
    connect(this,SIGNAL(unBlockAll()),&servidor,SLOT(unblockall()));
}
void Menu::menu()
//In:Binario B1mercado,inventario inventario,listaClientes clientes
//Out:None
//Funci�n: Men� que funciona como nexo principal entre todas las funcionalidades
{

    cout<<"***************Sistema de gestion del supermercado****************"<<endl;
    cout<<"1. Facturar"<<endl;
    cout<<"2. Revisar Gondolas"<<endl;
    cout<<"3. Verificar Inventario"<<endl;
    cout<<"4. Generacion de reportes"<<endl;
    cout<<"5. Ingresar nuevos datos"<<endl;
    cout<<"6. Modificar datos"<<endl;
    cout<<"7. Consultas"<<endl;
    cout<<"0. Salir del programa"<<endl;
    cout<<"Digite la opcion deseada: ";
    string opcionS;
    int opcion;
    cin>>opcionS;
    if(!esNumerico(opcionS))
    {
        cout<<"Opcion invalida"<<endl;
        menu();
        return;
    }
    opcion = stoi (opcionS);
    if (opcion==1)
        if(colaclientes.ColaVacia())
        {
            cout<<"La cola de clientes esta vacia"<<endl;
        }
        else
        {
            FacturarCliente();
        }

    else if(opcion==2)
    {
        emit blockAll();
        supermercado.rellenarGondolaBinario(inventario);
        cout<<"No hay gondolas que requieran rellenado, o no quedan gondolas por rellenar"<<endl;
        emit unBlockAll();
    }
    else if (opcion==3)
    {
        inventario.rellenarInventario();
        cout<<"Ya se han verificado las reservas de todas las marcas"<<endl;
    }
    else if(opcion==4)
    {
        while (menuReportes()!=1);
    }
    else if(opcion==5)
    {
        emit blockAll();
        menuAgregar();
        emit unBlockAll();
    }
    else if(opcion==6)
    {
        emit blockAll();
        menuModificar();
        emit unBlockAll();
    }
    else if(opcion==7)
    {
       emit blockAll();
       menuConsultar();
       emit unBlockAll();
    }
    else if(opcion==0)
    {
        return;
    }
    else
    {
        cout<<"Opcion invalida"<<endl;
        menu();
        return;
    }
   menu();
   return ;
}


void Menu::menuAgregar(){
    cout<<"*****************Agregar datos******************"<<endl;
    cout<<"1. Agregar pasillo"<<endl;
    cout<<"2. Agregar producto"<<endl;
    cout<<"3. Agregar marca"<<endl;
    cout<<"4. Agregar cliente"<<endl;
    cout<<"0. Volver al menu de administrador"<<endl;
    cout<<"Seleccione el dato que desea agregar: ";
    string opcionS;
    int opcion;
    cin>>opcionS;
    if(!esNumerico(opcionS))
    {
        cout<<"Opcion invalida"<<endl;
        menuAgregar();
        return;
    }
    opcion = stoi (opcionS);
    if (opcion==1)
        agregarPasillo();
    else if(opcion==2)
    {
        agregarProducto();
    }
    else if (opcion==3)
    {
        agregarMarca();
    }
    else if(opcion==4)
    {
        agregarCliente();
    }
    else if(opcion==0)
    {
       return;
    }
    else
    {
        cout<<"Opcion invalida"<<endl;
        menuAgregar();
        return;
    }
    menuAgregar();
    return;
}

void Menu::agregarPasillo(){
    int codigo;
    string nombre;
    cout<<"Ingrese el codigo del nuevo pasillo, o un cero para volver: ";
    cin>>codigo;
    if(cin.fail())
    {
        cout<<"Codigo invalido"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else
    {
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigo);
        if (codigo==0){
            return;
        }
        if (aux == NULL){
            cout<<"Ingrese el nombre del nuevo pasillo: ";
            cin>>nombre;
            if (nombre!=""){
                supermercado.InsertaNodo(codigo,nombre);
                 cout<<"Pasillo creado"<<endl;
            }else{
                cout<<"El nombre del pasillo no puede estar vacio"<<endl;
            }
        }else{
            cout<<"Ya existe un pasillo con el codigo ingresado"<<endl;
        }
    }
    return;
}

void Menu::agregarProducto(){
    int codigoPasillo;
    int codigo;
    string nombre;
    cout<<"Ingrese el codigo del pasillo al cual le desea agregar un producto, o un cero para volver: ";
    cin>>codigoPasillo;
    if(cin.fail())
    {
        cout<<"Codigo invalido"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else{
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
        cout<<"Ha seleccionado el pasillo: "<<aux->nombre<<endl;
        if (codigoPasillo==0){
            return;
        }
        if (aux != NULL){
            cout<<"Ingrese el codigo del nuevo producto: ";
            cin>>codigo;
            if(cin.fail())
            {
                cout<<"Codigo invalido"<<endl;
                return;
            }
            else
            {
                pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigo);
                if (aux2==NULL){
                    cout<<"Ingrese el nombre del nuevo producto: ";
                    cin>>nombre;
                    if (nombre!=""){
                         BinarioAVL temp = BinarioAVL();
                         temp.raiz = aux->productos;
                         temp.InsertarBalanceado(temp.raiz,temp.Hh,codigo,nombre);
                         aux->productos = temp.raiz;
                         cout<<"Producto ingresado"<<endl;
                    }
                    else
                    {
                        cout<<"El nombre del producto no puede estar vacio"<<endl;
                    }
                }
                else
                {
                    cout<<"Ya existe un producto con el codigo ingresado"<<endl;
                }
           }
        }
        else{
            cout<<"No existen pasillos con el codigo ingresado"<<endl;
        }
    }
}

void Menu::agregarMarca(){
    int codigoPasillo;
    int codigoProducto;
    int codigo;
    int precio;
    int cantidadEnGondola;
    string nombre;
    cout<<"Ingrese el codigo del pasillo en el cual desea agregar una marca, o un cero para volver: ";
    cin>>codigoPasillo;
    if(cin.fail())
    {
        cout<<"Codigo invalido"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else
    {
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
        if (codigoPasillo==0){
            return;
        }
        if (aux != NULL){
            cout<<"Ha seleccionado el pasillo: "<<aux->nombre<<endl;
            cout<<"Ingrese el codigo del producto en el cual desea agregar una marca, o un cero para volver: ";
            cin>>codigoProducto;
            if(cin.fail())
            {
                cout<<"Codigo invalido"<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
            else{
                pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigoProducto);
                if (codigoProducto==0){
                    return;
                }
                if (aux2!=NULL){
                    cout<<"Ha seleccionado el producto: "<<aux2->nombre<<endl;
                    cout<<"Ingrese el codigo de la nueva marca: ";
                    cin>>codigo;
                    if(cin.fail())
                    {
                        cout<<"Codigo invalido"<<endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                        return;
                    }
                        RBTree temp = RBTree (aux2->marcas);
                        NodePtr aux3 = temp.searchTree(codigo);
                        if (aux3 == NULL){
                            cout<<"Ingrese le nombre de la nueva marca: ";
                            while (true){
                                cin>>nombre;
                                if (nombre!=""){
                                    break;
                                }else{
                                    cout<<"El nombre de la marca no puede estar vacio, favor reingresarlo: ";
                                }
                            }
                            cout<<"Ingrese el precio de la nueva marca: ";
                            while (true){
                                cin>>precio;
                                if(cin.fail())
                                {
                                    cout<<"Precio invalido, favor reingresar: "<<endl;
                                    cin.clear();
                                    cin.ignore(256,'\n');
                                }
                                else{
                                    break;
                                }

                            }
                            cout<<"Ingrese la cantidad de existencias en gondola de la nueva marca: ";
                            while (true){
                                cin>>cantidadEnGondola;
                                if(cin.fail())
                                {
                                    cout<<"cantoidad invalida, favor reingresar: "<<endl;
                                    cin.clear();
                                    cin.ignore(256,'\n');
                                }
                                else{
                                    break;
                                }
                            }
                            RBTree temp = RBTree(aux2->marcas);
                            temp.insert(codigo,nombre,precio,cantidadEnGondola);
                            aux2->marcas = temp.getRoot();
                            cout<<"Marca agregada"<<endl;
                    }
                    else{
                        cout<<"Ya existe una marca con el codigo ingresado"<<endl;
                    }
                }
                else
                {
                    cout<<"No existen productos con el codigo ingresado"<<endl;
                }
            }
        }
        else
        {
            cout<<"No existen pasillos con el codigo ingresado"<<endl;
        }
    }
}

void Menu::agregarCliente(){
    string cedulaS;
    int cedula;
    string nombre;
    string telefono;
    string codigoCiudad;
    string correo;
    cout<<"Ingrese el numero de cedula del nuevo cliente, o un cero para voler: ";
    cin>>cedulaS;
    if (cedulaS == "0"){
         return;
    }
    cedula = stoi (cedulaS);
    int k;
    Pagina* aux = clientes.buscar(cedula,k);
    if (aux==NULL){
        cout<<"Ingrese el nombre del cliente: ";
        cin>>nombre;
        cout<<"Ingrese el correo electronico del cliente: ";
        cin>>correo;
        cout<<"Ingrese el codigo de la ciudad del cliente: ";
        cin>>codigoCiudad;
        cout<<"Ingrese el telefono del cliente: ";
        cin>>telefono;
        clientes.insertar(cedula,nombre,telefono,codigoCiudad,correo);
        cout<<"Cliente agregado"<<endl;
        return;

    }else{
        cout<<"Ya hay un cliente registrado con dicha cedula"<<endl;
    }
}


void Menu::menuModificar(){
    cout<<"*****************Modificacion de datos******************"<<endl;
    cout<<"1. Modificar precio"<<endl;
    cout<<"2. Modificar impuesto"<<endl;
    cout<<"3. Modificar pertenencia a la canasta"<<endl;
    cout<<"0. Volver al menu de administrador"<<endl;
    cout<<"Seleccione el dato que desea modificar: ";
    string opcionS;
    int opcion;
    cin>>opcionS;
    if(!esNumerico(opcionS))
    {
        cout<<"Opcion invalida"<<endl;
        menuModificar();
        return;
    }
    opcion = stoi (opcionS);
    if (opcion==1)
        modificarPrecio ();
    else if(opcion==2)
    {
        modificarImpuesto ();
    }
    else if (opcion==3)
    {
        modificarPertenencia();
    }
    else if(opcion==0)
    {
       return;
    }
    else
    {
        cout<<"Opcion invalida"<<endl;
        menuModificar();
        return;
    }
    menuModificar();
    return;
}

void Menu::modificarPrecio(){
    int codigoPasillo;
    int codigoProducto;
    int codigo;
    int precio;
    cout<<"Ingrese el codigo del pasillo en el cual esta la marca cuyo precio desea cambiar, o un cero para volver: ";
    cin>>codigoPasillo;
    if(cin.fail())
    {
        cout<<"Codigo invalido"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else
    {
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
        if (codigoPasillo==0){
            return;
        }
        if (aux != NULL){
            cout<<"Ha seleccionado el pasillo: "<<aux->nombre<<endl;
            cout<<"Ingrese el codigo del producto en el cual esta la marca cuyo precio desea cambiar, o un cero para volver: ";
            cin>>codigoProducto;
            if(cin.fail())
            {
                cout<<"Codigo invalido"<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
            else{
                pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigoProducto);
                if (codigoProducto==0){
                    return;
                }
                if (aux2!=NULL){
                    cout<<"Ha seleccionado el producto: "<<aux2->nombre<<endl;
                    cout<<"Ingrese el codigo de la marca cuyo precio desea cambiar, o un cero para volver: ";
                    cin>>codigo;
                    if(cin.fail())
                    {
                        cout<<"Codigo invalido"<<endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                    }
                    else{
                        if (codigo==0){
                            return;
                        }
                        RBTree temp = RBTree (aux2->marcas);
                        NodePtr aux3 = temp.searchTree(codigo);
                        if (aux3!=NULL){
                            cout<<"Ha seleccionado la marca: "<<aux3->nombre<<endl;
                            cout<<"Ingrese el nuevo precio de esta marca: ";
                            cin>>precio;
                            if(cin.fail())
                            {
                                cout<<"Precio invalido"<<endl;
                                cin.clear();
                                cin.ignore(256,'\n');
                            }
                            else{
                                aux3->precio = precio;
                                cout<<"Precio modificado"<<endl;
                            }
                        }
                        else
                        {
                            cout<<"No existen marcas con el codigo ingresado"<<endl;
                        }
                    }
                }
                else
                {
                    cout<<"No existen productos con el codigo ingresado"<<endl;
                }
            }
        }
        else
        {
            cout<<"No existen pasillos con el codigo ingresado"<<endl;
        }
    }
}

void Menu::modificarImpuesto(){
    int codigoPasillo;
    int codigoProducto;
    int codigoMarca;
    int codigoI;
    string codigoIS;
    float impuesto;
    cout<<"Ingrese el codigo del pasillo en el cual esta la marca cuyo impuesto desea cambiar, o un cero para volver: ";
    cin>>codigoPasillo;
    if(cin.fail())
    {
        cout<<"Codigo invalido"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else
    {
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
        if (codigoPasillo==0){
            return;
        }
        if (aux != NULL){
            cout<<"Ha seleccionado el pasillo: "<<aux->nombre<<endl;
            cout<<"Ingrese el codigo del producto en el cual esta la marca cuyo impuesto desea cambiar, o un cero para volver: ";
            cin>>codigoProducto;
            if(cin.fail())
            {
                cout<<"Codigo invalido"<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
            else{
                pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigoProducto);
                if (codigoProducto==0){
                    return;
                }
                if (aux2!=NULL){
                    cout<<"Ha seleccionado el producto: "<<aux2->nombre<<endl;
                    cout<<"Ingrese el codigo de la marca cuyo precio desea cambiar, o un cero para volver: ";
                    cin>>codigoMarca;
                    if(cin.fail())
                    {
                        cout<<"Codigo invalido"<<endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                    }
                    else{
                        if (codigoMarca==0){
                            return;
                        }
                        codigoIS = to_string(codigoPasillo) + to_string(codigoProducto) + to_string(codigoMarca);
                        codigoI = stoi (codigoIS);
                        pnodoAA aux3 = inventario.buscarNodoAA(codigoI);
                        if (aux3!=NULL){
                            cout<<"Ha seleccionado la marca: "<<aux3->nombre<<", la cual tiene un impuesto de: "<<aux3->impuesto<<endl;
                            cout<<"Ingrese el nuevo impuesto: "<<endl;
                            cin>>impuesto;
                            if(cin.fail())
                            {
                                cout<<"Impuesto invalido"<<endl;
                                cin.clear();
                                cin.ignore(256,'\n');
                                return;
                            }
                            aux3->impuesto = impuesto;
                            cout<<"Impuesto modificado"<<endl;
                        }else{
                            cout<<"No se encontro la marca ingresada en el inventario"<<endl;
                        }
                    }
                }
                else
                {
                    cout<<"No existen productos con el codigo ingresado"<<endl;
                }
            }
        }
        else
        {
            cout<<"No existen pasillos con el codigo ingresado"<<endl;
        }
    }
}

void Menu::modificarPertenencia(){
    int codigoPasillo;
    int codigoProducto;
    int codigoMarca;
    int codigoI;
    string codigoIS;
    int canasta;
    cout<<"Ingrese el codigo del pasillo en el cual esta la marca cuya pertenencia desea cambiar, o un cero para volver: ";
    cin>>codigoPasillo;
    if(cin.fail())
    {
        cout<<"Codigo invalido"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else
    {
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
        if (codigoPasillo==0){
            return;
        }
        if (aux != NULL){
            cout<<"Ha seleccionado el pasillo: "<<aux->nombre<<endl;
            cout<<"Ingrese el codigo del producto en el cual esta la marca cuya pertenencia desea cambiar, o un cero para volver: ";
            cin>>codigoProducto;
            if(cin.fail())
            {
                cout<<"Codigo invalido"<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
            else{
                pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigoProducto);
                if (codigoProducto==0){
                    return;
                }
                if (aux2!=NULL){
                    cout<<"Ha seleccionado el producto: "<<aux2->nombre<<endl;
                    cout<<"Ingrese el codigo de la marca cuya pertenencia desea cambiar, o un cero para volver: ";
                    cin>>codigoMarca;
                    if(cin.fail())
                    {
                        cout<<"Codigo invalido"<<endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                    }
                    else{
                        if (codigoMarca==0){
                            return;
                        }
                        codigoIS = to_string(codigoPasillo) + to_string(codigoProducto) + to_string(codigoMarca);
                        codigoI = stoi (codigoIS);
                        pnodoAA aux3 = inventario.buscarNodoAA(codigoI);
                        if (aux3!=NULL){
                            cout<<"Ha seleccionado la marca: "<<aux3->nombre;
                            if (aux3->canastaB==1){
                                cout<<", la cual no pertenece a la canasta basica"<<endl;
                            }
                            else{
                                cout<<", la cual pertenece a la canasta basica"<<endl;
                            }
                            cout<<"Digite un 0 para que esta marca pertenezca a la canasta y un 1 en caso contrario: ";
                            cin>>canasta;
                            if(cin.fail())
                            {
                                cout<<"Opcion invalida"<<endl;
                                cin.clear();
                                cin.ignore(256,'\n');
                                return;
                            }
                            if (canasta!=1 && canasta !=0){
                                cout<<"Opcion invalida"<<endl;
                            }
                            aux3->canastaB = canasta;
                            cout<<"Pertenencia modificada"<<endl;
                        }else{
                            cout<<"No se encontro la marca ingresada en el inventario"<<endl;
                        }
                    }
                }
                else
                {
                    cout<<"No existen productos con el codigo ingresado"<<endl;
                }
            }
        }
        else
        {
            cout<<"No existen pasillos con el codigo ingresado"<<endl;
        }
    }
}

void Menu::menuConsultar(){
    cout<<"*****************Consulta de datos******************"<<endl;
    cout<<"1. Consultar el precio de una marca"<<endl;
    cout<<"2. Consultar la pertenencia de una marca a la canasta basica"<<endl;
    cout<<"3. Consultar el porcentaje de impuesto de una marca"<<endl;
    cout<<"0. Volver al menu de administrador"<<endl;
    cout<<"Seleccione el dato que desea consultar: ";
    string opcionS;
    int opcion;
    cin>>opcionS;
    if(!esNumerico(opcionS))
    {
        cout<<"Opcion invalida"<<endl;
        menuConsultar();
        return;
    }
    opcion = stoi (opcionS);
    if (opcion==1)
        consultaPrecio ();
    else if(opcion==2)
    {
       consultaPertenencia ();
    }
    else if (opcion==3)
    {
        consultaImpuesto ();
    }
    else if(opcion==0)
    {
       return;
    }
    else
    {
        cout<<"Opcion invalida"<<endl;
        menuConsultar();
        return;
    }
    menuConsultar();
    return;
}

void Menu::consultaPrecio (){
    int codigoPasillo;
    int codigoProducto;
    int codigo;
    cout<<"Ingrese el codigo del pasillo en el cual esta la marca cuyo precio desea consultar, o un cero para volver: ";
    cin>>codigoPasillo;
    if(cin.fail())
    {
        cout<<"Codigo invalido"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else
    {
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
        if (codigoPasillo==0){
            return;
        }
        if (aux != NULL){
            cout<<"Ha seleccionado el pasillo: "<<aux->nombre<<endl;
            cout<<"Ingrese el codigo del producto en el cual esta la marca cuyo precio desea consultar, o un cero para volver: ";
            cin>>codigoProducto;
            if(cin.fail())
            {
                cout<<"Codigo invalido"<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
            else{
                pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigoProducto);
                if (codigoProducto==0){
                    return;
                }
                if (aux2!=NULL){
                    cout<<"Ha seleccionado el producto: "<<aux2->nombre<<endl;
                    cout<<"Ingrese el codigo de la marca cuyo precio desea consultar, o un cero para volver: ";
                    cin>>codigo;
                    if(cin.fail())
                    {
                        cout<<"Codigo invalido"<<endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                    }
                    else{
                        if (codigo==0){
                            return;
                        }
                        RBTree temp = RBTree (aux2->marcas);
                        NodePtr aux3 = temp.searchTree(codigo);
                        if (aux3!=NULL){
                            cout<<"Ha seleccionado la marca: "<<aux3->nombre<<", cuyo precio es: "<<aux3->precio<<" colones"<<endl;
                        }
                        else
                        {
                            cout<<"No existen marcas con el codigo ingresado"<<endl;
                        }
                    }
                }
                else
                {
                    cout<<"No existen productos con el codigo ingresado"<<endl;
                }
            }
        }
        else
        {
            cout<<"No existen pasillos con el codigo ingresado"<<endl;
        }
    }
}

void Menu::consultaImpuesto(){
    int codigoPasillo;
    int codigoProducto;
    int codigoMarca;
    int codigoI;
    string codigoIS;
    int canasta;
    cout<<"Ingrese el codigo del pasillo en el cual esta la marca cuyo impuesto desea consultar, o un cero para volver: ";
    cin>>codigoPasillo;
    if(cin.fail())
    {
        cout<<"Codigo invalido"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else
    {
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
        if (codigoPasillo==0){
            return;
        }
        if (aux != NULL){
            cout<<"Ha seleccionado el pasillo: "<<aux->nombre<<endl;
            cout<<"Ingrese el codigo del producto en el cual esta la marca cuyo impuesto desea consultar, o un cero para volver: ";
            cin>>codigoProducto;
            if(cin.fail())
            {
                cout<<"Codigo invalido"<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
            else{
                pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigoProducto);
                if (codigoProducto==0){
                    return;
                }
                if (aux2!=NULL){
                    cout<<"Ha seleccionado el producto: "<<aux2->nombre<<endl;
                    cout<<"Ingrese el codigo de la marca cuyo impuesto desea consultar, o un cero para volver: ";
                    cin>>codigoMarca;
                    if(cin.fail())
                    {
                        cout<<"Codigo invalido"<<endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                    }
                    else{
                        if (codigoMarca==0){
                            return;
                        }
                        codigoIS = to_string(codigoPasillo) + to_string(codigoProducto) + to_string(codigoMarca);
                        codigoI = stoi (codigoIS);
                        pnodoAA aux3 = inventario.buscarNodoAA(codigoI);
                        if (aux3!=NULL){
                            cout<<"Ha seleccionado la marca: "<<aux3->nombre<<", cuyo porcentaje de impuesto es: "<<aux3->impuesto<<endl;
                        }else{
                            cout<<"No se encontro la marca ingresada en el inventario"<<endl;
                        }
                    }
                }
                else
                {
                    cout<<"No existen productos con el codigo ingresado"<<endl;
                }
            }
        }
        else
        {
            cout<<"No existen pasillos con el codigo ingresado"<<endl;
        }
    }
}

void Menu::consultaPertenencia(){
    int codigoPasillo;
    int codigoProducto;
    int codigoMarca;
    int codigoI;
    string codigoIS;
    int canasta;
    cout<<"Ingrese el codigo del pasillo en el cual esta la marca cuya pertenencia desea consultar, o un cero para volver: ";
    cin>>codigoPasillo;
    if(cin.fail())
    {
        cout<<"Codigo invalido"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    else
    {
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
        if (codigoPasillo==0){
            return;
        }
        if (aux != NULL){
            cout<<"Ha seleccionado el pasillo: "<<aux->nombre<<endl;
            cout<<"Ingrese el codigo del producto en el cual esta la marca cuya pertenencia desea consultar, o un cero para volver: ";
            cin>>codigoProducto;
            if(cin.fail())
            {
                cout<<"Codigo invalido"<<endl;
                cin.clear();
                cin.ignore(256,'\n');
            }
            else{
                pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigoProducto);
                if (codigoProducto==0){
                    return;
                }
                if (aux2!=NULL){
                    cout<<"Ha seleccionado el producto: "<<aux2->nombre<<endl;
                    cout<<"Ingrese el codigo de la marca cuya pertenencia desea consultar, o un cero para volver: ";
                    cin>>codigoMarca;
                    if(cin.fail())
                    {
                        cout<<"Codigo invalido"<<endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                    }
                    else{
                        if (codigoMarca==0){
                            return;
                        }
                        codigoIS = to_string(codigoPasillo) + to_string(codigoProducto) + to_string(codigoMarca);
                        codigoI = stoi (codigoIS);
                        pnodoAA aux3 = inventario.buscarNodoAA(codigoI);
                        if (aux3!=NULL){
                            cout<<"Ha seleccionado la marca: "<<aux3->nombre;
                            if (aux3->canastaB==1){
                                cout<<", la cual no pertenece a la canasta basica"<<endl;
                            }
                            else{
                                cout<<", la cual pertenece a la canasta basica"<<endl;
                            }
                        }else{
                            cout<<"No se encontro la marca ingresada en el inventario"<<endl;
                        }
                    }
                }
                else
                {
                    cout<<"No existen productos con el codigo ingresado"<<endl;
                }
            }
        }
        else
        {
            cout<<"No existen pasillos con el codigo ingresado"<<endl;
        }
    }
}
void Menu::FacturarCliente()
///In:
///Out:None
///Funci�n: Se encarga de realizar facturas en funci�n de la pila de productos del cliente, esta pila pasa a una lista, la cual se ordena con quicksort para luego ser recorrida con el fin de poner cada producto en la factura
{
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
            enviar=enviar+"Cantidad: "+std::to_string(item->cantidad)+" Codigo: "+item->marca+" Nombre: "+item->nombre+" Precio: "+std::to_string(precios)+" Impuestos: "+std::to_string(aplic)+" Total: "+std::to_string(total+aplic)+"\n";
            totalT=totalT+total+aplic;
        }
//        pNodoBinario aux = buscarNodo(supermercado.raiz,stoi(item->pasillo));
//        pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,stoi(item->producto));
//        RBTree temp = RBTree(aux2->marcas);
//        NodePtr aux3 = temp.searchTree(stoi(item->marca));
//        aux3->cantidadVentas = aux3->cantidadVentas + item->cantidad;
//        aux2->cantidadVentas = aux2->cantidadVentas + item->cantidad;
        listaventasG.insert(item->pasillo,item->producto,item->marca,item->producto,item->cantidad);
        listaventasI.insert(item->pasillo,item->producto,item->marca,item->producto,item->cantidad);
//       listaventasT.insert(item->pasillo,item->producto,item->marca,item->producto,item->cantidad);
        item=item->siguiente;
    }

    outfile<<"                      Total a pagar: "<<totalT<<"\n \n \n \n"<<endl;
    outfile.close();
    cout<<atendido->socket<<endl;
    emit enviart(&atendido->socket,QByteArray::fromStdString(enviar));
    colaclientes.BorrarInicio();
    return;
}

int Menu::precio(conodo compremix)
// In: nodoCompra* Out:int Fun: Devuelve el precio de un producto
{
    pNodoBinario pas=buscarNodo(supermercado.raiz,stoi(compremix->pasillo));
    pNodoBinarioAVL pro=buscarNodoAVL(pas->productos,stoi(compremix->producto));
    RBTree rojo=RBTree(pro->marcas);
    NodePtr marca=rojo.searchTree(stoi(compremix->marca));
    return marca->precio;
}

void Menu::reportePasillos (){
    ofstream archivo ("reportePasillos.txt");
    string texto;
    archivo<<"Pasillo(s) del supermercado: "<<endl;
    supermercado.reportePasillos(texto);
    archivo<<texto<<endl;
    string nombreArchivo ="reportePasillos";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void Menu::reporteClientes() {
    ofstream archivo ("reporteClientes.txt");
    string texto;
    archivo<<"Cliente(s) del supermercado: "<<endl;
    clientes.reporteClientes(texto);
    archivo<<texto<<endl;
    string nombreArchivo ="reporteClientes";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void Menu::reportePasilloMasVisitado(){
    ofstream archivo ("PasilloMasVisitado.txt");
    string texto;
    archivo<<"Pasillo(s) más visitado(s): "<<endl;
    supermercado.reportePasilloMasVisitado(texto);
    archivo<<texto<<endl;
    string nombreArchivo ="PasilloMasVisitado";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

void Menu::reportePasilloMenosVisitado(){
    ofstream archivo ("PasilloMenosVisitado.txt");
    string texto;
    archivo<<"Pasillo(s) menos visitado(s): "<<endl;
    supermercado.reportePasilloMenosVisitado(texto);
    archivo<<texto<<endl;
    string nombreArchivo ="PasilloMenosVisitado";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
}

string inordenMandar(pNodoBinario nodo)
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

void reporteProductoPasilloMasVendido (){
    if (supermercado.raiz == NULL){
        cout<<"No hay pasillos registrados aun"<<endl;
        return;
    }
    int codigoPasillo;
    string codigoPasilloS;
    cout<<inordenMandar(supermercado.raiz)<<endl;
    bool x = true;
    while (x){
        cout<<"Por favor digite el codigo del pasillo cuyo producto mas vendido desea conocer: ";
        cin>>codigoPasilloS;
        if(!esNumerico(codigoPasilloS)){
            cout<<"Debe digitar un codigo de pasillo valido"<<endl;
            continue;
        }
        codigoPasillo = stoi(codigoPasilloS);
        pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
        if (aux!=NULL){
            break;
        }else{
            cout<<"Debe digitar un codigo de pasillo valido"<<endl;
        }
    }
    pNodoBinario aux = buscarNodo(supermercado.raiz,codigoPasillo);
    ofstream archivo ("ProductoPasilloMasVendido.txt");
    string texto;
    archivo<<"Producto(s) mas vendido(s): "<<endl;
    BinarioAVL temp = BinarioAVL();
    temp.raiz = aux->productos;
    temp.reporteProductoMasVendido(texto);
    archivo<<texto<<endl;
    string nombreArchivo ="ProductoPasilloMasVendido";
    nombreArchivo = "notepad \"" + nombreArchivo + "\"";
    cout<<"Debe cerrar el archivo para volver al menu de reportes"<<endl;
    system(nombreArchivo.c_str());
    archivo.close();
    return;
 }



//A continuacion se definen las funciones de los menus, ambas llaman a las demas funciones descritas y mantienen el ciclo de entradas
//de ser necesario. Ademas, permiten el paso de parametros por referencia a las funciones que asi lo requieren
int Menu::menuReportes (){
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
    cout<<"0-Volver al menu principal"<<endl;
    cout<<"Digite el numero de la opcion deseada: ";
    cin>> opcionS;
    if (!esNumerico(opcionS)){
        cout<<"La opcion digitada es invalida"<<endl;
        return 0;
    }
    opcion = stoi (opcionS);
    switch (opcion){
        case 1: reportePasilloMasVisitado();
        break;
        case 2: reportePasilloMenosVisitado();
        break;
        case 3: reporteProductoPasilloMasVendido();
        break;
        case 4: cout<<"reporteMarcasMasVendidas();";
        break;
        case 5: cout<<"reporteClienteQueMasCompro();";
        break;
        case 6: cout<<"reporteClienteQueMenosCompro();";
        break;
        case 7: cout<<"reporteProductoGondola();";
        break;
        case 8: cout<<"reporteClienteMasFacturas();";
        break;
        case 9: cout<<"reporteMarcasProducto();";
        break;
        case 10: cout<<"reporteFacturaMayor();";
        break;
        case 11: cout<<"reporteProductoPasillo();";
        break;
        case 12: reporteClientes();
        break;
        case 13: reportePasillos();
        break;
        case 14: cout<<"reporteInventario();";
        break;
        case 0: return 1;
        default:
            cout<<"La opcion escogida es invalida"<<endl;
        break;
    }
    return 0;
}



