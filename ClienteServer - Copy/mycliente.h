#ifndef MYCLIENTE_H
#define MYCLIENTE_H

#include <QObject>
#include <QTcpSocket>
#include <QtDebug>
#include <string>
#include <QThreadPool>
#include "B.h"
#include "Globales.h"

class Mycliente: public QObject
{
    Q_OBJECT
public:
   explicit Mycliente(QObject*parent=nullptr);
   void SetSocket(qintptr Desc);
   void conectadoE(QByteArray data);
   void registrarCliente(QByteArray data);
signals:

public slots:
   void connected();
   void disconnected();
   void readyRead();
   void write(QByteArray Data);
private:
    QTcpSocket*socket;
};

#endif // MYCLIENTE_H
