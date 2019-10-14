#include "thread.h"
using namespace std;
Thread::Thread(QObject*parent)
{
    connect(this,SIGNAL(WriteByte(QByteArray)),&socket,SLOT(WriteByte(QByteArray)));
    connect(this,SIGNAL(waitResponse(2000)),&socket,SLOT(waitResponse(2000)));
}
void Thread::run()
{
    cout<<"Bienvenido"<<endl;
    while(true)
    {
        cout<<"Ingrese su cédula"<<endl;
        string cedula ;
        cin>>cedula;
        string login="LO";
        login.append(cedula);
        emit WriteByte(QByteArray::fromStdString(login));
        emit waitResponse(2000);
        this->sleep(1);
        if(socket.getestado())
        {
            cout<<"Se ha logueado"<<endl;
            while(true)
            {

            }
        }
        else
        {
            while(true)
            {
            cout<<"No se encuentra registrado \n Desea registrarse ? (y/n)"<<endl;
            string resp;
            cin>>resp;
            if(resp!="y"&&resp!="n")
            {
                cout<<"Por favor digite algo válido"<<endl;
            }
            else
            {
                string re="RE";

                if(resp=="y")
                {
                    string datos=pedirDato();
                    re.append(datos);
                    emit WriteByte(QByteArray::fromStdString(re));
                    sleep(2);
                    break;

                }
                else if(resp=="n")
                {
                    cout<<"Menú de visitante"<<endl;
                }
            }
            }
        }
    }
}
bool is_email_valid(string& email)
{
   const regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   return regex_match(email, pattern);
}
string Thread::pedirDato()
{
    string todo;
    string cedula;
    cout<<"Digite la cedula a registrar: ";
    while(true)
    {
    cout<<"Cedula: ";
    cin>>cedula;
    if(cedula.length()==7)
    {
        break;
    }
    cout<<"La cédula debe consistir de 7 dígitos"<<endl;
    }
    string nombre;
    cout<<"Ingrese su nombre: ";
    cin>>nombre;
    string ciudad;
    cout<<"Ingrese su ciudad: ";
    cin>>ciudad;
    string telefono;
    cout<<"Ingrese su número telefónico: ";
    while(telefono.length()<8)
    {
        cin>>telefono;
        if(telefono.length()==8)
        {
            break;
        }
        cout<<"Digite un número telefónico de 8 dígitos: ";
    }
    string correo;
    cout<<"Ingrese su correo electrónico: ";
    cin>>correo;
    todo.append(cedula);
    todo.append(";");
    todo.append(nombre);
    todo.append(";");
    todo.append(ciudad);
    todo.append(";");
    todo.append(telefono);
    todo.append(";");
    todo.append(correo);
    return todo;


}


