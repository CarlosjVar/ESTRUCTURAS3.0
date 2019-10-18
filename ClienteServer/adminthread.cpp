#include "adminthread.h"

using namespace std;
adminThread::adminThread(QObject*parent)
{

}
void adminThread::run()
{
    cout<<"Bienvenido a la interfaz del administrador"<<endl;
    cout<<"Por favor ingrese sus credenciales de administrador: "<<endl;
    int cedula;
    cin>>cedula;
    Pagina*pag=new Pagina(5);
    int k;
    pag=administradores.buscar(cedula,k);
    if(pag!=nullptr)
    {
        cout<<"Bienvenido: "<<pag->obtenerDato(k,0)<<endl;
        Menu menu1;
        menu1.menu();
    }
    else
    {
        cout<<"Codigo incorrecto"<<endl;
        return run();
    }
}

