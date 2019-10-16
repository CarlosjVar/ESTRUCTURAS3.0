#include "menu.h"

void Menu::menu()
//In:Binario B1mercado,inventario inventario,listaClientes clientes
//Out:None
//Funci�n: Men� que funciona como nexo principal entre todas las funcionalidades
{
    int opcion;
    cout<<"Sistema de gestion del supermercado"<<endl<<"por favor selecciones una opcion: "<<endl;
    cout<<"1. Facturar"<<endl;
    cout<<"2. Revisar Gondolas"<<endl;
    cout<<"3. Verificar Inventario"<<endl;
    cout<<"4. Generacion de reportes"<<endl;
    cout<<"5. Ingresar nuevos datos"<<endl;
    cout<<"6. Modificar datos"<<endl;
    cout<<"7. Consultas"<<endl;
    cout<<"0. Salir del programa"<<endl;
    cout<<"Opcion: ";
    cin>>opcion;
    cout<<" "<<endl;
    if(cin.fail())
    {
        cout<<"Opcion invalida"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    if (opcion==1)
//        if(espera->ColaVacia())
//        {
//            cout<<"La cola de clientes est� vac�a"<<endl;
//        }
//        else
//        {
//        }
        cout<<"Opcion de facturar"<<endl;
    else if(opcion==2)
    {
        //rellenarGondolas(Supermercado,inventario,listaventasG);
        //listaventasG.first=NULL;
        cout<<"Opcion de rellenar gondolas"<<endl;
    }
    else if (opcion==3)
    {
        //rellenarInventario(inventario, listaventasI);
        //listaventasI.first=NULL;
        cout<<"Opcion de revisar inventario"<<endl;
    }
    else if(opcion==4)
    {
        //reportes(Supermercado,clientes,inventario);
        cout<<"Reportes"<<endl;
    }
    else if(opcion==5)
    {
        menuAgregar();
    }
    else if(opcion==6)
    {
        menuModificar();
    }
    else if(opcion==7)
    {
       cout<<"opcion de consultas"<<endl;
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
    int opcion;
    cout<<"1. Pasillo"<<endl;
    cout<<"2. Producto"<<endl;
    cout<<"3. Marca"<<endl;
    cout<<"4. Cliente"<<endl;
    cout<<"0. Volver al menu de administrador"<<endl;
    cout<<"Seleccione el dato que desea agregar: ";
    cin>>opcion;
    if(cin.fail())
    {
        cout<<"Opcion invalida"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
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
    int opcion;
    cout<<"1. Modificar precio"<<endl;
    cout<<"2. Modificar impuesto"<<endl;
    cout<<"3. Modificar pertenencia a la canasta"<<endl;
    cout<<"0. Volver al menu de administrador"<<endl;
    cout<<"Seleccione una opcion: ";
    cin>>opcion;
    if(cin.fail())
    {
        cout<<"Opcion invalida"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
    }
    if (opcion==1)
        modificarPrecio ();
    else if(opcion==2)
    {
        //modificarImpuesto ();
    }
    else if (opcion==3)
    {
        //modificarPertenencia (B1);
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
                        if (codigo!=NULL){
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


