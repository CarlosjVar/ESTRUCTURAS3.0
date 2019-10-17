#ifndef B_H
#define B_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

using datosCliente = string[4];
// 0: nombre
// 1: codigoCiudad
// 2: telefono
// 3: correo
using estadisticasCliente = int[3];
// 0: numero de facturas
// 1: factura de mayor monto
// 2: acumulado de compras
typedef int tipoClave;
class Pagina;
typedef Pagina *pPagina;
class Pagina
{
protected:
    tipoClave *claves;
    pPagina *ramas;
    int cuenta;
    datosCliente *clientes;
    estadisticasCliente* eClientes;

private:
    int max;
public:
    Pagina(int orden)
    {
        this->max = orden;
        this->claves = new tipoClave[orden];
        this->eClientes = new estadisticasCliente[orden];
        this->clientes = new datosCliente[orden];
        this->ramas = new pPagina[orden];
        for(int i = 0; i <= orden; i++)
        {
            this->ramas[i] = nullptr;
        }
    }
    string obtenerDato (int y,int dato) {return this->clientes[y][dato];}
    void cambiarDato (int numCliente, int numDato , string dato) {this->clientes[numCliente][numDato] = dato;}
    int obtenerEstadistica (int y,int dato) {return this->eClientes[y][dato];}
    void cambiarEstadistica (int numCliente, int numDato , int dato) {this->eClientes[numCliente][numDato] = dato;}
    bool nodoLleno() { return (this->cuenta == this->max - 1); }
    bool nodoSemiVacio() { return (this->cuenta < this->max / 2); }
    tipoClave obtenerClave(int i) { return this->claves[i]; }
    void cambiarClave(int i, tipoClave clave) { this->claves[i] = clave; }
    Pagina *obtenerRama(int i) { return this->ramas[i]; }
    void cambiarRamas(int i, Pagina *p) { this->ramas[i] = p; }
    int obtenerCuenta(){ return this->cuenta; }
    void cambiarCuenta(int valor) { this->cuenta = valor; }
};

class ArbolB
{
protected:
    int orden;
    Pagina *raiz;

private:
    Pagina *insertar(Pagina *raiz, tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo);
    bool empujar(Pagina *actual, tipoClave cl, tipoClave &mediana, Pagina *&nuevo, string &nombre, string &telefono, string &codigoCiudad, string &correo);
    void meterPagina(Pagina *actual, tipoClave cl, Pagina *ramaDr, int k, string nombre, string telefono, string codigoCiudad, string correo);

public:
    ArbolB()
    {
        this->orden = 0;
        this->raiz = NULL;
    }
    explicit ArbolB(int m)
    {
        this->orden = m;
        this->raiz = NULL;
    }
    bool arbolVacio() { return this->raiz == NULL; }
    Pagina *obtenerRaiz() { return raiz; }
    void cambiarRaiz(Pagina *r) { raiz = r; }
    int obtenerOrden() { return orden; }
    void cambiarOrden(int ord) { orden = ord; }

    Pagina *buscar(tipoClave cl, int &n);
    Pagina *buscar(Pagina *actual, tipoClave cl, int &n);

    bool buscarNodo(Pagina *actual, tipoClave cl, int &k);
    void dividirNodo(Pagina *actual, tipoClave &mediana, Pagina *&nuevo, int pos, string &nombre, string &telefono, string &codigoCiudad, string &correo);

    void escribir();
    void escribir(Pagina *r, int h);

    void listaCreciente();
    void inOrden(Pagina *r);
    void cargarClientes (string pNombreArchivo);
    void cargarAdmins(string pnombreARCHIVO);

    void insertar(tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo);
};
#endif
