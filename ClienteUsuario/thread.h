#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QObject>
#include <iostream>
#include <string>
#include "socketglobal.h"
#include <regex>
class Thread:public QThread
{
    Q_OBJECT
public:
    Thread(QObject*parent=nullptr);
    void run() override;
    bool LoginV();
    std::string pedirDato();
    void menu();
    void comprar();
    void compra1();
    void consultapre();
signals:
    void WriteByte(QByteArray data);
    void waitResponse(int q);
};
bool is_email_valid(const std::string& email);
#endif // THREAD_H
