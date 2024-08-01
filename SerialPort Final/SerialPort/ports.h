#ifndef PORTS_H
#define PORTS_H

#include <QObject>
#include <QSerialPortInfo>
#include <QtSerialPort>
#include <QTimer>

class PortS : public QObject
{
    Q_OBJECT
public:
    QString acpData,tempData,outData,capData;//сохранение текущих данных
    int i=0;

    explicit PortS(QObject *parent = nullptr);
    ~PortS();
    bool connect(QString portName);//Соединение с портом
    void parsData(QByteArray b);//Обработка полученных данных

signals:
    void dataReceived();//Передает исходные полученные данные в main

    void threadQuit();//Завершение потока


public slots:
    void dataReady();
    void quitPort();//Cлот Закрытие порта

private:
    QSerialPort *serial;
    QTimer *timer;

};

#endif // SERIALPORT_H
