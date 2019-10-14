#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;



class nodoCiudad {
   public:
    nodoCiudad(int pCodigo, string pNombre)
    {
       nombre = pNombre;
       codigo = pCodigo;
       siguiente = NULL;
       anterior =NULL;
    }

   nodoCiudad( int pCodigo, string pNombre, nodoCiudad* signodo)
    {
       nombre = pNombre;
       codigo = pCodigo;
       siguiente = signodo;
    }
    string nombre;
    int  codigo;
    nodoCiudad *siguiente;
    nodoCiudad *anterior;

   friend class listaCiudades;
};
 typedef nodoCiudad *pnodoCiudad;

class listaCiudades {
   public:
    listaCiudades() { primero = actual = NULL; }
    void InsertarInicio(int pCodigo, string pNombre);
    void InsertarFinal (int pCodigo, string pNombre);
    bool ListaVacia() { return primero == NULL; }
    void Mostrar ();
    int largoLista();
    void cargarCiudades (string pNombreArchivo);
    pnodoCiudad primero;
    pnodoCiudad actual;
};

int listaCiudades::largoLista(){
    int cont=0;
    pnodoCiudad aux = primero;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        cont++;
        aux=aux->siguiente;
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
}

void listaCiudades::InsertarInicio(int pCodigo, string pNombre){

   if (ListaVacia())
   {
     primero = new nodoCiudad(pCodigo, pNombre);
     primero->anterior=primero;
     primero->siguiente=primero;
   }
   else
   {
     pnodoCiudad nuevo=new nodoCiudad (pCodigo, pNombre);
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
}

void listaCiudades::InsertarFinal(int pCodigo, string pNombre){
   if (ListaVacia())
     {
     primero = new nodoCiudad(pCodigo, pNombre);
     primero->anterior=primero;
     primero->siguiente=primero;
   }
   else
   {
     pnodoCiudad nuevo = new nodoCiudad(pCodigo, pNombre);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }
}

void listaCiudades::Mostrar(){
   pnodoCiudad aux=primero;
   while(aux->siguiente!=primero)
     {
      cout <<aux->codigo<<", "<<aux->nombre<<endl;
      aux = aux->siguiente;
     }
     cout <<aux->codigo<<", "<<aux->nombre<<endl;
     cout<<endl;
}

void listaCiudades::cargarCiudades(string pNombreArchivo){
    bool rep = false;
    string linea;
    string codigoS;
    int codigo;
    string nombre;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,codigoS,';');
        getline(lineaActual,nombre,';');
        codigo = stoi (codigoS);
        if (ListaVacia()){
            InsertarInicio(codigo, nombre);
        }else{
            pnodoCiudad aux = primero;
            if (aux->codigo==codigo){
                rep = true;
            }
            aux=aux->siguiente;
            while (aux!=primero){
                if (aux->codigo==codigo)
                    rep = true;
                aux=aux->siguiente;
            }
            if (rep==false){
                InsertarFinal(codigo,nombre);
            }
            else{
                rep=false;
            }
        }
    }
    archivo.close();
}
