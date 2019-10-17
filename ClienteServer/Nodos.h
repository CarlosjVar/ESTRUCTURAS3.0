#ifndef NODOS_H
#define NODOS_H
#include <iostream>
#include <string>
#include "Rojinegro.h"
using namespace std;

class NodoBinarioAVL {
   public:

    NodoBinarioAVL(int num,string nombre, NodoBinarioAVL *der = NULL, NodoBinarioAVL *izq = NULL, NodoBinarioAVL *sig=NULL, NodoBinarioAVL *ant=NULL):
        Hizq(izq), Hder(der), valor(num), siguiente(sig), anterior(ant), FB(0), nombre(nombre) {}

    string nombre;
    int valor;
    int FB;
    NodoBinarioAVL *Hizq, *Hder, *siguiente, *anterior;
    NodePtr marcas = NULL;
    friend class Pila;
    friend class Binario;
    friend class BinarioAVL;
    void InsertaBinarioAVL(int num,string nombre);
};
typedef NodoBinarioAVL *pnodoAVL;
typedef NodoBinarioAVL *pNodoBinarioAVL;
class NodoBinario {
   public:

    NodoBinario(int num,string nombre, NodoBinario *der = NULL, NodoBinario *izq = NULL, NodoBinario *sig=NULL, NodoBinario *ant=NULL):
        Hizq(izq), Hder(der), valor(num), nombre(nombre), siguiente(sig), anterior(ant){}

    string nombre;
    int valor;
    pNodoBinarioAVL productos = NULL;
    NodoBinario *Hizq, *Hder, *siguiente, *anterior;

    friend class Pila;
    friend class Binario;

    void InsertaBinario(int num, string nombre);
};

typedef NodoBinario *pnodo;
typedef NodoBinario *pNodoBinario;
class nodoCompra{
    ///Nodo utilizado en la pila de compras para guardar informaci�n acerca de los productos seleccionados por el cliente
public:
    nodoCompra(string pasillop,string productop,string marcap,string nombrep,int pcantidad){
    pasillo=pasillop;
    producto=productop;
    marca=marcap;
    nombre=nombrep;
    cantidad=pcantidad;
    siguiente=NULL;
    }
    nodoCompra(string pasillop,string productop,string marcap,string nombrep,int pcantidad, nodoCompra*sigui)
    {
       pasillo=pasillop;
        producto=productop;
        marca=marcap;
        nombre=nombrep;
        cantidad=pcantidad;
        siguiente=sigui;
    }
    int cantidad;
    nodoCompra*siguiente;
private:
    string pasillo;
    string producto;
    string marca;
    string nombre;
friend class listasort;
friend class PilaC;
friend class Menu;
friend class Mycliente;
};
typedef nodoCompra*conodo;

class PilaC
{
public:
    PilaC(){primero=actual=NULL;}
    void InsertarInicio(string pasillop,string productop,string marcap,string nombrep,int pcantidad);
    conodo BorrarInicio();
    bool PilaVacia(){return primero==NULL;}
    void Mostrar();

private:
    nodoCompra*primero;
    nodoCompra*actual;
    friend class Menu;
    friend class Mycliente;
};
class nodoCliente{
    ///Nodo que guarda la informaci�n de los clientes
public:
    nodoCliente(string pcedula,string pnombre,string ptelefono,string pcorreo){
    cedula=pcedula;
    nombre=pnombre;
    telefono=ptelefono;
    correo=pcorreo;
    siguiente=NULL;
    anterior=NULL;
    carrito=NULL;
    facturas=0;
    total=0;
    mayor=0;
    }
    nodoCliente(string pcedula,string pnombre,string ptelefono,string pcorreo,int pmayor)
    {
    cedula=pcedula;
    nombre=pnombre;
    telefono=ptelefono;
    correo=pcorreo;
    siguiente=NULL;
    anterior=NULL;
    carrito=NULL;
    facturas=0;
    total=0;
    mayor=pmayor;
    }
private:
    string cedula;
    string nombre;
    string telefono;
    string correo;
    int facturas;
    nodoCliente*siguiente;
    nodoCliente*anterior;
    PilaC*carrito;
    int total;
    int mayor;
    friend class Menu;
    friend class ColaS;
    friend class Mycliente;
};
typedef nodoCliente*clienodo;
class ColaS{
    ///Cola encargada de hacer de cola de espera del supermercado
public:
    ColaS(){primero=actual=NULL;}
    void insertarFinal(string pcedula,string pnombre,string ptelefono,string pcorreo,PilaC*carrito,int facturas);
    void BorrarInicio();
    bool ColaVacia(){return primero==NULL;};
    clienodo obtenercliente();
    void Mostrar();
private:
    nodoCliente*primero;
    nodoCliente*actual;
    friend class Menu;
    friend class Mycliente;

};
class listasort {
    ///Lista obtenida de internet que se encarga de sortear elementos
 private:
  conodo first;

 public:
  listasort() { this->first = NULL; }
  bool empty() { return this->first == NULL; }
  void insert(string pasillo,string producto,string marca,string nombre,int cantidad);
  void print();
  void sort();
  void mergeSort(nodoCompra **headRef);
  void frontBackSplit(nodoCompra *source, nodoCompra **frontRef, nodoCompra **backRef);
    nodoCompra*sortedMerge(nodoCompra *a, nodoCompra *b);
    friend class Menu;
    friend class Mycliente;
};
void MergeSort(nodoCompra** headRef);
nodoCompra* SortedMerge(nodoCompra* a, nodoCompra* b);
void FrontBackSplit(nodoCompra* source,
                    nodoCompra** frontRef, nodoCompra** backRef);
#endif
