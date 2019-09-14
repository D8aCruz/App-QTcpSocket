#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    i = 0;
    ui->lineEditEstado->setStyleSheet("font-weight: normal; color: white; background-color: red;");
    ui->lineEditEstado->setText("Desconectado");
    ui->pushButtonConectar->setText("Conectar");

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cambio(int state,int color)
{
    switch (state) {
        case 1:
            switch (color) {
                case 0:
                    ui->lineEditColor->setStyleSheet("font-weight: normal; color: white; background-color: lightgreen;");
                    break;
                case 1:
                    ui->lineEditColor->setStyleSheet("font-weight: normal; color: white; background-color: red;");
                    break;
                case 2:
                    ui->lineEditColor->setStyleSheet("font-weight: normal; color: white; background-color: blue;");
                    break;
            }
            break;
        case 0:
           ui->lineEditColor->setStyleSheet("font-weight: normal; color: white; background-color: white;");
           break;
    }
}


void MainWindow::on_pushButtonConectar_clicked()
{
    if(!socket->isOpen()){
        socket->connectToHost("192.168.0.3",80);
        if(!socket->waitForConnected(1000)){
            QMessageBox::information(this,"Error",socket->errorString());
        }
    } else {
        socket->close();
    }

}

void MainWindow::connected(){
    ui->lineEditEstado->setStyleSheet("font-weight: bold; color: black; background-color: lightgreen;");
    ui->lineEditEstado->setText("CONECTADO");
    ui->pushButtonConectar->setText("Desconectar");
}
void MainWindow::disconnected(){
    ui->lineEditEstado->setStyleSheet("font-weight: normal; color: white; background-color: red;");
    ui->lineEditEstado->setText("Desconectado");
    ui->pushButtonConectar->setText("Conectar");
}
void MainWindow::bytesWritten(qint64 bytes){
    qDebug()<<"We wrote: "<<bytes;
}
void MainWindow::readyRead(){
    ui->textEditRecibido->append(socket->readAll());
}



void MainWindow::on_pushButtonVerde_clicked()
{
    QTextStream T(socket);
    if(!i){
        i=1;
    T<<"#G1$";
    socket->flush();
    }else {
        i = 0;
        T<<"#G0$";
        socket->flush();
    }
    cambio(i,0);
}

void MainWindow::on_pushButtonRojo_clicked()
{
    QTextStream T(socket);
    if(!i){
        i=1;
        T<<"#B1$";
        socket->flush();
    }else {
        i = 0;
        T<<"#B0$";
        socket->flush();
    }
    cambio(i,1);
}

void MainWindow::on_pushButtonAzul_clicked()
{
    QTextStream T(socket);
    if(!i){
        i=1;
        T<<"#R1$";
        socket->flush();
    }else {
        i = 0;
        T<<"#R0$";
        socket->flush();
    }
    cambio(i,2);
}
