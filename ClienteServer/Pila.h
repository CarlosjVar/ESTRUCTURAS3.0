#ifndef PILA_H
#define PILA_H
#include "Nodos.h"
#include <iostream>
using namespace std;


class Pila {
   public:
    Pila() : plista(NULL) {}

    void Push(pnodo);
    void Mostrar();
    bool Vacia() { return plista == NULL; }
    pnodo Pop();
    int Size();

    pnodo plista;
};


class PilaAVL {
   public:
    PilaAVL() : plista(NULL) {}

    void Push(pnodoAVL);
    void Mostrar();
    bool Vacia() { return plista == NULL; }
    pnodoAVL Pop();
    int Size();

    pnodoAVL plista;
};


#endif
