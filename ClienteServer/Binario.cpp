#include "Binario.h"

pNodoBinario buscarNodo(pNodoBinario pRaiz, int valor)
{
    if (pRaiz == nullptr || pRaiz->valor == valor)
       return pRaiz;
    if (pRaiz->valor < valor)
       return buscarNodo(pRaiz->Hder, valor);
    return buscarNodo(pRaiz->Hizq, valor);
}

pNodoBinarioAVL buscarNodoAVL(pNodoBinarioAVL pRaiz, int valor)
{
    if (pRaiz == nullptr || pRaiz->valor == valor)
       return pRaiz;
    if (pRaiz->valor < valor)
       return buscarNodoAVL(pRaiz->Hder, valor);
    return buscarNodoAVL(pRaiz->Hizq, valor);
}

void Binario::reporteMarcaMasVendidaBinario(string &texto){
    int mayor = 0;
    mayorCantidadDeVentas(this->raiz, mayor);
    if (mayor==0){
        texto.append("No se ha vendido ninguna marca aún");
        return;
    }
    reporteMarcaMasVendidaBinario(texto, this->raiz,mayor);
    return;
}

void Binario::reporteMarcaMasVendidaBinario(string &texto,pNodoBinario raiz,int &mayor){
    if (raiz==NULL){
        return;
    }
    reporteMarcaMasVendidaBinario(texto,raiz->Hder,mayor);
    reporteMarcaMasVendidaBinario(texto,raiz->Hizq,mayor);
    BinarioAVL temp = BinarioAVL();
    temp.reporteMarcaMasVendidaAVL(texto,raiz->productos,mayor);
}

void BinarioAVL::reporteMarcaMasVendidaAVL(string &texto, pnodoAVL raiz, int &mayor){
    if (raiz==NULL){
        return;
    }
    reporteMarcaMasVendidaAVL(texto, raiz->Hder,mayor);
    reporteMarcaMasVendidaAVL(texto, raiz->Hizq,mayor);
    RBTree temp = RBTree (raiz->marcas);
    temp.reporteMarcaMasVendida(texto,mayor);
}


void Binario::mayorCantidadDeVentas(pNodoBinario raiz, int &mayor){
    if (raiz==NULL){
        return;
    }
    mayorCantidadDeVentas(raiz->Hder,mayor);
    mayorCantidadDeVentas(raiz->Hizq,mayor);
    BinarioAVL temp = BinarioAVL();
    temp.mayorCantidadDeVentasAVL(raiz->productos,mayor);
}

void BinarioAVL::mayorCantidadDeVentasAVL(pnodoAVL raiz, int &mayor){
    if (raiz==NULL){
        return;
    }
    mayorCantidadDeVentasAVL(raiz->Hder,mayor);
    mayorCantidadDeVentasAVL(raiz->Hizq,mayor);
    RBTree temp = RBTree (raiz->marcas);
    temp.mayorCantidadDeVentasRN(mayor);
}


void Binario::reportePasilloMasVisitado(string &texto){
    int mayor;
    cantidadMayorDeVisitas(mayor, this->raiz);
    if (mayor==0){
        texto.append("No se ha visitado ningún pasillo aún");
        return;
    }
    reportePasilloMasVisitado(texto, this->raiz,mayor);
    return;
}

void Binario::cantidadMayorDeVisitas(int &mayor, pNodoBinario raiz){
    if (raiz==NULL){
        return;
    }
    else
    {
        cantidadMayorDeVisitas(mayor,raiz->Hder);
        cantidadMayorDeVisitas(mayor,raiz->Hizq);
        if (raiz->cantidadVisitas>mayor){
            mayor=raiz->cantidadVisitas;
            return;
        }
    }
    return;
}

void Binario::cantidadMenorDeVisitas(int &mayor, pNodoBinario raiz){
    if (raiz==NULL){
        return;
    }
    else
    {
        cantidadMenorDeVisitas(mayor,raiz->Hder);
        cantidadMenorDeVisitas(mayor,raiz->Hizq);
        if (raiz->cantidadVisitas<mayor){
            mayor=raiz->cantidadVisitas;
            return;
        }
    }
    return;
}

void Binario::reportePasilloMasVisitado(string &texto, pNodoBinario raiz, int mayor){
    if (raiz==NULL){
        return;
    }
    else
    {
        reportePasilloMasVisitado(texto,raiz->Hder,mayor);
        reportePasilloMasVisitado(texto,raiz->Hizq,mayor);
        if (raiz->cantidadVisitas==mayor){
            texto.append("-Codigo: ");
            texto.append(to_string(raiz->valor));
            texto.append(", Nombre de pasillo: ");
            texto.append(raiz->nombre);
            texto.append("\n");
        }
    }
    return;
}

void Binario::reportePasilloMenosVisitado(string &texto, pNodoBinario raiz, int menor){
    if (raiz==NULL){
        return;
    }
    else
    {
        reportePasilloMenosVisitado(texto,raiz->Hder,menor);
        reportePasilloMenosVisitado(texto,raiz->Hizq,menor);
        if (raiz->cantidadVisitas==menor){
            texto.append("-Codigo: ");
            texto.append(to_string(raiz->valor));
            texto.append(", Nombre de pasillo: ");
            texto.append(raiz->nombre);
            texto.append("\n");
        }
    }
    return;
}


void Binario::reportePasilloMenosVisitado(string &texto){
    int menor = this->raiz->cantidadVisitas;
    cantidadMenorDeVisitas(menor, this->raiz);
    reportePasilloMenosVisitado(texto, this->raiz,menor);
    return;
}


void Binario::reportePasillos (string &texto){
    reportePasillos(texto,this->raiz);
}

void Binario::reportePasillos(string &texto,pNodoBinario raiz){
    if (raiz==NULL){
        return;
    }
    else
    {
        reportePasillos(texto,raiz->Hder);
        reportePasillos(texto,raiz->Hizq);
        texto.append("-Codigo: ");
        texto.append(to_string(raiz->valor));
        texto.append(", Nombre de pasillo: ");
        texto.append(raiz->nombre);
        texto.append("\n");
        return;
    }
}

void Binario::cargarPasillos(string pNombreArchivo){
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
        if (raiz==nullptr){
            InsertaNodo(codigo,nombre);
        }else{
            pNodoBinario aux = buscarNodo(raiz,codigo);
            if (aux==NULL){
                InsertaNodo(codigo,nombre);
            }
        }
    }
    archivo.close();
}

void Binario::rellenarGondolaBinario(AA inventario){
    rellenarGondolaBinario(this->raiz,inventario);
}

void Binario::rellenarGondolaBinario(pNodoBinario raiz, AA inventario){
    if (raiz==NULL){
        return;
    }
    rellenarGondolaBinario(raiz->Hder, inventario);
    rellenarGondolaBinario(raiz->Hizq,inventario);
    BinarioAVL temp = BinarioAVL();
    temp.rellenarGondolaAVL(raiz->productos, raiz->valor,inventario);
}

void Binario::InsertaNodo(int num,string nombre)
{
    if(raiz==NULL){
        raiz = new NodoBinario(num,nombre);
    }else{
        raiz->InsertaBinario(num,nombre);
    }
}

void Binario::PreordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    while(p.Vacia()==false || (Act!=NULL)){
        if(Act!=NULL){
            cout<<Act->valor<<","<<Act->nombre<<" - ";
            p.Push(Act);
            Act = Act->Hizq;
        }else{
            Act=p.Pop();
            Act=Act->Hder;
        }
    }
}

void Binario::InordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    bool band=true;
    while(band){
        while(Act!=NULL){
            p.Push(Act);
            Act = Act->Hizq;
        }
        if(!p.Vacia()){
            Act=p.Pop();
            cout<<Act->valor<<","<<Act->nombre<<" - ";
            Act=Act->Hder;
        }
        if(p.Vacia() & Act==NULL){
            break;
        }
    }
}

void Binario::PostordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    Pila p2;
    while(!p.Vacia() || Act!=NULL){
        if(Act!=NULL){
            p2.Push(new NodoBinario(Act->valor,Act->nombre));
            p.Push(Act);
            Act = Act->Hder;
        }else{
            Act=p.Pop();
            Act = Act->Hizq;
        }
    }
    while(!p2.Vacia()){
        NodoBinario *salida=p2.Pop();
        cout<<Act->valor<<","<<Act->nombre<<" - ";
    }
}

void Binario::PostordenG(pNodoBinario pRaiz)
{
    if (pRaiz == NULL)
        return;
    PostordenG(pRaiz->Hizq);
    PostordenG(pRaiz->Hder);
    cout<<pRaiz->valor<<","<<pRaiz->nombre<<" - ";
}
void Binario::cargarProductos (string pNombreArchivo){
    string linea;
    string codigoS;
    int codigo;
    string codigoPasilloS;
    int codigoPasillo;
    string nombre;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,codigoPasilloS,';');
        getline(lineaActual,codigoS,';');
        getline(lineaActual,nombre,';');
        codigo = stoi (codigoS);;
        codigoPasillo = stoi (codigoPasilloS);
        pNodoBinario aux = buscarNodo(raiz,codigoPasillo);
        if (aux!=NULL){
                if (aux->productos!=NULL){
                    pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigo);
                    if (aux2==NULL){
                        BinarioAVL B3;
                        B3.InsertarBalanceado (aux->productos,B3.Hh,codigo,nombre);
                    }
                }else{
                    aux->productos = new NodoBinarioAVL (codigo,nombre);
                }
        }
    }
    return;
}

void Binario::cargarMarcas (string pNombreArchivo){
    string linea;
    int codigoPasillo;
    int codigoProducto;
    int codigo;
    int cantidadGondola;
    string nombre;
    int precio;
    string precioS;
    string cantidadGondolaS;
    string codigoS;
    string codigoProductoS;
    string codigoPasilloS;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,codigoPasilloS,';');
        getline(lineaActual,codigoProductoS,';');
        getline(lineaActual,codigoS,';');
        getline(lineaActual,nombre,';');
        getline(lineaActual,cantidadGondolaS,';');
        getline(lineaActual,precioS,';');
        codigo = stoi (codigoS);
        codigoPasillo = stoi (codigoPasilloS);
        precio = stoi (precioS);
        codigoProducto = stoi (codigoProductoS);
        cantidadGondola = stoi (cantidadGondolaS);
        pNodoBinario aux = buscarNodo(raiz,codigoPasillo);
        if (aux!=NULL){
            pNodoBinarioAVL aux2 = buscarNodoAVL(aux->productos,codigoProducto);
            if (aux2!=NULL){
                if (aux2->marcas==NULL){
                    RBTree temp = RBTree();
                    temp.insert(codigo,nombre,precio,cantidadGondola);
                    aux2->marcas = temp.root;
                }else{
                    RBTree temp = RBTree();
                    temp.root = aux2->marcas;
                    NodePtr aux3 = temp.searchTree(codigo);
                    if (aux3==NULL){
                        temp.insert(codigo,nombre,precio,cantidadGondola);
                        aux2->marcas = temp.root;
                    }
                }
            }
        }
    }
    archivo.close();
    return;
}

void BinarioAVL::reporteProductoMasVendido(string &texto){
    int mayor;
    cantidadMayorDeVentas(mayor, this->raiz);
    if (mayor==0){
        texto.append("No se han vendido productos aún");
        return;
    }
    reporteProductoMasVendido(texto, this->raiz,mayor);
    return;
}

void BinarioAVL::cantidadMayorDeVentas(int &mayor, pNodoBinarioAVL raiz){
    if (raiz==NULL){
        return;
    }
    else
    {
        cantidadMayorDeVentas(mayor,raiz->Hder);
        cantidadMayorDeVentas(mayor,raiz->Hizq);
        if (raiz->cantidadVentas>mayor){
            mayor=raiz->cantidadVentas;
            return;
        }
    }
    return;
}


void BinarioAVL::reporteProductos(string &texto, pnodoAVL raiz){
    if (raiz==NULL){
        return;
    }
    else
    {
        reporteProductos(texto,raiz->Hder);
        reporteProductos(texto,raiz->Hizq);
        texto.append("-Codigo: ");
        texto.append(to_string(raiz->valor));
        texto.append(", Nombre de producto: ");
        texto.append(raiz->nombre);
        texto.append("\n");
        return;

    }
}

void BinarioAVL::reporteProductoMasVendido(string &texto, pNodoBinarioAVL raiz, int mayor){
    if (raiz==NULL){
        return;
    }
    else
    {
        reporteProductoMasVendido(texto,raiz->Hder,mayor);
        reporteProductoMasVendido(texto,raiz->Hizq,mayor);
        if (raiz->cantidadVentas==mayor){
            texto.append("-Codigo: ");
            texto.append(to_string(raiz->valor));
            texto.append(", Nombre de producto: ");
            texto.append(raiz->nombre);
            texto.append("\n");
        }
    }
    return;
}

void BinarioAVL::rellenarGondolaAVL(pnodoAVL raiz, int codigoPasillo, AA inventario){
    if (raiz==NULL){
        return;
    }
    rellenarGondolaAVL(raiz->Hder, codigoPasillo, inventario);
    rellenarGondolaAVL(raiz->Hizq, codigoPasillo, inventario);
    RBTree temp = RBTree();
    temp.rellenarGondolaRN(raiz->marcas, codigoPasillo, raiz->valor, inventario);
}

void BinarioAVL::PreordenI(){
    NodoBinarioAVL *Act = raiz;
    PilaAVL p;
    while(p.Vacia()==false || (Act!=NULL)){
        if(Act!=NULL){
            cout<<Act->valor<<" - ";
            p.Push(Act);
            Act = Act->Hizq;
        }else{
            Act=p.Pop();
            Act=Act->Hder;
        }
    }
}

void BinarioAVL::InordenI(){
    NodoBinarioAVL *Act = raiz;
    PilaAVL p;
    bool band=true;
    while(band){
        while(Act!=nullptr){
            p.Push(Act);
            Act = Act->Hizq;
        }
        if(!p.Vacia()){
            Act=p.Pop();
            cout<<Act->valor<<" - ";
            Act=Act->Hder;
        }
        if(p.Vacia() & Act==NULL){
            break;
        }
    }
}

void BinarioAVL::PostordenI(){
    NodoBinarioAVL *Act = raiz;
    PilaAVL p;
    PilaAVL p2;
    while(!p.Vacia() || Act!=NULL){
        if(Act!=NULL){
            p2.Push(new NodoBinarioAVL (Act->valor,Act->nombre));
            p.Push(Act);
            Act = Act->Hder;
        }else{
            Act=p.Pop();
            Act = Act->Hizq;
        }
    }
    while(!p2.Vacia()){
        NodoBinarioAVL *salida=p2.Pop();
        cout<<salida->valor<<" - ";
    }
}

void BinarioAVL::PostordenG(pNodoBinarioAVL pRaiz)
{
    if (pRaiz == NULL)
        return;
    PostordenG(pRaiz->Hizq);
    PostordenG(pRaiz->Hder);
    cout<<pRaiz->valor<<","<<pRaiz->nombre<<" - ";
}


void BinarioAVL::Equilibrar1(NodoBinarioAVL* n, bool Hh){
    NodoBinarioAVL *n1;
    switch (n->FB){
        case -1: n->FB = 0;
        break;
        case 0: n->FB = 1;
        Hh = false;
        break;
        case 1: n1 = n->Hder;
        if(n1->FB>=0){
            if(n1->FB=0){
                Hh = false;
                RotacionSimpleDerecha(n, n1);
            }else{
                RotacionDobleDerecha(n, n1);
            }
        }
    }
}

void BinarioAVL::Equilibrar2(NodoBinarioAVL* n, bool Hh){
    NodoBinarioAVL *n1;
    switch (n->FB){
        case 1: n->FB = 0;
        break;
        case 0: n->FB = 1;
        Hh = false;
        break;
        case -1: n1 = n->Hizq;
        if(n1->FB<=0){
            if(n1->FB==0){
                Hh = false;
                RotacionSimpleIzquierda(n, n1);
            }else{
                RotacionDobleIzquierda(n, n1);
            }
        }
    }
}
void BinarioAVL::InsertarBalanceado(pNodoBinarioAVL &ra, bool &Hh, int x, string nombre){
    pNodoBinarioAVL n1;
    if(ra==NULL){
        ra = new NodoBinarioAVL(x,nombre);
        Hh = true;
    }else{
        if(x<ra->valor){
            InsertarBalanceado(ra->Hizq, Hh, x,nombre);
        if(Hh){
            switch(ra->FB){
                case 1: ra->FB=0;
                Hh = false;
                break;
                case 0: ra->FB  = -1;
                break;
                case -1: n1=ra->Hizq;
                if(n1->FB ==-1){
                    RotacionSimpleIzquierda(ra, n1);
                }else{
                    RotacionDobleIzquierda(ra,n1);
                }
                Hh = false;
                break;
            }
        }
        }else{
            if(x>ra->valor){
                InsertarBalanceado(ra->Hder, Hh, x,nombre);
                if(Hh){
                    switch(ra->FB){
                        case -1: ra->FB=0;
                        Hh = false;
                        break;
                        case 0: ra->FB=1;
                        break;
                        case 1:n1=ra->Hder;
                        if(n1->FB==1){
                            RotacionSimpleDerecha(ra, n1);
                        }else{
                            RotacionDobleDerecha(ra, n1);
                        }
                        Hh=false;
                        break;
                    }
                }
            }
        }
    }
}

void BinarioAVL::RotacionDobleIzquierda(NodoBinarioAVL*& n, NodoBinarioAVL*& n1){
    NodoBinarioAVL *n2;
    n2=n1->Hder;
    n->Hizq = n2->Hder;
    n2->Hder=n;
    n1->Hder=n2->Hizq;
    n2->Hizq=n1;

    if(n2->FB==1){
        n1->FB=-1;
    }else{
        n1->FB=0;
    }
    if(n2->FB==-1){
        n->FB=1;
    }else{
        n->FB=0;
    }
    n2->FB=0;
    n=n2;
}

void BinarioAVL::RotacionDobleDerecha(NodoBinarioAVL*& n, NodoBinarioAVL*& n1){
    NodoBinarioAVL *n2;
    n2=n1->Hizq;
    n->Hder = n2->Hizq;
    n2->Hizq=n;
    n1->Hizq=n2->Hder;
    n2->Hder=n1;

    if(n2->FB==1){
        n->FB=-1;
    }else{
        n->FB=0;
    }
    if(n2->FB==-1){
        n1->FB=1;
    }else{
        n1->FB=0;
    }
    n2->FB=0;
    n=n2;
}

void BinarioAVL::RotacionSimpleDerecha(NodoBinarioAVL*& n, NodoBinarioAVL*& n1){
    n->Hder=n1->Hizq;
    n1->Hizq=n;

    if(n1->FB==1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=1;
        n1->FB=-1;
    }
    n=n1;
}

void BinarioAVL::RotacionSimpleIzquierda(NodoBinarioAVL*& n, NodoBinarioAVL*& n1){
    n->Hizq=n1->Hder;
    n1->Hder=n;

    if(n1->FB==-1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=-1;
        n1->FB=1;
    }
    n=n1;
}
