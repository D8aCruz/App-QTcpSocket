#include "socketwifi.h"

socketWifi::socketWifi(QObject *parent) : QObject(parent)
{


}

void socketWifi::Test()
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    qDebug()<< "Connecting....";
    socket->connectToHost("192.168.43.95",80);

    if(!socket->waitForConnected(1000)){
        qDebug()<<"Error: "<<socket->errorString();
    }
}
