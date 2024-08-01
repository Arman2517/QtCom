#include "portsvolt.h"

PortSVolt::PortSVolt(QObject *parent) : QObject(parent), serial(nullptr)
{
    timer=new QTimer(this);
    timer->setInterval(100);
    QObject::connect(timer,&QTimer::timeout,this,&PortSVolt::valinquiry);
}

bool PortSVolt::connect(QString portName)
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
        QObject::connect(serial,&QSerialPort::readyRead,this,&PortSVolt::dataReady);

    }else
    {
        qDebug()<<"Ошибка соединения с портом";
    }
    timer->start();
    return serial->isOpen();
}


void PortSVolt::dataReady()
{
    if(serial->isOpen()){
        parsData(serial->readAll());
        return;
    }
}



void PortSVolt::parsData(QByteArray b)
{

    QString dataB=b;
    QRegExp rx("[\r]");

    QThread::msleep(50);
    int pos=0;
    pos=rx.indexIn(dataB,pos);
    if(pos!=-1){
        dataB.remove(pos,2);
    }
    voltData+=dataB;
    if (voltData.size()>6) voltData.remove(6,19);//Устранение лишних данных, если приходят дважды
    if(voltData.size()>4){
        QChar znak=voltData[0];
        voltData.remove(0,1);
        double z=voltData.toDouble()*pow(10,-2);///
        voltData=QString::number(z);
        voltData.insert(0,znak);
        voltData.push_back(" В");
        emit dataReceived();
    }
    if(voltData.size()>1) firstCon=true;//Первая отправка была выполнена
}


void PortSVolt::quitPortV(){//Закрытие порта
    if(serial != nullptr){
        serial->close();
        delete serial;
        serial=nullptr;
        timer->stop();
    }
    emit threadQuit();
}

PortSVolt::~PortSVolt(){
    if(serial != nullptr){
        serial->close();
        delete serial;
    }
        emit threadQuit();
}

void PortSVolt::valinquiry()
{
    if(serial->isOpen()){
        if(firstCon==false){
            QString s;
            s="*CLS";
            QString EndOfLine("\r\n");
            s+=EndOfLine;
            s+=":CONF:VOLT:AC 10";
            s+=EndOfLine;
            s+=":VAL?";
            s+=EndOfLine;
            serial->write(s.toUtf8());
        }else
        {
            QString s;
            s+=":VAL?";
            QString EndOfLine("\r\n");
            s+=EndOfLine;
            serial->write(s.toUtf8());
        }
    }


}
