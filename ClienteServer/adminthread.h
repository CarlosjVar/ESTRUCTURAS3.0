#ifndef ADMINTHREAD_H
#define ADMINTHREAD_H
#include <QThread>
#include <QObject>
#include <QDebug>
#include <iostream>
#include <string>
#include <strings.h>
#include <QObject>
#include "Globales.h"
#include "menu.h"
#include "Nodos.h"
using namespace std;
class adminThread:public QThread
{
    Q_OBJECT
public:
    adminThread(QObject*parent=nullptr);
    void run();
    void facturar();

};

#endif // ADMINTHREAD_H
