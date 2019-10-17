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
void PilaC::InsertarInicio(string pasillop,string productop,string marcap,string nombrep,int pcantidad)
///Inserta al tope de la pila
{
if (PilaVacia())
     primero = new nodoCompra( pasillop, productop, marcap, nombrep, pcantidad);
   else
     primero=new nodoCompra ( pasillop, productop, marcap, nombrep, pcantidad,primero);
}

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
void PilaC::Mostrar()
///Muestra la pila de productos
{
   conodo aux;
if (primero== NULL)
   cout << "No hay elementos";
else
{


    aux = primero;
    while(aux)
    {
        cout << aux->nombre<< "-> ";
        aux = aux->siguiente;
    }
    cout << endl;
   }

}
void FrontBackSplit(nodoCompra* source,
                    nodoCompra** frontRef, nodoCompra** backRef)
/// Parte la lista en 2 mitades, la del inicio y la de la mitad
{
    nodoCompra* fast;
    nodoCompra* slow;
    slow = source;
    fast = source->siguiente;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->siguiente;
        if (fast != NULL) {
            slow = slow->siguiente;
            fast = fast->siguiente;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->siguiente;
    slow->siguiente = NULL;
}
nodoCompra* SortedMerge(nodoCompra* a, nodoCompra* b)
/// Mueve las direcciones de siguiente para ajustar la lista y sortearla
{
    nodoCompra* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
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
void MergeSort(nodoCompra** headRef)
{
    nodoCompra* head = *headRef;
    nodoCompra* a;
    nodoCompra* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->siguiente == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}


