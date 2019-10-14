#include "Nodos.h"
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
void Cola::insertarFinal(string pcedula,string pnombre,string ptelefono,string pcorreo,PilaC*carrito,int facturas)
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
void Cola::BorrarInicio()
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
clienodo Cola::obtenercliente()
///Encargado de retornar el primer cliente en entrar a la cola
{
    if(ColaVacia())
    {
        cout<<"No hay clientes en la cola"<<endl;
    }
    clienodo atender=primero;
    return atender;




}
void PilaC::InsertarInicio(string pasillop,string productop,string marcap,string nombrep,int pcantidad)
///Inserta al tope de la pila
{
if (PilaVacia())
     primero = new nodoCompra( pasillop, productop, marcap, nombrep, pcantidad);
   else
     primero=new nodoCompra ( pasillop, productop, marcap, nombrep, pcantidad,primero);
}
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
};

void listasort::insert(string pasillo,string producto,string marca,string nombre,int cantidad) {
    ///Simple inserci�n en una lista
  if (this->empty()) {
    this->first = new nodoCompra(pasillo,producto,marca,nombre,cantidad);
    return;
  }
  nodoCompra *aux = this->first;
  this->first = new nodoCompra(pasillo,producto,marca,nombre,cantidad);
  this->first->siguiente = aux;
}

void listasort::print() {
    ///Muestra los elementos de la lista
  conodo aux = this->first;
  while (aux != NULL) {

    cout << aux->cantidad << " "<<aux->nombre<<" ";
    aux = aux->siguiente;
  }
  cout << endl;
}
