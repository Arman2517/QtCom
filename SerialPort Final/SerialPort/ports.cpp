#include "ports.h"
#include <QDebug>
#include <QRegExp>
#include <QMessageBox>
#include <sys./time.h>

PortS::PortS(QObject *parent) : QObject(parent), serial(nullptr)
{

}

bool PortS::connect(QString portName)
{

    if(serial != nullptr){
        serial->close();
        delete serial;
    }

    serial = new QSerialPort(this);
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    if(serial->open(QIODevice::ReadWrite)){
        qDebug()<<"Отлично";
        QObject::connect(serial,&QSerialPort::readyRead,this,&PortS::dataReady);

    }else
    {
        qDebug()<<"Ошибка соединения с портом";
    }
    return serial->isOpen();
}


void PortS::dataReady()
{
    if(serial->isOpen()){
        parsData(serial->readAll());
        return;
    }
}



void PortS::parsData(QByteArray b)
{
    acpData="";
    tempData="";
    outData="";
    capData="";
    QString dataB=b,x="";
    QRegExp rx(".*(#v)");
    QRegExp rxF("[#v]");
    QRegExp rx2("[\r]");

    if(rx.indexIn(dataB)==0){
        i=rxF.indexIn(dataB,0);
        i+=2;
        while(i<dataB.size()-3 && i!=1){
            while(dataB[i]!='#' && i<dataB.size()-3){
                x+=dataB[i];
                if(dataB[i]=="t"){
                    x.remove(x.size()-1,1);
                    acpData=x;
                    x="";
                }
                if(dataB[i]=="r"){
                    x.remove(x.size()-1,1);
                    tempData=x;
                    x="";
                }
                if(dataB[i]=="c"){
                    x.remove(x.size()-1,1);
                    outData=x;
                    x="";
                }
                if(dataB[i]=="!"){
                    x.remove(x.size()-1,1);
                    capData=x;
                    x="";
                    i+=2;
                    emit dataReceived();
                }
                i++;
            }

        }
        serial->clear();
    }


}


void PortS::quitPort(){//Закрытие порта
    if(serial != nullptr){
        serial->close();
        delete serial;
        serial=nullptr;
    }
    emit threadQuit();
}

PortS::~PortS(){
    if(serial != nullptr){
        serial->close();
        delete serial;
    }
        emit threadQuit();
}

