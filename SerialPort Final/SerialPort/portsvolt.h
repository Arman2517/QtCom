#ifndef PORTSVOLT_H
#define PORTSVOLT_H

#include <QObject>
#include <QSerialPortInfo>
#include <QtSerialPort>
#include <QTimer>

class PortSVolt : public QObject
{
    Q_OBJECT
public:
    QString voltData;// Данные полученные с вольтметра
    bool firstCon=false; // проверка на соединение

    explicit PortSVolt(QObject *parent = nullptr);
    ~PortSVolt();
    bool connect(QString portName);//Соединение с портом
    void parsData(QByteArray b);//Обработка полученных данных

signals:
    void dataReceived();//Передает исходные полученные данные в main

    void threadQuit();//Завершение потока


public slots:
    void dataReady();
    void quitPortV();//Cлот Закрытие порта
    void valinquiry();
private:

    QSerialPort *serial;
    QTimer *timer;

};

#endif // PORTSVOLT_H
