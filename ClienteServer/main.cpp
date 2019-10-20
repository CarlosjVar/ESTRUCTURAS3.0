#include <QCoreApplication>
#include "server.h"
#include "ListaCiudades.h"
#include "Globales.h"
#include "adminthread.h"
#include "serverGlo.h"
ArbolB clientes=ArbolB(5);
ArbolB administradores=ArbolB(5);
Binario supermercado;
AA inventario=AA();
ColaS colaclientes;
ColaS clienteslog;
Server servidor;
listasort listaventasG;
listasort listaventasI;
listasort listaventasT;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    servidor.StartServer();
    supermercado.cargarPasillos("Pasillos.txt");
    supermercado.PreordenI();
    supermercado.cargarProductos("ProductosPasillos.txt");
    supermercado.cargarMarcas("MarcasProductos.txt");
    clientes.cargarClientes("Clientes.txt");
    administradores.cargarAdmins("Administradores.txt");
    listaCiudades L1 = listaCiudades();
    L1.cargarCiudades("Ciudades.txt");
    inventario.cargarInventario("inventario.txt");
    adminThread admin;
    admin.start();
    return a.exec();
}
