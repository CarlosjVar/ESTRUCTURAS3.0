/////////
/// Carlos Varela 2019077177
/// Estándar GNC 11+
/// 19/09/19
/// Versión 1.0
//////////
#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED
#include "funciones.h"
#include <fstream>
#include "nodos.h"
using namespace std;
class listaDCPas {
    ///Lista doble circular que ser� usada para armar el supermercado
   public:
    listaDCPas() { primero = actual = NULL; }
    void InsertarInicio(string nombre,string codigoPas);
    void InsertarFinal(string nombre,string codigoPas);
    bool ListaVacia() { return primero == NULL; }
    void Imprimir();
    void Mostrar();
    void Siguiente();
    void Primero();
    int largoLista();
    void cargarPasillos(string nombreArchivo);
    void cargarProductos(string nombreArchivo);
    void cargarMarcas(string nombreArhivo);
    int preciomarca(string pasillo,string producto,string marca);
    void pasilloMV(listaDCPas super);
    void pasilloLV(listaDCPas super);
    void prodPasillMv(listaDCPas super);
    void marcasV(listaDCPas super);
    void marcasPasProd(listaDCPas super);
    void productosPas(listaDCPas super);
    void sacarPas(listaDCPas super);
    void sacarMR(listaDCPas super);
   private:
    pasnodo primero;
    pasnodo actual;
    friend class Menu;
};
int listaDCPas::preciomarca(string pasillop,string productop,string marcap)
///Retorna el precio de una marca dada para su uso en facturas
{
    pasnodo pasillo=primero;
    while(pasillo->siguiente!=primero)
    {
        if(pasillo->codigoP==pasillop)
        {
            break;
        }
        pasillo=pasillo->siguiente;
    }
    if(pasillo->codigoP==pasillop)
    {
      pronodo producto=pasillo->producto;
      while(producto->siguiente!=pasillo->producto)
      {
        if (producto->codigoProd==productop)
        {
            break;
        }
        producto=producto->siguiente;
      }
      if(producto->codigoProd==productop)
      {
          marnodo marca=producto->marca;

          while(marca->siguiente!=producto->marca)
          {
              if(marca->marca==marcap)
              {
                  break;
              }
              marca=marca->siguiente;
          }
          if(marca->marca==marcap)
          {
              return marca->precio;
          }
      }
    }
}
int listaDCPas::largoLista()
///Retorna el largo de una lista
{
    int cont=0;

    pasnodo aux = primero;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
}
void listaDCPas::InsertarInicio(string nombre,string codigoPas)
///Inserta al inicio de una lista doble circular
{
   if (ListaVacia())
   {
     primero = new nodoPasillo( nombre, codigoPas);
     primero->anterior=primero;
     primero->siguiente=primero;
   }
   else
   {
     pasnodo nuevo=new nodoPasillo( nombre, codigoPas);
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
}

void listaDCPas::InsertarFinal(string nombre,string codigoPas)
///Inserta al final de una lista doble circular
{
   if (ListaVacia())
     {
     primero = new nodoPasillo( nombre, codigoPas);
     primero->anterior=primero;
     primero->siguiente=primero;
   }
   else
   {
     pasnodo nuevo = new nodoPasillo( nombre, codigoPas);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }
}

void listaDCPas::Mostrar()
///Muestra lista
{
   pasnodo aux=primero;
   while(aux->siguiente!=primero)
     {

      cout << aux->nombreP << "-> ";
        aux = aux->siguiente;
     }
     cout<<aux->nombreP<<"->";
     cout<<endl;
}


void listaDCPas::cargarPasillos(string pNombreArchivo){
    ///Carga los pasillos de un txt medianto la librer�a fstream y un while de mientras haya l�neas
    bool repetido=false;
    string linea;
    char separador[]=";";
    ifstream archivo (pNombreArchivo);
    getline(archivo,linea);
    if(linea=="")
    {
        return;
    }
    char cstr[linea.size()+1];
    strcpy(cstr,linea.c_str());
    char*token= strtok(cstr,separador);
    string codigo=token;
    token=strtok(NULL,separador);
    InsertarFinal(codigo,token);
    while (getline(archivo,linea)){
        if(linea=="")
        {
            return;
        }
        char cstr[linea.size()+1];
        strcpy(cstr,linea.c_str());
        char*token= strtok(cstr,separador);
        string codigo=token;
        pasnodo aux=primero;
        while(aux->siguiente!=primero){
            if (aux->codigoP==codigo){
                repetido=true;
            }
            aux=aux->siguiente;
        }
        if(!repetido){
        token=strtok(NULL,separador);
        InsertarFinal(codigo,token);
    }
   }
   archivo.close();
}
void listaDCPas::cargarProductos(string pnombreArchivo){
    ///Carga los productos de un txt medianto la librer�a fstream y un while de mientras haya l�neas
    string linea;
    char separador[]=";";
    ifstream archivo (pnombreArchivo);
    getline(archivo,linea);
    if(linea=="")
    {
        return;
    }
    char cstr[linea.size()+1];
    strcpy(cstr,linea.c_str());
    char*token= strtok(cstr,separador);
    string pasillo=token;
    token=strtok(NULL,separador);
    string codigo=token;
    token=strtok(NULL,separador);
    pasnodo aux=primero;
    while(aux->siguiente!=primero)
    {
        if(aux->codigoP==pasillo)
        {

            aux->producto=new nodoProducto(codigo,token);
            aux->producto->anterior=aux->producto;
            aux->producto->siguiente=aux->producto;
        }
        aux=aux->siguiente;
    }
    aux=primero->anterior;
    if(aux->codigoP==pasillo)
        {
            aux->producto=new nodoProducto(codigo,token);
            aux->producto->anterior=aux->producto;
            aux->producto->siguiente=aux->producto;
        }
    while (getline(archivo,linea))
    {
        if(linea=="")
        {
            return;
        }
        bool repetido=false;
        char cstr[linea.size()+1];
        strcpy(cstr,linea.c_str());
        char*token2= strtok(cstr,separador);
        string pasillo2=token2;
        token2=strtok(NULL,separador);
        string codigo2=token2;
        token2=strtok(NULL,separador);
        pasnodo auxp2=primero;
        while(auxp2->siguiente!=primero)
        {
            if (auxp2->codigoP==pasillo2)
            {
                break;
            }
            auxp2=auxp2->siguiente;
        }
        if (auxp2->codigoP==pasillo2)
        {
            if (auxp2->producto==NULL)
            {
                auxp2->producto=new nodoProducto(codigo2,token2);
                auxp2->producto->anterior=auxp2->producto;
                auxp2->producto->siguiente=auxp2->producto;
            }
            else
            {
                pronodo aux2=auxp2->producto;
                while(aux2->siguiente!=auxp2->producto)
                {
                    if (codigo2==aux2->codigoProd)
                    {
                        repetido=true;
                    }
                    aux2=aux2->siguiente;
                }
                if (codigo2==aux2->codigoProd)
                    {
                       repetido=true;
                    }
                if(repetido==false)
                {
                    aux2->siguiente=new nodoProducto(codigo2,token2);
                    aux2->siguiente->anterior=aux2;
                    aux2->siguiente->siguiente=auxp2->producto;
                    auxp2->producto->anterior=aux2->siguiente;
                }
            }
        }
    }
    archivo.close();
}
void listaDCPas::cargarMarcas(string pnombreArchivo)
{
    ///Carga las marcas de un txt medianto la librer�a fstream y un while de mientras haya l�neas
    string linea;
    char separador[]=";";
    ifstream archivo (pnombreArchivo);
    getline(archivo,linea);
    if(linea=="")
    {
        return;
    }
    char cstr[linea.size()+1];
    strcpy(cstr,linea.c_str());
    char*token= strtok(cstr,separador);
    string pasillo=token;
    token=strtok(NULL,separador);
    string producto=token;
    token=strtok(NULL,separador);
    string marca=token;
    token=strtok(NULL,separador);
    string nombre=token;
    token=strtok(NULL,separador);
    int cantidad=StrtoInt(token);
    token=strtok(NULL,separador);
    int precio=StrtoInt(token);
    pasnodo aux=primero;
    while(aux->siguiente!=primero)
    {
        if(aux->codigoP==pasillo)
        {
            break;
        }
        aux=aux->siguiente;
    }
    aux=primero->anterior;
    if(aux->codigoP==pasillo)
        {
            pronodo auxprod=aux->producto;
            while(auxprod->siguiente!=aux->producto)
            {
                if (auxprod->codigoProd==producto)
                {
                    auxprod->marca=new nodoMarca(marca,nombre,cantidad,precio);
                    auxprod->marca->anterior=auxprod->marca;
                    auxprod->marca->siguiente=auxprod->marca;
                }
                auxprod=auxprod->siguiente;
            }
            if (auxprod->codigoProd==producto)
            {
                auxprod->marca=new nodoMarca(marca,nombre,cantidad,precio);
                auxprod->marca->anterior=auxprod->marca;
                auxprod->marca->siguiente=auxprod->marca;
            }
        }
    while (getline(archivo,linea))
    {
        if(linea=="")
        {
        return;
        }
        bool repetido=false;
        char cstr[linea.size()+1];
        strcpy(cstr,linea.c_str());
        char*token= strtok(cstr,separador);
        string pasilloL=token;
        token=strtok(NULL,separador);
        string productoL=token;
        token=strtok(NULL,separador);
        string marcaL=token;
        token=strtok(NULL,separador);
        string nombreL=token;
        token=strtok(NULL,separador);
        int cantidadL=StrtoInt(token);
        token=strtok(NULL,separador);
        int precioL=StrtoInt(token);
        pasnodo auxL=primero;
        while(auxL->siguiente!=primero)
        {
            if (auxL->codigoP==pasilloL)
            {
                break;
            }


            auxL=auxL->siguiente;
        }
        if (auxL->codigoP==pasilloL)
        {
            pronodo aux2=auxL->producto;
            while(aux2->siguiente!=auxL->producto)
            {
                if (aux2->codigoProd==productoL)
                {
                    break;
                }
                aux2=aux2->siguiente;
            }
                if(aux2->codigoProd==productoL)
                {
                   if(aux2->marca==NULL)
                    {
                        aux2->marca=new nodoMarca(marcaL,nombreL,cantidadL,precioL);
                        aux2->marca->anterior=aux2->marca;
                        aux2->marca->siguiente=aux2->marca;
                    }
                    else
                    {
                        marnodo auxmar=aux2->marca;
                        while(auxmar->siguiente!=aux2->marca)
                        {
                            if(marcaL==auxmar->marca)
                            {
                                repetido=true;
                            }
                            auxmar=auxmar->siguiente;
                        }
                        if (marcaL==auxmar->marca)
                        {
                            repetido=true;
                        }
                        if(repetido==false)
                        {
                            auxmar->siguiente=new nodoMarca(marcaL,nombreL,cantidadL,precioL);
                            auxmar->siguiente->anterior=auxmar;
                            auxmar->siguiente->siguiente=aux2->marca;
                            aux2->marca->anterior=auxmar->siguiente;
                        }
                    }
                }
            }
        }
    archivo.close();
}

class listaClientes{
    ///Lista utilizada para almacenar los nodos de los clientes
 public:
    listaClientes() { primero = actual = NULL; }
    void InsertarInicio(string cedula,string nombre,string telefono,string correo);
    void InsertarFinal(string cedula,string nombre,string telefono,string correo);
    bool ListaVacia() { return primero == NULL; }
    void Imprimir();
    void Mostrar();
    void Siguiente();
    void Primero();
    int largoLista();
    void cargarClietes(string archivoC);
    void clienteMas(listaClientes clientes);
    void clienteMenos(listaClientes clientes);
    void masfacturas(listaClientes clientes);
    void sacarClientes(listaClientes clientes);
 private:
    clienodo primero;
    clienodo actual;
    friend class Menu;
};
int listaClientes::largoLista()
{
    int cont=0;

    clienodo aux = primero;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
}
void listaClientes::InsertarInicio(string cedula,string nombre,string telefono,string correo)
///Inserta al inicio de la lista de clientes
{
   if (ListaVacia())
   {
     primero = new nodoCliente(cedula,nombre,telefono,correo);
     primero->anterior=primero;
     primero->siguiente=primero;
   }
   else
   {
     clienodo nuevo=new nodoCliente(cedula,nombre,telefono,correo);
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
}

void listaClientes::InsertarFinal(string cedula,string nombre,string telefono,string correo)
///Inserta al final de la lista de clientes
{
   if (ListaVacia())
     {
     primero = new nodoCliente(cedula,nombre,telefono,correo);
     primero->anterior=primero;
     primero->siguiente=primero;
   }
   else
   {
     clienodo nuevo=new nodoCliente(cedula,nombre,telefono,correo);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }
}

void listaClientes::Mostrar()
{
   clienodo aux=primero;
   while(aux->siguiente!=primero)
     {

      cout << aux->nombre << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->nombre<<"->";
     cout<<endl;
}
void listaClientes::cargarClietes(string archivoC)
///Carga la lista de clientes con datos brindados desde un txt
{
    bool repetido=false;
    string linea;
    char separador[]=";";
    ifstream archivo(archivoC);
    getline(archivo,linea);
    if(linea=="")
    {
        return;
    }
    char cstr[linea.size()+1];
    strcpy(cstr,linea.c_str());
    char*token= strtok(cstr,separador);
    string cedula=token;
    token=strtok(NULL,separador);
    string nombre=token;
    token=strtok(NULL,separador);
    string numero=token;
    token=strtok(NULL,separador);
    string correo=token;
    InsertarFinal(cedula,nombre,numero,correo);
    while (getline(archivo,linea)){
        if(linea=="")
        {
            return;
        }
        char cstr[linea.size()+1];
        strcpy(cstr,linea.c_str());
        char*token= strtok(cstr,separador);
        string cedula=token;
        token=strtok(NULL,separador);
        string nombre=token;
        token=strtok(NULL,separador);
        string numero=token;
        token=strtok(NULL,separador);
        string correo=token;
        clienodo aux=primero;
        while(aux->siguiente!=primero){
            if (aux->cedula==cedula){
                repetido=true;
            }
            aux=aux->siguiente;
        }
        if(!repetido){
        token=strtok(NULL,separador);
        InsertarFinal(cedula,nombre,numero,correo);
    }
    }
    archivo.close();
}
class listaProductosCaja{
public:
    listaProductosCaja(){primero=actual=NULL;}
    void insertarProducto(conodo);
private:
    nodoCompra*primero;
    nodoCompra*actual;
};
class nodoInv{
    ///Nodo espec�ficamente pensado para ser implementado en el inventario
public:
    nodoInv(string pasillop,string productop,string marcap,string nombrep,int cantidadp,int canastaBp)
    {
        pasillo=pasillop;
        producto=productop;
        marca=marcap;
        nombre=nombrep;
        cantidad=cantidadp;
        canastaB=canastaBp;
    }
private:
    string pasillo;
    string producto;
    string marca;
    string nombre;
    int cantidad;
    int canastaB;
    nodoInv*siguiente;
    nodoInv*anterior;
    friend class inventario;
    friend class Menu;
};
typedef nodoInv*inodo;
class inventario{
    ///Lista doble circular para ser implementada con nodos inventario
public:
    inventario(){ primero = actual = NULL; }
    void InsertarFinal(string pasillop,string productop,string marcap,string nombrep,int cantidadp,int canastaBp);
    bool ListaVacia() { return primero == NULL; }
    void Mostrar();
    void Siguiente();
    void Primero();
    void cargarInventario(string invname);
    bool canasta(string pasillo,string producto,string marca);
    void sacarInv(inventario inven);
   private:
    inodo primero;
    inodo actual;
friend class Menu;
};
void inventario::sacarInv(inventario inven)
///In:inventario inven
///Out:File
///Funci�n:Genera reporte de stocks del inventario
{
ofstream outfile("InventarioR.txt");
outfile<<"Inventario/s registrados"<<endl;
inodo prod=inven.primero;
while(prod->siguiente!=inven.primero)
{
    outfile<<" Pasillo: "<<prod->pasillo<<" Producto: "<<prod->producto<<" Marca: "<<prod->marca<<" Nombre: "<<prod->nombre<<" Stock: "<<prod->cantidad<<endl;
    prod=prod->siguiente;
}
outfile<<" Pasillo: "<<prod->pasillo<<" Producto: "<<prod->producto<<" Marca: "<<prod->marca<<" Nombre: "<<prod->nombre<<" Stock: "<<prod->cantidad<<endl;
outfile.close();

}
void inventario::InsertarFinal(string pasillop,string productop,string marcap,string nombrep,int cantidadp,int canastaBp)
///Inserta al final del inventario
{
   if (ListaVacia())
     {
     primero = new nodoInv(pasillop,productop,marcap,nombrep,cantidadp,canastaBp);
     primero->anterior=primero;
     primero->siguiente=primero;
   }
   else
   {
     inodo nuevo = new nodoInv(pasillop,productop,marcap,nombrep,cantidadp,canastaBp);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }
}

void inventario::Mostrar()
{
   inodo aux=primero;
   while(aux->siguiente!=primero)
     {

      cout << aux->nombre << "-> ";
        aux = aux->siguiente;
     }
     cout<<endl;
}
bool inventario::canasta(string pasillop,string productop,string marcap)
///Retorna si  un producto posee canasta b�sica o no mediante un bool
{
    inodo buscador=primero;
    while(buscador->siguiente==NULL)
    {
        if(buscador->pasillo==pasillop)
        {
            if(buscador->producto==productop)
               {
                    if(buscador->marca==marcap)
                    {
                        break;
                    }
               }
        }
        buscador=buscador->siguiente;
    }
     if(buscador->pasillo==pasillop)
        {
            if(buscador->producto==productop)
               {
                    if(buscador->marca==marcap)
                    {
                        if(buscador->canastaB==0)
                        {
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
               }
        }

}
void inventario::cargarInventario(string pNombreArchivo)
///M�todo encargado de cargar el inventario desde un txt
{
bool repetido=false;
    string linea;
    char separador[]=";";
    ifstream archivo (pNombreArchivo);
    getline(archivo,linea);
    if(linea=="")
    {
        return;
    }
    char cstr[linea.size()+1];
    strcpy(cstr,linea.c_str());
    char*token= strtok(cstr,separador);
    string pasillo=token;
    token=strtok(NULL,separador);
    string producto=token;
    token=strtok(NULL,separador);
    string marca=token;
    token=strtok(NULL,separador);
    string nombre=token;
    token=strtok(NULL,separador);
    int cantidad=StrtoInt(token);
    token=strtok(NULL,separador);
    int canasta=StrtoInt(token);
    InsertarFinal(pasillo,producto,marca,nombre,cantidad,canasta);
    while (getline(archivo,linea)){
        if(linea=="")
        {
            return;
        }
        char cstr[linea.size()+1];
        strcpy(cstr,linea.c_str());
        char*token= strtok(cstr,separador);
        string pasillo=token;
        token=strtok(NULL,separador);
        string producto=token;
        token=strtok(NULL,separador);
        string marca=token;
        token=strtok(NULL,separador);
        string nombre=token;
        token=strtok(NULL,separador);
        int cantidad=StrtoInt(token);
        token=strtok(NULL,separador);
        int canasta=StrtoInt(token);
        inodo aux=primero;
        while(aux->siguiente!=primero){
            if (aux->marca==marca){
                repetido=true;
            }
            aux=aux->siguiente;
        }
        if(!repetido){
        InsertarFinal(pasillo,producto,marca,nombre,cantidad,canasta);
    }
   }
   archivo.close();
}
void listaDCPas::pasilloMV(listaDCPas super)
///In:listaDCPas super
///Out:File
///Funci�n:Genera reporte de pasillo más visitado
{   int mayor;
    pasnodo pasilloM;
    pasnodo pasillo=super.primero;
    mayor=pasillo->visitas;
    pasilloM=new nodoPasillo(pasillo->codigoP,pasillo->nombreP);
    pasillo=pasillo->siguiente;
    while(pasillo!=super.primero)
    {
        if(pasillo->visitas>mayor)
        {
            pasilloM=new nodoPasillo(pasillo->codigoP,pasillo->nombreP);
            mayor=pasillo->visitas;
        }
        else if(pasillo->visitas==mayor)
        {
            pasnodo recorM=pasilloM;
            while(recorM->siguiente!=NULL)
            {
                recorM=recorM->siguiente;
            }
            recorM->siguiente=new nodoPasillo(pasillo->codigoP,pasillo->nombreP);
        }
        pasillo=pasillo->siguiente;
    }

    ofstream outfile("Pasillo+Visitado.txt");
    outfile<<"Pasillo/s mas visitado"<<endl;
    while(pasilloM!=NULL)
    {
        outfile<<pasilloM->nombreP<<" "<<pasilloM->codigoP<<endl;
        pasilloM=pasilloM->siguiente;
    }
    outfile.close();

}
void listaDCPas::pasilloLV(listaDCPas super)
///In:listaDCPas super
///Out:File
///Funci�n:Genera reporte de pasillo menos visitado
{   int menor;
    pasnodo pasilloM;
    pasnodo pasillo=super.primero;
    menor=pasillo->visitas;
    pasilloM=new nodoPasillo(pasillo->codigoP,pasillo->nombreP);
    pasillo=pasillo->siguiente;
    while(pasillo!=super.primero)
    {
        if(pasillo->visitas<menor)
        {
            pasilloM=new nodoPasillo(pasillo->codigoP,pasillo->nombreP);
            menor=pasillo->visitas;
        }
        else if(pasillo->visitas==menor)
        {
            pasnodo recorM=pasilloM;
            while(recorM->siguiente!=NULL)
            {
                recorM=recorM->siguiente;
            }
            recorM->siguiente=new nodoPasillo(pasillo->codigoP,pasillo->nombreP);
        }
        pasillo=pasillo->siguiente;
    }

    ofstream outfile("Pasillo-Visitado.txt");
    outfile<<"Pasillo/s menos visitado"<<endl;
    int i=0;
    while(pasilloM!=NULL)
    {
        cout<<i<<endl;;
        outfile<<pasilloM->nombreP<<" "<<pasilloM->codigoP<<endl;
        pasilloM=pasilloM->siguiente;
        i++;
    }
    outfile.close();

}
void listaDCPas::prodPasillMv(listaDCPas super)
///In:listaDCPas super
///Out:File
///Funci�n:Genera reporte de productos más visitads
{   pasnodo pasillo=super.primero;
    while(pasillo->siguiente!=super.primero)
    {
    cout<<pasillo->nombreP<<"    C�digo: "<<pasillo->codigoP<<endl;
    pasillo=pasillo->siguiente;
    }
    cout<<pasillo->nombreP<<"    C�digo: "<<pasillo->codigoP<<endl;
    cout<<"Ingrese el pasillo a revisar: ";
    string pasillop;
    cin>>pasillop;
    pasillo=super.primero;
    while(pasillo->siguiente!=super.primero)
    {
    if(pasillo->codigoP==pasillop)
    {
        break;
    }
    pasillo=pasillo->siguiente;
    }
    if(pasillo->codigoP==pasillop)
    {
        int mayor;
        pronodo prodm;
        pronodo producto=pasillo->producto;
        mayor=producto->visitas;
        prodm=new nodoProducto(producto->codigoProd,producto->nombreProd);
        producto=producto->siguiente;
        while(producto!=pasillo->producto)
        {
            if(producto->visitas>mayor)
            {
                prodm=new nodoProducto(producto->codigoProd,producto->nombreProd);
                mayor=producto->visitas;
            }
            else if(producto->visitas==mayor)
            {
                pronodo recorM=prodm;
                while(recorM->siguiente!=NULL)
                {
                    recorM=recorM->siguiente;
                }
                recorM->siguiente=new nodoProducto(producto->codigoProd,producto->nombreProd);
            }
            producto=producto->siguiente;
        }

        ofstream outfile("ProductoPas.txt");
        outfile<<"Productos/s mas visitado"<<endl;
        while(prodm!=NULL)
        {
            outfile<<prodm->nombreProd<<" "<<prodm->codigoProd<<endl;
            prodm=prodm->siguiente;
        }
        outfile.close();
    }
    else{

        cout<<"No se encontr� ese c�digo de pasillo"<<endl;
    }
}
void listaDCPas::marcasV(listaDCPas super)
{
///In:listaDCPas super
///Out:File
///Funci�n:Genera reporte de marca más vendida
    int mayor=0;
    conodo mayorM;
    pasnodo pasillo=super.primero;
    int largo=super.largoLista();
    cout<<largo<<endl;
    while(pasillo->siguiente!=super.primero)
    {
        pronodo producto=pasillo->producto;
        while(producto->siguiente!=pasillo->producto)
        {
            marnodo marca=producto->marca;
            while(marca->siguiente!=producto->marca)
            {
                if(marca->visitas>mayor)
                {
                    mayor=marca->visitas;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                marca=marca->siguiente;
            }
            if(marca->visitas>mayor)
                {
                    mayor=marca->visitas;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
            producto=producto->siguiente;
        }
        marnodo marca=producto->marca;
            while(marca->siguiente!=producto->marca)
            {
                if(marca->visitas>mayor)
                {
                    mayor=marca->visitas;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                marca=marca->siguiente;
            }
            if(marca->visitas>mayor)
                {
                    mayor=marca->visitas;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    if(recorrm==NULL)
                    {
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                    }
                    else
                    {
                        while(recorrm->siguiente!=NULL)
                        {
                            recorrm=recorrm->siguiente;
                        }
                        recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                    }
                }
        pasillo=pasillo->siguiente;
    }
            pronodo producto=pasillo->producto;
        while(producto->siguiente!=pasillo->producto)
        {
            marnodo marca=producto->marca;
            while(marca->siguiente!=producto->marca)
            {
                if(marca->visitas>mayor)
                {
                    mayor=marca->visitas;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                marca=marca->siguiente;
            }
            if(marca->visitas>mayor)
                {
                    mayor=marca->visitas;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
            producto=producto->siguiente;
        }
        marnodo marca=producto->marca;
            while(marca->siguiente!=producto->marca)
            {
                if(marca->visitas>mayor)
                {
                    mayor=marca->visitas;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                marca=marca->siguiente;
            }
            if(marca->visitas>mayor)
                {
                    mayor=marca->visitas;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    if(recorrm==NULL)
                    {
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                    }
                    else
                    {
                        while(recorrm->siguiente!=NULL)
                        {
                            recorrm=recorrm->siguiente;
                        }
                        recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                    }
                }
    ofstream outfile("Marcas+V.txt");
    outfile<<"Marcas mas vendidas"<<endl;
    while(mayorM!=NULL)
    {
        outfile<<"Pasillo: "<<mayorM->pasillo<<" Producto: "<<mayorM->producto<<" Marca: "<<mayorM->marca<<" Nombre: "<<mayorM->nombre<<" Compras: "<<mayorM->cantidad<<endl;
        mayorM=mayorM->siguiente;
    }
    outfile.close();


}
void listaClientes::clienteMas(listaClientes clientes)
///In:listaClientes clientes
///Out:File
///Funcion:Genera reporte del cliente que más compró
{
    int mayor;
    clienodo clienteM;
    clienodo cliente=clientes.primero;
    mayor=cliente->mayor;
    clienteM=new nodoCliente(cliente->cedula,cliente->nombre,cliente->telefono,cliente->correo,cliente->mayor);
    cliente=cliente->siguiente;
    while(cliente!=clientes.primero)
    {
        if(cliente->mayor>mayor)
        {
            clienteM=clienteM=new nodoCliente(cliente->cedula,cliente->nombre,cliente->telefono,cliente->correo,cliente->mayor);
            mayor=cliente->mayor;
        }
        else if(cliente->mayor==mayor)
        {
            clienodo recorM=clienteM;
            while(recorM->siguiente!=NULL)
            {
                recorM=recorM->siguiente;
            }
            recorM->siguiente=new nodoCliente(cliente->cedula,cliente->nombre,cliente->telefono,cliente->correo,cliente->mayor);
        }
        cliente=cliente->siguiente;
    }

    ofstream outfile("ClienteMas.txt");
    outfile<<"Clientes/s que más pagó"<<endl;
    while(clienteM!=NULL)
    {
        outfile<<"Nombre: "<<clienteM->nombre<<" Monto: "<<clienteM->mayor<<endl;
        clienteM=clienteM->siguiente;
    }
    outfile.close();

}
void listaClientes::clienteMenos(listaClientes clientes)
///In:listaClientes clientes
///Out:File
///Funci�n:Genera reporte de el cliente que menos pagó
{
int mayor;
    clienodo clienteM;
    clienodo cliente=clientes.primero;
    mayor=cliente->mayor;
    clienteM=new nodoCliente(cliente->cedula,cliente->nombre,cliente->telefono,cliente->correo,cliente->mayor);
    cliente=cliente->siguiente;
    while(cliente!=clientes.primero)
    {
        if(cliente->mayor<mayor)
        {
            clienteM=clienteM=new nodoCliente(cliente->cedula,cliente->nombre,cliente->telefono,cliente->correo,cliente->mayor);
            mayor=cliente->mayor;
        }
        else if(cliente->mayor==mayor)
        {
            clienodo recorM=clienteM;
            while(recorM->siguiente!=NULL)
            {
                recorM=recorM->siguiente;
            }
            recorM->siguiente=new nodoCliente(cliente->cedula,cliente->nombre,cliente->telefono,cliente->correo,cliente->mayor);
        }
        cliente=cliente->siguiente;
    }

    ofstream outfile("ClienteMenos.txt");
    outfile<<"Clientes/s que menos pagó"<<endl;
    while(clienteM!=NULL)
    {
        outfile<<"Nombre: "<<clienteM->nombre<<" Monto: "<<clienteM->mayor<<endl;
        clienteM=clienteM->siguiente;
    }
    outfile.close();
}
void listaClientes::masfacturas(listaClientes clientes)
///In:listaClientes clientes
///Out:File
///Funci�n:Genera reporte del cliente que más facturas hizo
{
    int mayor;
    clienodo clienteM;
    clienodo cliente=clientes.primero;
    mayor=cliente->facturas;
    clienteM=new nodoCliente(cliente->cedula,cliente->nombre,cliente->telefono,cliente->correo,cliente->facturas);
    cliente=cliente->siguiente;
    while(cliente!=clientes.primero)
    {
        if(cliente->facturas>mayor)
        {
            clienteM=clienteM=new nodoCliente(cliente->cedula,cliente->nombre,cliente->telefono,cliente->correo,cliente->facturas);
            mayor=cliente->facturas;
        }
        else if(cliente->facturas==mayor)
        {
            clienodo recorM=clienteM;
            while(recorM->siguiente!=NULL)
            {
                recorM=recorM->siguiente;
            }
            recorM->siguiente=new nodoCliente(cliente->cedula,cliente->nombre,cliente->telefono,cliente->correo,cliente->facturas);
        }
        cliente=cliente->siguiente;
    }

    ofstream outfile("ClienteMasF.txt");
    outfile<<"Clientes/s que más facturó"<<endl;
    while(clienteM!=NULL)
    {
        outfile<<"Nombre: "<<clienteM->nombre<<" Facturas: "<<clienteM->mayor<<endl;
        clienteM=clienteM->siguiente;
    }
    outfile.close();

}
void listaDCPas::marcasPasProd(listaDCPas super)
///In:listaDCPas super, string pasillo, string producto
///Out:File
///Funci�n:Genera reporte de las marcas que hay en el pasillo y producto seleccionados
{
string pasillos;
pasnodo pasillo=super.primero;
while(pasillo->siguiente!=super.primero)
{
    cout<<"Pasillo "<<pasillo->codigoP<<" "<<pasillo->nombreP<<endl;
    pasillo=pasillo->siguiente;
}
cout<<"Pasillo "<<pasillo->codigoP<<" "<<pasillo->nombreP<<endl;
cout<<"Codigo de pasillo: ";
cin>>pasillos;
pasillo=super.primero;
while(pasillo->siguiente!=super.primero)
{
    if(pasillo->codigoP==pasillos)
    {
        break;
    }
    pasillo=pasillo->siguiente;
}
if(pasillo->codigoP==pasillos)
{
    pronodo producto=pasillo->producto;
    string productos;
    while(producto->siguiente!=pasillo->producto)
    {
        cout<<"Producto "<<producto->codigoProd<<" "<<producto->nombreProd<<endl;
        producto=producto->siguiente;
    }
    cout<<"Producto "<<producto->codigoProd<<" "<<producto->nombreProd<<endl;
    cout<<"Ingrese cod producto: ";
    cin>>productos;
    producto=pasillo->producto;
    while(producto->siguiente!=pasillo->producto)
    {
        if(producto->codigoProd==productos)
        {
            break;
        }
        producto=producto->siguiente;
    }
    if(producto->codigoProd==productos)
    {
        marnodo marcas=producto->marca;
        ofstream outfile("MarcxProdxPas.txt");
        outfile<<"Marcas/s por pasillo/producto"<<endl;
        while (marcas->siguiente!=producto->marca)
        {
            outfile<<"Nombre: "<<marcas->nombre<<" Precio: "<<marcas->precio<<"Codigo: "<<marcas->marca<<endl;
            marcas=marcas->siguiente;
        }
        outfile<<"Nombre: "<<marcas->nombre<<" Precio: "<<marcas->precio<<" Codigo: "<<marcas->marca<<endl;
        outfile.close();

    }

}
else
{
    ofstream outfile("MarcxProdxPas.txt");
    outfile<<"No se encontró"<<endl;
    outfile.close();
}

}
void listaDCPas::productosPas(listaDCPas super)
///In:listaDCPas super, string pasillo
///Out:File
///Funci�n:Genera reporte de los productos que hay en un pasillo seleccionado
{
string pasillos;
pasnodo pasillo=super.primero;
while(pasillo->siguiente!=super.primero)
{
    cout<<"Pasillo "<<pasillo->codigoP<<" "<<pasillo->nombreP<<endl;
    pasillo=pasillo->siguiente;
}
cout<<"Pasillo "<<pasillo->codigoP<<" "<<pasillo->nombreP<<endl;
cout<<"Codigo de pasillo: ";
cin>>pasillos;
pasillo=super.primero;
while(pasillo->siguiente!=super.primero)
{
    if(pasillo->codigoP==pasillos)
    {
        break;
    }
    pasillo=pasillo->siguiente;
}
if(pasillo->codigoP==pasillos)
{
    pronodo producto=pasillo->producto;
    string productos;
    ofstream outfile("ProdxPas.txt");
    outfile<<"Productos/s por pasillo"<<endl;
    while(producto->siguiente!=pasillo->producto)
    {
        outfile<<"Producto "<<producto->codigoProd<<" "<<producto->nombreProd<<endl;
        producto=producto->siguiente;
    }
    outfile<<"Producto "<<producto->codigoProd<<" "<<producto->nombreProd<<endl;
    outfile.close();
}
else
{
     ofstream outfile("ProdxPas.txt");
    outfile<<"No se encontró"<<endl;
    outfile.close();
}

}
void listaClientes::sacarClientes(listaClientes clientes)
///In:listaClientes clientes
///Out:File
///Funci�n:Genera reporte de los clientes registrados
{
    ofstream outfile("ClientesR.txt");
    outfile<<"Cliente/s registrados"<<endl;
    clienodo cliente=clientes.primero;
    while(cliente->siguiente!=clientes.primero)
    {
        outfile<<"Cliente "<<cliente->nombre<<" Cedula: "<<cliente->cedula<<" Telefono: "<<cliente->telefono<<" Email: "<<cliente->correo<<endl;
        cliente=cliente->siguiente;
    }
    outfile<<"Cliente "<<cliente->nombre<<" Cedula: "<<cliente->cedula<<" Telefono: "<<cliente->telefono<<" Email: "<<cliente->correo<<endl;
    outfile.close();
}
void listaDCPas::sacarPas(listaDCPas super)
///In:listaDCPas super
///Out:File
///Funci�n:Genera reporte de todos los pasillos del supermercado
{
    pasnodo pasillo=super.primero;
    ofstream outfile("PasillosR.txt");
    outfile<<"Pasillos/s registrados"<<endl;
    while (pasillo->siguiente!=super.primero)
    {
        outfile<<"Pasillo "<<pasillo->nombreP<<" "<<pasillo->codigoP<<endl;
        pasillo=pasillo->siguiente;
    }
    outfile<<"Pasillo "<<pasillo->nombreP<<""<<pasillo->codigoP<<endl;
    outfile.close();
}
void listaDCPas::sacarMR(listaDCPas super)
///In:listaDCPas super
///Out:File
///Funci�n:Genera reporte de las marcas que más fueron recargadas en góndola
{
    int mayor=0;
    conodo mayorM;
    pasnodo pasillo=super.primero;
    int largo=super.largoLista();
    cout<<largo<<endl;
    while(pasillo->siguiente!=super.primero)
    {
        pronodo producto=pasillo->producto;
        while(producto->siguiente!=pasillo->producto)
        {
            marnodo marca=producto->marca;
            while(marca->siguiente!=producto->marca)
            {
                if(marca->recarga>mayor)
                {
                    mayor=marca->recarga;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->recarga==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                marca=marca->siguiente;
            }
            if(marca->visitas>mayor)
                {
                    mayor=marca->recarga;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->recarga==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
            producto=producto->siguiente;
        }
        marnodo marca=producto->marca;
            while(marca->siguiente!=producto->marca)
            {
                if(marca->recarga>mayor)
                {
                    mayor=marca->recarga;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                marca=marca->siguiente;
            }
            if(marca->recarga>mayor)
                {
                    mayor=marca->recarga;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->recarga==mayor)
                {
                    conodo recorrm=mayorM;
                    if(recorrm==NULL)
                    {
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                    }
                    else
                    {
                        while(recorrm->siguiente!=NULL)
                        {
                            recorrm=recorrm->siguiente;
                        }
                        recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                    }
                }
        pasillo=pasillo->siguiente;
    }
            pronodo producto=pasillo->producto;
        while(producto->siguiente!=pasillo->producto)
        {
            marnodo marca=producto->marca;
            while(marca->siguiente!=producto->marca)
            {
                if(marca->recarga>mayor)
                {
                    mayor=marca->recarga;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->visitas==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                marca=marca->siguiente;
            }
            if(marca->recarga>mayor)
                {
                    mayor=marca->recarga;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->recarga==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm->siguiente!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
            producto=producto->siguiente;
        }
        marnodo marca=producto->marca;
            while(marca->siguiente!=producto->marca)
            {
                if(marca->recarga>mayor)
                {
                    mayor=marca->recarga;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->recarga==mayor)
                {
                    conodo recorrm=mayorM;
                    while(recorrm!=NULL)
                    {
                        recorrm=recorrm->siguiente;
                    }
                    recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                marca=marca->siguiente;
            }
            if(marca->recarga>mayor)
                {
                    mayor=marca->visitas;
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                }
                else if(marca->recarga==mayor)
                {
                    conodo recorrm=mayorM;
                    if(recorrm==NULL)
                    {
                    mayorM=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                    }
                    else
                    {
                        while(recorrm->siguiente!=NULL)
                        {
                            recorrm=recorrm->siguiente;
                        }
                        recorrm->siguiente=new nodoCompra( pasillo->codigoP, producto->codigoProd, marca->marca, marca->nombre,mayor);
                    }
                }
    ofstream outfile("Marcas+R.txt");
    outfile<<"Marcas mas Recargadas"<<endl;
    while(mayorM!=NULL)
    {
        outfile<<"Pasillo: "<<mayorM->pasillo<<" Producto: "<<mayorM->producto<<" Marca: "<<mayorM->marca<<" Nombre: "<<mayorM->nombre<<" Recarga: "<<mayorM->cantidad<<endl;
        mayorM=mayorM->siguiente;
    }
    outfile.close();
}
/// Código tomado de geeksforgeeks
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


#endif // LISTAS_H_INCLUDED


