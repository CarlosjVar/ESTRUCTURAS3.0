#ifndef BINARIO_H_INCLUDED
#define BINARIO_H_INCLUDED
#include "Rojinegro.h"
#include "Pila.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


class Binario{
public:
    pNodoBinario raiz;

    Binario():raiz(NULL){}

    void cargarProductos (string pNombreArchivo);
    void InsertaNodo(int num, string nombre);
    void PreordenI();
    void InordenI();
    string InordenCliente();
    void PostordenI();
    void PostordenG(pNodoBinario pRaiz);
    void cargarPasillos (string pNombreArchivo);
    void cargarMarcas (string pNombreArchivo);
    void rellenarGondolaBinario (AA inventario);
    void rellenarGondolaBinario (pNodoBinario raiz, AA inventario);
    void reporteMarcaMasVendidaBinario (string &texto);
    void reporteMarcaMasVendidaBinario (string &texto, pNodoBinario raiz,int &mayor );
    void mayorCantidadDeVentas (pNodoBinario raiz, int &mayor);
    void reportePasillos (string &texto);
    void reportePasillos (string &texto, pNodoBinario raiz);
    void reportePasilloMasVisitado (string &texto);
    void reportePasilloMasVisitado (string &texto, pNodoBinario raiz, int mayor);
    void  cantidadMayorDeVisitas (int &mayor, pNodoBinario raiz);
    void  cantidadMenorDeVisitas (int &menor, pNodoBinario raiz);
    void reportePasilloMenosVisitado (string &texto);
    void reportePasilloMenosVisitado (string &texto, pNodoBinario raiz, int menor);
    bool Hh = false;
};



class BinarioAVL{
public:
    pNodoBinarioAVL raiz;
    BinarioAVL():raiz(NULL){}
    void PreordenI();
    void InordenI();
    void PostordenI();
    void PostordenG(pNodoBinarioAVL pRaiz);
    bool Hh = false;

    void Equilibrar1(NodoBinarioAVL *n, bool);
    void Equilibrar2(NodoBinarioAVL *n, bool);
    void InsertarBalanceado(NodoBinarioAVL*&r, bool &Hh, int x, string nombre);
    void RotacionDobleIzquierda(NodoBinarioAVL *&n1, NodoBinarioAVL *&n2);
    void RotacionDobleDerecha(NodoBinarioAVL *&n1, NodoBinarioAVL *&n2);
    void RotacionSimpleIzquierda(NodoBinarioAVL *&n1, NodoBinarioAVL *&n2);
    void RotacionSimpleDerecha(NodoBinarioAVL *&n1, NodoBinarioAVL *&n2);
    void rellenarGondolaAVL (pnodoAVL raiz, int codigoPasillo, AA inventario);
    void reporteProductos (string &texto,pnodoAVL raiz);
    void reporteMarcaMasVendidaAVL (string &texto, pnodoAVL raiz, int &mayor);
    void mayorCantidadDeVentasAVL (pnodoAVL raiz,int &mayor);
    void reporteProductoMasVendido (string &texto);
    void reporteProductoMasVendido (string &texto, pNodoBinarioAVL raiz, int mayor);
    void  cantidadMayorDeVentas (int &mayor, pNodoBinarioAVL raiz);
};
pNodoBinario buscarNodo(pNodoBinario pRaiz, int valor);
pNodoBinarioAVL buscarNodoAVL(pNodoBinarioAVL pRaiz, int valor);
#endif // BINARIO_H_INCLUDED
