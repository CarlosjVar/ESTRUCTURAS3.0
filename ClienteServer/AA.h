#ifndef AA_H
#define AA_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

class nodoAA {
   public:
    nodoAA(int v)
    {
        valor = v;
        hIzq = NULL;
        hDer = NULL;
        nivel=1;
    }
    nodoAA *hIzq;
    int nivel;
    nodoAA *hDer;
    int valor;
    int codigoPasillo;
    int codigoProducto;
    int codigoMarca;
    string nombre;
    int cantidadStock;
    int canastaB;
    float impuesto;

};
typedef nodoAA *pnodoAA;

class AA{
private:
    nodoAA *raiz;
    pnodoAA insertar(pnodoAA t, int val, int codigoPasillo, int codigoProducto, int codigoMarca, string nombre, int cantidadStock, int canastaB,float impuesto);
    pnodoAA giro(pnodoAA aux);
    pnodoAA reparto(pnodoAA aux);
    pnodoAA rotarDerecha(pnodoAA aux);
    pnodoAA rotarIzquierda(pnodoAA aux);
    void Postorden(pnodoAA ra);
    void Inorden(pnodoAA ra);
    pnodoAA buscarNodoAA(pnodoAA pRaiz,int valor);
public:
    void cargarInventario(string pNombreArchivo);
    AA() { raiz = NULL; }
    void Postorden();
    void Inorden();
    void insertar(int val, int codigoPasillo, int codigoProducto, int codigoMarca, string nombre, int cantidadStock, int canastaB,float impuesto);
    pnodoAA buscarNodoAA(int valor);
    friend class Mycliente;
    friend class Menu;
};
#endif


