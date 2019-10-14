#include "AA.h"
pnodoAA AA::buscarNodoAA(int valor){
    return buscarNodoAA(this->raiz, valor);
}

pnodoAA AA::buscarNodoAA(pnodoAA pRaiz, int valor)
{
    if (pRaiz == NULL || pRaiz->valor == valor)
       return pRaiz;
    if (pRaiz->valor < valor)
       return buscarNodoAA(pRaiz->hDer, valor);
    return buscarNodoAA(pRaiz->hIzq, valor);
}

void AA::Inorden(){
    Inorden(this->raiz);
}

void AA::Postorden(){
    Postorden(this->raiz);
}

void AA::Inorden(pnodoAA R){
 if(R==NULL){
        return;
    }else{
        Inorden(R->hIzq);
        cout<<R->valor<<","<<R->nombre<<" -> ";
        Inorden(R->hDer);
    }
}

void AA::Postorden(pnodoAA R){
 if(R==NULL){
        return;
    }else{

        Postorden(R->hIzq);
        Postorden(R->hDer);
        cout<<R->valor<<","<<R->nombre<<" -> ";
    }
}

void AA::insertar (int val, int codigoPasillo, int codigoProducto, int codigoMarca, string nombre, int cantidadStock, int canastaB){
    this->raiz = insertar(this->raiz,  val,  codigoPasillo,  codigoProducto,  codigoMarca,  nombre,  cantidadStock, canastaB);
}

pnodoAA AA::insertar(pnodoAA aux, int val, int codigoPasillo, int codigoProducto, int codigoMarca, string nombre, int cantidadStock, int canastaB)
{
    if (aux==NULL){
        aux=new nodoAA(val);
        aux->codigoPasillo = codigoPasillo;
        aux->codigoProducto = codigoProducto;
        aux->codigoMarca = codigoMarca;
        aux->nombre = nombre;
        aux->cantidadStock = cantidadStock;
        aux->canastaB = canastaB;
    }
    else if (val<aux->valor){
        aux->hIzq=insertar(aux->hIzq, val,  codigoPasillo,  codigoProducto,  codigoMarca,  nombre, cantidadStock, canastaB);
    }
    else if (val>aux->valor){
        aux->hDer=insertar(aux->hDer, val,  codigoPasillo,  codigoProducto,  codigoMarca,  nombre, cantidadStock, canastaB);
    }
    else {
        cout<<"Repetido"<<endl;
        return aux;
    }
    aux=giro(aux);
    aux=reparto(aux);
    return aux;
}

pnodoAA AA::giro( pnodoAA aux )
{
    if (aux->hIzq==NULL){
        return aux;
    }
    if(aux->hIzq->nivel == aux->nivel ){
        aux= rotarIzquierda( aux );
    }
    return aux;
}

pnodoAA AA::reparto(pnodoAA aux)
{
    if (aux->hDer==NULL){
        return aux;
    }
    if( aux->hDer->nivel == aux->nivel && aux->hDer->hDer!=NULL && aux->hDer->hDer->nivel==aux->nivel)
    {
        aux= rotarDerecha(aux);
        aux->nivel++;
    }
    return aux;
}
pnodoAA AA::rotarIzquierda(pnodoAA aux)
{
    pnodoAA otro=aux->hIzq;
    aux->hIzq = otro->hDer;
    otro->hDer= aux;
    return otro;
}
/**
* Rotate binary tree node with right child.
* For AVL trees, this is a single rotation for case 4.
*/
pnodoAA AA::rotarDerecha(pnodoAA aux)
{
    pnodoAA otro = aux->hDer;
    aux->hDer= otro->hIzq;
    otro->hIzq=aux;
    return otro;
}

void AA::cargarInventario(string pNombreArchivo){
    string linea;
    int codigoPasillo;
    int codigoProducto;
    int codigoMarca;
    int cantidadStock;
    int codigo;
    string codigoS;
    string nombre;
    int canastaB;
    string canastaBS;
    string cantidadStockS;
    string codigoMarcaS;
    string codigoProductoS;
    string codigoPasilloS;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,codigoPasilloS,';');
        getline(lineaActual,codigoProductoS,';');
        getline(lineaActual,codigoMarcaS,';');
        getline(lineaActual,nombre,';');
        getline(lineaActual,cantidadStockS,';');
        getline(lineaActual,canastaBS,';');
        codigoMarca = stoi (codigoMarcaS);
        codigoPasillo = stoi (codigoPasilloS);
        canastaB = stoi (canastaBS);
        codigoProducto = stoi (codigoProductoS);
        cantidadStock = stoi (cantidadStockS);
        codigoS = codigoPasilloS + codigoProductoS + codigoMarcaS;
        codigo = stoi (codigoS);
        pnodoAA aux = buscarNodoAA(codigo);
        if (aux==NULL){
            insertar(codigo, codigoPasillo, codigoProducto, codigoMarca, nombre, cantidadStock, canastaB);
        }
    }
    archivo.close();
}
