#include "thread.h"
using namespace std;
Thread::Thread(QObject*parent)
{
    connect(this,SIGNAL(WriteByte(QByteArray)),&socket,SLOT(WriteByte(QByteArray)));
    connect(this,SIGNAL(waitResponse(int)),&socket,SLOT(waitResponse(int)));
}
void Thread::run()
//Funcionamiento del thread del cliente
{
    cout<<"Bienvenido"<<endl;
    while(true)
    {
        cout<<"Ingrese su cedula"<<endl;
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
            socket.setCed(cedula);
            menu();
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
                cout<<"Por favor digite algo valido"<<endl;
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
                    menuN();
                    break;
                }
            }
            }
        }
    }
}
bool is_email_valid(string& email)
//Valida email valido
{
   const regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   return regex_match(email, pattern);
}
string Thread::pedirDato()
//Pide los datos a registrar
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
void Thread::menuN()
//Menú de cliente no registrado
{
    while(true)
    {
        cout<<"Bienvenido , seleccione una opcion: "<<endl;
        cout<<"1 Consultar un precio "<<endl;
        cout<<"2 Consultar si un producto es de la canasta "<<endl;
        cout<<"3 Consultar el % impuesto de un producto "<<endl;
        cout<<"4 Salir"<<endl;
        string opc;
        cout<<"Opcion: ";
        cin>>opc;
        if(opc=="1")
        {
            if(socket.concalma)
            {
                cout<<"En mantenimiento"<<endl;
            }
            else
            {
            consultapre();
            }
        }
        else if(opc=="2")
        {
            if(socket.concalma)
            {
                cout<<"En mantenimiento"<<endl;
            }
            else
            {
                consultacanasta();
            }
        }
        else if(opc=="3")
        {
            if(socket.concalma)
            {
                cout<<"En mantenimiento"<<endl;
            }
            else
            {
                consultaImp();
            }

        }
        else if(opc=="4")
        {


            break;

        }


    }
}

void Thread::menu()
//Menu de cliente registrado
{
    while(true)
    {
        cout<<"Bienvenido , seleccione una opción: "<<endl;
        cout<<"1 Consultar un precio "<<endl;
        cout<<"2 Consultar si un producto es de la canasta "<<endl;
        cout<<"3 Consultar el % impuesto de un producto "<<endl;
        cout<<"4 Comprar"<<endl;
        cout<<"5 Reportes"<<endl;
        cout<<"6 Salir"<<endl;
        string opc;
        cout<<"Opcion: ";
        cin>>opc;
        if(opc=="1")
        {
            if(socket.concalma)
            {
                cout<<"En mantenimiento"<<endl;
            }
            else
            {
            consultapre();
            }
        }
        else if(opc=="2")
        {
            if(socket.concalma)
            {
                cout<<"En mantenimiento"<<endl;
            }
            else
            {
                consultacanasta();
            }
        }
        else if(opc=="3")
        {
            if(socket.concalma)
            {
                cout<<"En mantenimiento"<<endl;
            }
            else
            {
                consultaImp();
            }

        }
        else if(opc=="4")
        {
            if(socket.concalma)
            {
            cout<<"En mantenimiento"<<endl;
            }
            else
            {
            compra1();
            }
        }
        else if(opc=="5")
        {
            if(socket.concalma)
            {
            cout<<"En mantenimiento"<<endl;
            }
            else
            {
            menuR();
            }
        }
        else if (opc=="6")
        {
           socket.conectado=false;
           return run();
        }

    }
}
void Thread::menuR()
{
    cout<<"Menú de reportes del cliente"<<endl;
    char resp;
    while(true)
    {
        cout<<"1.Marcas de un producto"<<endl;
        cout<<"2.Productos de un pasillo"<<endl;
        cout<<"3.Pasillos del supermercado"<<endl;
        cin>>resp;
        if(resp=='1')
        {
            string consulta="CO";
            consulta.append("PA");
            emit WriteByte(QByteArray::fromStdString(consulta));
            emit waitResponse(2000);
            sleep(1);
            consulta="CO";
            int pasi;
            while(true)
            {
                cout<<"Eliga un pasillo: ";
                cin>>pasi;
                if(socket.concalma)
                {
                    cout<<"Servidor en mantenimiento"<<endl;
                }
                else if(!cin.fail())
                {
                    break;
                }
                if(cin.fail())
                {
                    cin.ignore();
                    cin.clear();
                }
                cin.ignore();
                cout<<"Por favor digite un numero"<<endl;
            }
            consulta.append("PR;");
            consulta.append(std::to_string(pasi));
            emit WriteByte(QByteArray::fromStdString(consulta));
            emit waitResponse(2000);
            sleep(1);
            if(socket.getpa())
            {
                return;
            }
            consulta="CO";
            int produ;
            while(true)
            {
                cout<<"Eliga un producto: ";
                cin>>produ;
                if(socket.concalma)
                {
                    cout<<"Servidor en mantenimiento"<<endl;
                }
                else if(!cin.fail())
                {
                    break;
                }
                if(cin.fail())
                {
                    cin.ignore();
                    cin.clear();
                }
                cin.ignore();
                cout<<"Por favor digite un numero"<<endl;
            }
            consulta="CO";
            consulta.append("MA;");
            consulta.append(std::to_string(pasi));
            consulta.append(";");
            consulta.append(std::to_string(produ));
            emit WriteByte(QByteArray::fromStdString(consulta));
            emit waitResponse(2000);
            sleep(1);
            if(socket.getpro())
            {
                return;
            }
            break;
        }
        else if(resp=='2')
        {
            string consulta="CO";
            consulta.append("PA");
            emit WriteByte(QByteArray::fromStdString(consulta));
            emit waitResponse(2000);
            sleep(1);
            consulta="CO";
            int pasi;
            while(true)
            {
                cout<<"Eliga un pasillo: ";
                cin>>pasi;
                if(socket.concalma)
                {
                    cout<<"Servidor en mantenimiento"<<endl;
                }
                else if(!cin.fail())
                {
                    break;
                }
                if(cin.fail())
                {
                    cin.ignore();
                    cin.clear();
                }
                cin.ignore();
                cout<<"Por favor digite un numero"<<endl;
            }
            consulta.append("PR;");
            consulta.append(std::to_string(pasi));
            emit WriteByte(QByteArray::fromStdString(consulta));
            emit waitResponse(2000);
            sleep(1);
            if(socket.getpa())
            {
                return;
            }
            break;
        }
        else if(resp=='3')
        {
            string consulta="CO";
            consulta.append("PA");
            emit WriteByte(QByteArray::fromStdString(consulta));
            emit waitResponse(2000);
            sleep(1);
            break;
        }
    }
}
void Thread::consultaImp()
//Consulta de impuesto
{
    string consulta="CO";
    consulta.append("PA");
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    consulta="CO";
    int pasi;
    while(true)
    {
        cout<<"Eliga un pasillo: ";
        cin>>pasi;
        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }
    consulta.append("PR;");
    consulta.append(std::to_string(pasi));
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    if(socket.getpa())
    {
        return;
    }
    consulta="CO";
    int produ;
    while(true)
    {
        cout<<"Eliga un producto: ";
        cin>>produ;
        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }
    consulta="CO";
    consulta.append("MA;");
    consulta.append(std::to_string(pasi));
    consulta.append(";");
    consulta.append(std::to_string(produ));
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    if(socket.getpro())
    {
        return;
    }
    int marca;
    while(true)
    {
        cout<<"Eliga una marca: ";
        cin>>marca;
        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }
    consulta="CO";
    consulta.append("CI;");
    consulta.append(std::to_string(pasi));
    consulta.append(";");
    consulta.append(std::to_string(produ));
    consulta.append(";");
    consulta.append(std::to_string(marca));
    emit WriteByte(QByteArray::fromStdString(consulta));
    sleep(1);
}
void Thread::consultacanasta()
//Consuta de canasta básica
{
    string consulta="CO";
    consulta.append("PA");
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    consulta="CO";
    int pasi;
    while(true)
    {
        cout<<"Eliga un pasillo: ";
        cin>>pasi;
        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }
    consulta.append("PR;");
    consulta.append(std::to_string(pasi));
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    if(socket.getpa())
    {
        return;
    }
    consulta="CO";
    int produ;
    while(true)
    {
        cout<<"Eliga un producto: ";
        cin>>produ;
        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }

    consulta="CO";
    consulta.append("MA;");
    consulta.append(std::to_string(pasi));
    consulta.append(";");
    consulta.append(std::to_string(produ));
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    if(socket.getpro())
    {
        return;
    }
    int marca;
    while(true)
    {
        cout<<"Eliga una marca: ";
        cin>>marca;

        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }
    consulta="CO";
    consulta.append("CC;");
    consulta.append(std::to_string(pasi));
    consulta.append(";");
    consulta.append(std::to_string(produ));
    consulta.append(";");
    consulta.append(std::to_string(marca));
    emit WriteByte(QByteArray::fromStdString(consulta));
    sleep(1);
}
void Thread::consultapre()
//Consulta de precio

    {
        string consulta="CO";
        consulta.append("PA");
        emit WriteByte(QByteArray::fromStdString(consulta));
        emit waitResponse(2000);
        sleep(1);
        consulta="CO";
        int pasi;
        while(true)
        {
            cout<<"Eliga un pasillo: ";
            cin>>pasi;
            if(socket.concalma)
            {
                cout<<"Servidor en mantenimiento"<<endl;
            }
            else if(!cin.fail())
            {
                break;
            }
            if(cin.fail())
            {
                cin.ignore();
                cin.clear();
            }
            cin.ignore();
            cout<<"Por favor digite un numero"<<endl;
        }
        consulta.append("PR;");
        consulta.append(std::to_string(pasi));
        emit WriteByte(QByteArray::fromStdString(consulta));
        emit waitResponse(2000);
        sleep(1);
        if(socket.getpa())
        {
            return;
        }
        consulta="CO";
        int produ;
        while(true)
        {
            cout<<"Eliga un producto: ";
            cin>>produ;
            if(socket.concalma)
            {
                cout<<"Servidor en mantenimiento"<<endl;
            }
            else if(!cin.fail())
            {
                break;
            }
            if(cin.fail())
            {
                cin.ignore();
                cin.clear();
            }
            cin.ignore();
            cout<<"Por favor digite un numero"<<endl;
        }
        consulta="CO";
        consulta.append("MA;");
        consulta.append(std::to_string(pasi));
        consulta.append(";");
        consulta.append(std::to_string(produ));
        emit WriteByte(QByteArray::fromStdString(consulta));
        emit waitResponse(2000);
        sleep(1);
        if(socket.getpro())
        {
            return;
        }
        int marca;
        while(true)
        {
            cout<<"Eliga una marca: ";
            cin>>marca;
            if(socket.concalma)
            {
                cout<<"Servidor en mantenimiento"<<endl;
            }
            else if(!cin.fail())
            {
                break;
            }
            if(cin.fail())
            {
                cin.ignore();
                cin.clear();
            }
            cin.ignore();
            cout<<"Por favor digite un numero"<<endl;
        }
        consulta="CO";
        consulta.append("CN;");
        consulta.append(std::to_string(pasi));
        consulta.append(";");
        consulta.append(std::to_string(produ));
        consulta.append(";");
        consulta.append(std::to_string(marca));
        emit WriteByte(QByteArray::fromStdString(consulta));
        sleep(1);
}

void Thread::compra1()
//Validación para cola y si desea
{
    string anadir="AD";

    if(socket.cola)
    {
        cout<<"Cliente ya en cola"<<endl;
        return;

    }
    while(true)
    {
        std::cout<<"Que desea hacer: \n 1:Comprar \n 2:Pasar al carrito \n Opcion: "<<std::endl;
        string respuesta;
        cin>>respuesta;
        if(respuesta=="1")
        {   comprar();
            return compra1();
        }
        else if(respuesta=="2")
        {
            socket.cola=true;
            anadir.append(std::to_string(socket.cedula));
            emit WriteByte(QByteArray::fromStdString(anadir));
            break;
        }
    }
}
void Thread::comprar()
//Pide todos los datos necesarios para realizar una compra
{
    string consulta="CO";
    consulta.append("PA");
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    consulta="CO";
    int pasi;
    while(true)
    {
        cout<<"Eliga un pasillo: ";
        cin>>pasi;
        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }
    consulta.append("PR;");
    consulta.append(std::to_string(pasi));
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    if(socket.getpa())
    {
        return;
    }
    consulta="CO";
    int produ;
    while(true)
    {
        cout<<"Eliga un producto: ";
        cin>>produ;
        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }

    consulta="CO";
    consulta.append("MA;");
    consulta.append(std::to_string(pasi));
    consulta.append(";");
    consulta.append(std::to_string(produ));
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    if(socket.getpro())
    {
        return;
    }
    int marca;
    while(true)
    {
        cout<<"Eliga una marca: ";
        cin>>marca;
        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }
    consulta="CO";
    consulta.append("CO;");
    consulta.append(std::to_string(pasi));
    consulta.append(";");
    consulta.append(std::to_string(produ));
    consulta.append(";");
    consulta.append(std::to_string(marca));
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);
    sleep(1);
    if(socket.getmar())
    {
        return;
    }
    int cantidad;
    while(true)
    {
        cout<<"Digite cuantos productos desea llevar: ";
        std::cin>>cantidad;
        if(socket.concalma)
        {
            cout<<"Servidor en mantenimiento"<<endl;
        }
        else if(!cin.fail())
        {
            break;
        }
        if(cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        cin.ignore();
        cout<<"Por favor digite un numero"<<endl;
    }
    consulta="CO";
    consulta.append("AG;");
    consulta.append(std::to_string(pasi));
    consulta.append(";");
    consulta.append(std::to_string(produ));
    consulta.append(";");
    consulta.append(std::to_string(marca));
    consulta.append(";");
    consulta.append(std::to_string(cantidad));
    consulta.append(";");
    consulta.append(std::to_string(socket.getCed()));
    emit WriteByte(QByteArray::fromStdString(consulta));
    emit waitResponse(2000);



}
