QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT       += core
QT       += network
QT       -= gui
SOURCES += \
        AA.cpp \
        B.cpp \
        Binario.cpp \
        Menu.cpp \
        Nodos.cpp \
        Pila.cpp \
        Rojinegro.cpp \
        adminthread.cpp \
        main.cpp \
        mycliente.cpp \
        server.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AA.h \
    B.h \
    Binario.h \
    Globales.h \
    ListaCiudades.h \
    Nodos.h \
    Pila.h \
    Rojinegro.h \
    adminthread.h \
    menu.h \
    mycliente.h \
    server.h \
    serverGlo.h

DISTFILES += \
    Administradores.txt \
    Ciudades.txt \
    ClienteServer.pro.user \
    Clientes.txt \
    Inventario.txt \
    MarcasProductos.txt \
    Pasillos.txt \
    ProductosPasillos.txt
