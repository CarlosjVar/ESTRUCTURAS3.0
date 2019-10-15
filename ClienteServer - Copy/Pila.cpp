#include "Pila.h"

void Pila::Push(pnodo v)
{
   if(Vacia()) {
      plista = v;
   }else{
    NodoBinario *aux=plista;
    while(aux->siguiente){
        aux=aux->siguiente;
    }
    aux->siguiente=v;
    v->anterior=aux;

   }
}

pnodo Pila::Pop()
{
    NodoBinario *borrar;
    NodoBinario *salida;
    if(Vacia()){
        cout<<"Pila Vacia"<<endl;
    }else{
    borrar=plista;
    while(borrar->siguiente){
        borrar=borrar->siguiente;
    }
    if(Size()>1){
        salida=borrar;
        borrar->anterior->siguiente=NULL;
        borrar=NULL;
        delete borrar;
    }else{
        salida =plista;
        plista = NULL;
    }
    }
    return salida;
}

int Pila::Size(){
    while(plista && plista->anterior) plista = plista->anterior;
    int cont=0;
    NodoBinario *aux;
    aux=plista;
    while(aux){
        cont++;
        aux=aux->siguiente;
    }
    return cont;
}

void Pila::Mostrar(){
    if(Vacia()){
        cout<<"Vacia";
    }
    NodoBinario *aux = plista;
    while(aux){
        cout<< aux->valor<<" - ";
        aux=aux->siguiente;
    }
}
void PilaAVL::Push(pnodoAVL v)
{
   if(Vacia()) {
      plista = v;
   }else{
    NodoBinarioAVL *aux=plista;
    while(aux->siguiente){
        aux=aux->siguiente;
    }
    aux->siguiente=v;
    v->anterior=aux;

   }
}

pnodoAVL PilaAVL::Pop()
{
    NodoBinarioAVL *borrar;
    NodoBinarioAVL *salida;
    if(Vacia()){
        cout<<"Pila Vacia"<<endl;
    }else{
    borrar=plista;
    while(borrar->siguiente){
        borrar=borrar->siguiente;
    }
    if(Size()>1){
        salida=borrar;
        borrar->anterior->siguiente=NULL;
        borrar=NULL;
        delete borrar;
    }else{
        salida =plista;
        plista = NULL;
    }
    }
    return salida;
}

int PilaAVL::Size(){
    while(plista && plista->anterior) plista = plista->anterior;
    int cont=0;
    NodoBinarioAVL *aux;
    aux=plista;
    while(aux){
        cont++;
        aux=aux->siguiente;
    }
    return cont;
}

void PilaAVL::Mostrar(){
    if(Vacia()){
        cout<<"Vacia";
    }
    NodoBinarioAVL *aux = plista;
    while(aux){
        cout<< aux->valor<<" - ";
        aux=aux->siguiente;
    }
}

