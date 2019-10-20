#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "Globales.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "serverGlo.h"
#include <QObject>
#include "server.h"
#include <QByteArray>


class Menu:public QObject{
    Q_OBJECT
public:
    Menu(QObject*parent=nullptr);



//void rellenarInventario(inventario inven,listasort listaventas);
//int traerInventario(inventario inventario,int solicita,conodo compra);
//void rellenarGondolasMarc(inventario inventario,pNodoBinarioAVL pasillo,pNodoBinarioAVL producto,conodo compra);
//void rellenarGondolasProd(inventario inventario,pNodoBinarioAVL pasillo,conodo compra);
//void rellenarGondolas(Binario B1,inventario inventario,listasort listaventas);
//void comprar(listaClientes clientes,Binario B1);
//void facturarCliente(Binario B1,inventario inventariop,listaClientes clientes);
void menu();
void menuAgregar ();
void menuModificar ();
void agregarPasillo ();
void agregarProducto ();
void agregarMarca ();
void agregarCliente ();
void modificarPrecio ();
void modificarImpuesto ();
void modificarPertenencia ();
void modificarCanasta();
void menuConsultar();
void consultaPrecio();
void consultaImpuesto();
void consultaPertenencia();
void FacturarCliente();
int precio(conodo compremix);
int menuReportes ();
void reportePasillos();
void reporteClientes();
void reportePasilloMasVisitado ();
void reportePasilloMenosVisitado ();
void reporteProductosPasilloMasVendido ();
void reporteMarcaMasVendida ();
void reporteClienteQueMasCompro ();
void reporteClienteQueMenosCompro ();
void reporteInventario ();
void reporteProductoPasillo ();
signals:
    void enviart(qintptr*s,QByteArray data);
    void blockAll();
    void unBlockAll();

private:
};

bool esNumerico (string pstring);

#endif // MENU_H_INCLUDED
