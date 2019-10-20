#include "B.h"
void ArbolB::insertar(tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo)
{
    raiz = insertar(raiz, cl, nombre, telefono, codigoCiudad, correo);
}

Pagina* ArbolB::insertar(Pagina *r, tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo)
{
    bool subeArriba;
    int mediana;
    Pagina *nd;
    subeArriba = empujar(r, cl,  mediana, nd, nombre, telefono, codigoCiudad, correo);
    // El arbol crece de nivel y se inserta la clave mediana
    if(subeArriba)
    {
        Pagina *p;
        p = new Pagina(orden);
        p->cambiarCuenta(1);
        p->cambiarClave(1, mediana);
        p->cambiarDato(1,0,nombre);
        p->cambiarDato(1,1,telefono);
        p->cambiarDato(1,2,codigoCiudad);
        p->cambiarDato(1,3,correo);
        // Claves menores
        p->cambiarRamas(0, r);
        // Claves mayores
        p->cambiarRamas(1, nd);
        r = p;
    }
    return r;
}

bool ArbolB::empujar(Pagina *actual, tipoClave cl, tipoClave &mediana, Pagina *&nuevo, string &nombre, string &telefono, string &codigoCiudad, string &correo)
{
    int k;
    bool subeArriba = false;
    // Llego a una pagina nula
    if(actual == NULL)
    {
        // Se devuelve hacia la pagina padre
        subeArriba = true;
        mediana = cl;
        nuevo = NULL;
    }
    else
    {
        bool esta;
        esta = buscarNodo(actual, cl, k);
        if (esta) {
            throw "\nClave duplicada";
        }
        subeArriba = empujar(actual->obtenerRama(k), cl, mediana, nuevo, nombre, telefono, codigoCiudad, correo);
        if (subeArriba) {
            if (!actual->nodoLleno()) {
                subeArriba = false;
                meterPagina(actual, mediana, nuevo, k, nombre, telefono, codigoCiudad, correo);
            } else {
                subeArriba = true;
                dividirNodo(actual, mediana, nuevo, k, nombre, telefono, codigoCiudad, correo);
            }
        }
    }
    return subeArriba;
}

/**
 * Revisa si la clave se encuentra en el arbol
 * @param actual La pagina actual
 * @param cl La clave que se busca
 * @param k La posicion de la pagina
 * @return verdadero si se encuentra la clave
 */
bool ArbolB::buscarNodo(Pagina *actual, tipoClave cl, int &k)
{
    int index;
    bool encontrado;
    // Revisar si la clave esta en la pagina
    if(cl < actual->obtenerClave(1))
    {
        encontrado = false;
        index = 0;
    }
    else
    {
        // Llegar a la posicion que debe tener la clave
        index = actual->obtenerCuenta();
        while(cl < actual->obtenerClave(index) && index > 1)
        {
            index--;
        }
        // Revisar si la clave existe
        encontrado = cl == actual->obtenerClave(index);
    }
    k = index;
    return encontrado;
}

/**
 * Baja por las ramas del arbol hasta encontrar la clave
 * @param cl La clave que se desea buscar
 * @param n
 * @return La referencia al nodo donde se encuentra la clave
 */
Pagina* ArbolB::buscar(tipoClave cl, int &n)
{
    return buscar(this->raiz, cl, n);
}

/**
 * Recorre todos los nodos en busca de las claves
 * @param actual
 * @param cl
 * @param n
 * @return
 */
Pagina* ArbolB::buscar(Pagina *actual, tipoClave cl, int &n)
{
    // Parada de la funcion recursiva
    if(actual == nullptr)
    {
        return nullptr;
    }
    else
    {
        // Verificar si existe dentro del nodo
        bool esta = buscarNodo(actual, cl, n);
        if (esta)
            return actual;
        else
            return buscar(actual->obtenerRama(n), cl, n);
    }
}

void ArbolB::meterPagina(Pagina *actual, tipoClave cl, Pagina *ramaDr, int k, string nombre, string telefono, string codigoCiudad, string correo)
{
    // Desplazar elementos a la derecha
    for(int i = actual->obtenerCuenta(); i >= k + 1; i--)
    {
        actual->cambiarClave(i + 1, actual->obtenerClave(i));
        actual->cambiarDato(i+1 , 0 , actual->obtenerDato(i,0));
        actual->cambiarDato(i+1 , 1 , actual->obtenerDato(i,1));
        actual->cambiarDato(i+1 , 2 , actual->obtenerDato(i,2));
        actual->cambiarDato(i+1 , 3 , actual->obtenerDato(i,3));
        actual->cambiarRamas(i + 1, actual->obtenerRama(i));
    }
    // Pone la clave y la rama derecha en la posicion k + 1
    actual->cambiarClave(k + 1, cl);
    actual->cambiarDato(k+1,0,nombre);
    actual->cambiarDato(k+1,1,telefono);
    actual->cambiarDato(k+1,2,codigoCiudad);
    actual->cambiarDato(k+1,3,correo);
    actual->cambiarRamas(k + 1, ramaDr);
    // Incrementa el numero de claves
    actual->cambiarCuenta(actual->obtenerCuenta() + 1);
}

void ArbolB::dividirNodo(Pagina *actual, tipoClave &mediana, Pagina *&nuevo, int pos, string &nombre, string &telefono, string &codigoCiudad, string &correo)
{
    int i, posMdna, k;
    Pagina *nuevaPag;
    k = pos;
    // Posicion de la clave mediana
    posMdna = (k <= orden / 2) ? orden / 2 : orden / 2 + 1;
    nuevaPag = new Pagina(orden);
    for(i = posMdna + 1; i < orden; i++)
    {
        nuevaPag->cambiarClave(i - posMdna, actual->obtenerClave(i));
        nuevaPag->cambiarRamas(i - posMdna, actual->obtenerRama(i));
        nuevaPag->cambiarDato(i - posMdna , 0 , actual->obtenerDato(i,0));
        nuevaPag->cambiarDato(i - posMdna , 1 , actual->obtenerDato(i,1));
        nuevaPag->cambiarDato(i - posMdna , 2 , actual->obtenerDato(i,2));
        nuevaPag->cambiarDato(i - posMdna , 3 , actual->obtenerDato(i,3));
    }
    nuevaPag->cambiarCuenta((orden - 1) - posMdna);
    actual->cambiarCuenta(posMdna);
    if (k <= orden / 2)
        meterPagina(actual, mediana, nuevo, pos, nombre, telefono, codigoCiudad, correo);
    else
    {
        pos = k - posMdna;
        meterPagina(nuevaPag, mediana, nuevo, pos, nombre, telefono, codigoCiudad, correo);
    }
    mediana = actual->obtenerClave(actual->obtenerCuenta());
    nombre = actual->obtenerDato(actual->obtenerCuenta(),0);
    telefono = actual->obtenerDato(actual->obtenerCuenta(),1);
    codigoCiudad = actual->obtenerDato(actual->obtenerCuenta(),2);
    correo = actual->obtenerDato(actual->obtenerCuenta(),3);
    nuevaPag->cambiarRamas(0, actual->obtenerRama(actual->obtenerCuenta()));
    actual->cambiarCuenta(actual->obtenerCuenta() - 1);
    nuevo = nuevaPag;
}

void ArbolB::escribir()
{
    escribir(raiz, 1);
}

void ArbolB::escribir(Pagina *r, int h)
{
    int i;
    if (r != NULL)
    {
        escribir(r->obtenerRama(0), h + 5);
        for(int i = 1; i <= r->obtenerCuenta() / 2; i++){
            escribir(r->obtenerRama(i), h + 5);
            cout << endl;
        }
        for(i = 1; i <= r->obtenerCuenta(); i++)
        {
            for(int j = 0; j <= h; j++)
            {
                cout << " ";
            }
            cout << r->obtenerClave(i) <<","<< r->obtenerDato(i,0) << endl;
        }
        for(i = r->obtenerCuenta() / 2 + 1; i <= r->obtenerCuenta(); i++)
        {
            this->escribir(r->obtenerRama(i), h + 5);
        }
        cout << endl;
    }
}

void ArbolB::reporteClientes(string &texto)
{
    reporteClientes(texto,this->raiz);
}

void ArbolB::reporteClientes(string &texto, Pagina *r)
{
    if(r)
    {
        reporteClientes(texto,r->obtenerRama(0));
        for (int k = 1; k <= r->obtenerCuenta(); k++)
        {
            texto.append("-Cedula: ");
            texto.append(to_string(r->obtenerClave(k)));
            texto.append(", Nombre del cliente: ");
            texto.append(r->obtenerDato(k,0));
            texto.append (", Telefono: ");
            texto.append(r->obtenerDato(k,1));
            texto.append (", Correo: ");
            texto.append(r->obtenerDato(k,3));
            texto.append (", Cod. de ciudad: ");
            texto.append(r->obtenerDato(k,2));
            texto.append("\n");
            reporteClientes(texto,r->obtenerRama(k));
        }
    }
}

void ArbolB::sacarMayorCompra(int &mayor, Pagina *r)
{
    if(r)
    {
        sacarMayorCompra(mayor,r->obtenerRama(0));
        for (int k = 1; k <= r->obtenerCuenta(); k++)
        {
            if (mayor<r->obtenerEstadistica(k,0)){
                mayor=r->obtenerEstadistica(k,0);
            }
            sacarMayorCompra(mayor,r->obtenerRama(k));
        }
    }
}

void ArbolB::sacarMayorCompra(int &mayor){
    sacarMayorCompra(mayor,this->raiz);
}

void ArbolB::sacarMenorCompra(int &menor, Pagina *r)
{
    if(r)
    {
        sacarMenorCompra(menor,r->obtenerRama(0));
        for (int k = 1; k <= r->obtenerCuenta(); k++)
        {
            if (menor>r->obtenerEstadistica(k,0)){
                menor=r->obtenerEstadistica(k,0);
            }
            sacarMenorCompra(menor,r->obtenerRama(k));
        }
    }
}

void ArbolB::sacarMenorCompra(int &menor){
    sacarMenorCompra(menor,this->raiz);
}

void ArbolB::reporteClienteQueMasCompro(string &texto){
    int mayor;
    sacarMayorCompra(mayor);
    if (mayor==0){
        texto.append("Ningún cliente ha facturado aún");
    }
    reporteClienteQueMasCompro(texto,this->raiz,mayor);

}

void ArbolB::reporteClienteQueMenosCompro(string &texto){
    int menor = raiz->obtenerEstadistica(0,0);
    sacarMenorCompra(menor);
    reporteClienteQueMenosCompro(texto,this->raiz,menor);

}

void ArbolB::reporteClienteQueMasCompro(string &texto, Pagina *r, int mayor){
    if(r)
    {
        reporteClienteQueMasCompro(texto,r->obtenerRama(0),mayor);
        for (int k = 1; k <= r->obtenerCuenta(); k++)
        {
            if (r->obtenerEstadistica(k,0)==mayor){
                texto.append("-Cedula: ");
                texto.append(to_string(r->obtenerClave(k)));
                texto.append(", Nombre del cliente: ");
                texto.append(r->obtenerDato(k,0));
                texto.append("\n");
            }
            reporteClienteQueMasCompro(texto,r->obtenerRama(k),mayor);
        }
    }
}

void ArbolB::reporteClienteQueMenosCompro(string &texto, Pagina *r, int menor){
    if(r)
    {
        reporteClienteQueMenosCompro(texto,r->obtenerRama(0),menor);
        for (int k = 1; k <= r->obtenerCuenta(); k++)
        {
            if (r->obtenerEstadistica(k,0)==menor){
                texto.append("-Cedula: ");
                texto.append(to_string(r->obtenerClave(k)));
                texto.append(", Nombre del cliente: ");
                texto.append(r->obtenerDato(k,0));
                texto.append("\n");
            }
            reporteClienteQueMenosCompro(texto,r->obtenerRama(k),menor);
        }
    }
}


void ArbolB::listaCreciente()
{
    inOrden(raiz);
}

void ArbolB::inOrden(Pagina *r)
{
    if(r)
    {
        inOrden(r->obtenerRama(0));
        for (int k = 1; k <= r->obtenerCuenta(); k++)
        {
            cout << r->obtenerClave(k) <<","<< r->obtenerDato(k,0) << endl;" - ";
            inOrden(r->obtenerRama(k));
        }
    }
}

void ArbolB::cargarClientes(string pNombreArchivo){
    int n;
    bool repetido;
    int cedula;
    string codigoCiudad;
    string linea;
    string cedulaS;
    string nombre;
    string telefono;
    string correo;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,cedulaS,';');
        getline(lineaActual,nombre,';');
        getline(lineaActual,codigoCiudad,';');
        getline(lineaActual,telefono,';');
        getline(lineaActual,correo,';');
        cedula = stoi (cedulaS);
        Pagina* aux = buscar(cedula,n);
        if (aux == NULL){
            insertar(cedula,nombre,telefono,codigoCiudad,correo);

        }
    }
    archivo.close();
}

void ArbolB::cargarAdmins(string pNombreArchivo){
    int n;
    bool repetido;
    int cedula;
    string linea;
    string cedulaS;
    string nombre;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,cedulaS,';');
        getline(lineaActual,nombre,';');
        cedula = stoi (cedulaS);
        Pagina* aux = buscar(cedula,n);
        if (aux == NULL){
            insertar(cedula,nombre,"","","");
        }
    }
    archivo.close();
}
