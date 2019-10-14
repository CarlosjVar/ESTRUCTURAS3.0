#include <iostream>
#include <string>
#ifndef NODOS_H
#define NODOS_H
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

void NodoBinarioAVL::InsertaBinarioAVL(int num, string nombre)
{
    if(num<valor){
        if(Hizq==NULL){
            Hizq = new NodoBinarioAVL(num,nombre);
        }else{
            Hizq->InsertaBinarioAVL(num,nombre);
        }
    }else{
        if(Hder==NULL){
            Hder = new NodoBinarioAVL(num,nombre);
        }else{
            Hder->InsertaBinarioAVL(num,nombre);
        }
    }
}

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

void NodoBinario::InsertaBinario(int num,string nombre)
{
    if(num<valor){
        if(Hizq==NULL){
            Hizq = new NodoBinario(num,nombre);
        }else{
            Hizq->InsertaBinario(num,nombre);
        }
    }else{
        if(Hder==NULL){
            Hder = new NodoBinario(num,nombre);
        }else{
            Hder->InsertaBinario(num,nombre);
        }
    }
}
class nodoCompra{
    ///Nodo utilizado en la pila de compras para guardar informaci�n acerca de los productos seleccionados por el cliente
public:
    nodoCompra(int pasillop,int productop,int marcap,string nombrep,int pcantidad){
    pasillo=pasillop;
    producto=productop;
    marca=marcap;
    nombre=nombrep;
    cantidad=pcantidad;
    siguiente=NULL;
    }
    nodoCompra(int pasillop,int productop,int marcap,string nombrep,int pcantidad, nodoCompra*sigui)
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
    int pasillo;
    int producto;
    int marca;
    string nombre;

friend class Pila;
friend class Menu;
friend class listasort;
friend class listaDCPas;
};
typedef nodoCompra*conodo;
class PilaC{
    ///Pila que contiene los elementos del carrito del cliente
public:
    PilaC(){primero=actual=NULL;}
    void InsertarInicio(int pasillop,int productop,int marcap,string nombrep,int pcantidad);
    conodo BorrarInicio();
    bool PilaVacia(){return primero==NULL;}
    void Mostrar();

private:
    nodoCompra*primero;
    nodoCompra*actual;
    friend class Menu;
};
void PilaC::InsertarInicio(int pasillop,int productop,int marcap,string nombrep,int pcantidad)
///Inserta al tope de la pila
{
if (PilaVacia())
     primero = new nodoCompra( pasillop, productop, marcap, nombrep, pcantidad);
   else
     primero=new nodoCompra ( pasillop, productop, marcap, nombrep, pcantidad,primero);
}
conodo PilaC::BorrarInicio()
{
    conodo aux;
if (PilaVacia()){
 cout << "No hay elementos en la lista:" << endl;
}
    else{
    if (primero->siguiente == NULL) {
                primero= NULL;
            } else {
                primero=primero->siguiente;
            }
    return aux;
    }
}
class nodoCliente{
    ///Nodo que guarda la informaci�n de los clientes
public:
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


friend class listaClientes;
friend class Menu;
friend class ColaS;
};
typedef nodoCliente*clienodo;
class ColaS{
    ///Cola encargada de hacer de cola de espera del supermercado
public:
    Cola(){primero=actual=NULL;}
    void insertarFinal(string pcedula,string pnombre,string ptelefono,string pcorreo,PilaC*carrito,int facturas);
    void BorrarInicio();
    bool ColaVacia(){return primero==NULL;};
    clienodo obtenercliente();
    void Mostrar();
private:
    nodoCliente*primero;
    nodoCliente*actual;
    friend class Menu;
};
void ColaS::insertarFinal(string pcedula,string pnombre,string ptelefono,string pcorreo,PilaC*carrito,int facturas)
///Funci�n que inserta al final de la cola
{
    if (ColaVacia())
    {
    primero = new nodoCliente(pcedula,pnombre,ptelefono,pcorreo);
    primero->carrito=carrito;
    primero->facturas=facturas;
    }
    else
     { clienodo aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoCliente(pcedula,pnombre,ptelefono,pcorreo);
        aux->siguiente->carrito=carrito;
        aux->siguiente->facturas=facturas;

      }

}
void ColaS::BorrarInicio()
///Funci�n encargada de eliminar el primer cliente en entrar a la cola
{
if (ColaVacia()){
 cout << "No hay elementos en la lista:" << endl;

}else{
    if (primero->siguiente == NULL) {
            primero= NULL;
        } else {

            clienodo aux = primero;
            primero=primero->siguiente;
            delete aux;
        }
    }
}
clienodo ColaS::obtenercliente()
///Encargado de retornar el primer cliente en entrar a la cola
{
    if(ColaVacia())
    {
        cout<<"No hay clientes en la cola"<<endl;
    }
    clienodo atender=primero;
    return atender;




}

void ColaS::Mostrar()
///Muestra las personas en cola
{
   clienodo aux;
   if (primero== NULL)
       cout << "No hay elementos";
   else
   {


   		aux = primero;
		while(aux)
		{
		    cout << aux->nombre << "-> ";
		    aux = aux->siguiente;
		}
		cout << endl;
   }
}
#endif
