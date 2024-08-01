#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QMessageBox>
#include <QtGui>
#include <QFile>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadPorts();

    connect(&thread_1,&QThread::started,&port,[this](){port.connect(ui->cmbPorts->currentText());});// Сигнал для сохдания потока
    connect(&port,&PortS::threadQuit,&thread_1,&QThread::terminate);
    port.moveToThread(&thread_1);

    connect(&thread_2,&QThread::started,&portV,[this](){portV.connect(ui->VoltPorts->currentText());});//Сигнал для создания потока Вольтметра
    connect(&portV,&PortSVolt::threadQuit,&thread_2,&QThread::terminate);
    portV.moveToThread(&thread_2);

    connect(&port,&PortS::dataReceived,this,&MainWindow::readData);//Получение данных с класса Порта
    connect(&portV,&PortSVolt::dataReceived,this,&MainWindow::readDataV);//Получение данных с класса Порта

    connect(this,&MainWindow::ACPDataSend,&calibration,&Temp::getACP);//Передача данных АЦП в QLIST градуировки

    connect(this,&MainWindow::ACPDataSend,&tempP,&tempPogr::getPogrACP);//Передача данных АЦП в QLIST температурной погрешности

    connect(this,&MainWindow::tempDataSend,&calibration,&Temp::getTemp);//Передача данных температуры в QLIST градуировки

    connect(this,&MainWindow::tempDataSend,&tempP,&tempPogr::getPogrTemp);//Передача данных температуры в QLIST температурной погрешности

    connect(this,&MainWindow::voltDataSend,&acc_tests,&PSI::getVolt);//Передача данных с вольтметра в ПСИ

    connect(this,&MainWindow::portQuit,&port,&PortS::quitPort);//Сигнал закрытия порта
    connect(this,&MainWindow::portQuitV,&portV,&PortSVolt::quitPortV);//Сигнал закрытия порта Вольтметра


    QFont font;
    font.setPointSize(15);
    ui->ACPEdit->setFont(font);
    ui->outEdit->setFont(font);
    ui->tempEdit->setFont(font);
    ui->CAPEdit->setFont(font);
    ui->voltEdit->setFont(font);

}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::loadPorts(){
    foreach(auto &port, QSerialPortInfo::availablePorts()){
        ui->cmbPorts->addItem(port.portName());
        ui->VoltPorts->addItem(port.portName());
    }
}

void MainWindow::readData(){//считывание данных с программы.

    if(port.acpData!=NULL){
        ui->ACPEdit->setText(port.acpData);
    }
    if(port.tempData!=NULL){
        ui->tempEdit->setText(port.tempData);
    }
    if(port.outData!=NULL){
        ui->outEdit->setText(port.outData);
    }
    if(port.capData!=NULL){
        ui->CAPEdit->setText(port.capData);
    }

    //Проверка есть ли данные в переменных и раскидка по виджетам
    if(port.acpData.size()>1){
        emit ACPDataSend(port.acpData);
    }
    if(port.tempData.size()>1){
        emit tempDataSend(port.tempData);
    }


}

void MainWindow::readDataV(){

    if(portV.voltData!=NULL){
        ui->voltEdit->setText(portV.voltData);
    }
    if(portV.voltData.size()>1){
        emit voltDataSend(portV.voltData);
        portV.voltData.clear();
    }
}

void MainWindow::on_start_clicked()
{

    if(startPort==false){
        thread_1.start();
        startPort=true;
    }else
    {
        QMessageBox::warning(this,"Ошибка подключения к порту","Порт уже открыт");
    }

}


void MainWindow::on_stop_clicked()
{
    if(startPort==true){
        startPort=false;
        emit portQuit();
    }else
    {
        QMessageBox::warning(this,"Ошибка подключения к порту","Нет открытых портов");
    }
}

void MainWindow::on_startV_clicked()
{
    if(startPortV==false){
        thread_2.start();
        startPortV=true;
    }else
    {
        QMessageBox::warning(this,"Ошибка подключения к порту","Порт уже открыт");
    }

}

void MainWindow::on_stopV_clicked()
{
    if(startPortV==true){
        startPortV=false;
        emit portQuitV();
    }else
    {
        QMessageBox::warning(this,"Ошибка подключения к порту","Нет открытых портов");
    }
}


void MainWindow::on_calibration_clicked()
{
    calibration.show();
}

void MainWindow::on_tempPogr_clicked()
{
    tempP.show();
}

void MainWindow::on_PSI_clicked()
{
    acc_tests.show();
}

void MainWindow::on_tempSetting_clicked()
{
    setting.show();
}


void MainWindow::on_hexCreate_clicked()
{
    QMessageBox::information(this,"Cоздание Hex файла","Выберите файл градуировки");
    calibration.on_loadFromJson_clicked();
    QMessageBox::information(this,"Cоздание Hex файла","Выберите файл настройки температуры");
    tempP.on_loadFromJson_clicked();
    if(calibration.count>10 && tempP.countTb1>1 && tempP.countTb2>1 && tempP.countTb3>1 && tempP.countTb4>1 && tempP.countTb5>1){
        calibration.DataToHex();
        tempP.DataToHex();
    }else if (calibration.count<10) QMessageBox::warning(this,"Ошибка создания файла","Недостаточно данных\nв файле \"Градуировка\"");
    else QMessageBox::warning(this,"Ошибка создания файла","Недостаточно данных\nв файле \"Настройка температуры\"");
}
