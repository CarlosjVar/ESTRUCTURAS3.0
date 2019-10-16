#ifndef SOCKETTEST_H
#define SOCKETTEST_H
#include <QThread>
#include <QObject>
#include <QDebug>
#include <iostream>
#include <string>
#include <strings.h>
#include <QTcpSocket>

class SocketTest : public QObject
{
    Q_OBJECT
public:
    explicit SocketTest(QObject *parent = 0);

    void Connect();

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void WriteByte(QByteArray data);
    void waitResponse(int q);
    bool getestado();
    bool getpa();
    bool getpro();
    bool getmar();
    void setCed(std::string ced);
    int getCed();
private:
    QTcpSocket *socket;
    bool conectado;
    bool paInv=false;
    bool proInv=false;
    bool marInv=false;
    int cedula;
friend class Thread;
};

#endif // SOCKETTEST_H
