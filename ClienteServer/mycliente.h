#ifndef MYCLIENTE_H
#define MYCLIENTE_H

#include <QObject>
#include <QTcpSocket>
#include <QtDebug>
#include <string>
#include <QThreadPool>
#include "B.h"
#include "Globales.h"
#include <iostream>

class Mycliente: public QObject
{
    Q_OBJECT
public:
   explicit Mycliente(QObject*parent=nullptr);
   void SetSocket(qintptr Desc);
   void conectadoE(QByteArray data);
   void registrarCliente(QByteArray data);
   void setCedula(int cedula);
   string inordenMandar(pNodoBinario nodo);
   string inordenMandarP(pNodoBinarioAVL nodo);
   string inordenMandarM(NodePtr nodo);
   void  FacturarCliente();
   int static precio(conodo compremix);
signals:
    void envio(QByteArray data);
public slots:
   void connected();
   void disconnected();
   void readyRead();
   void write(QByteArray Data);
   void enviov(QByteArray data);
private:
    QTcpSocket*socket;
    QThreadPool*pool;
    int cedula;
};
extern QList<Mycliente*> lisSock;
#endif // MYCLIENTE_H
