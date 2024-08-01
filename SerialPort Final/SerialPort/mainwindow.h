#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <temp.h>
#include <temppogr.h>
#include <psi.h>
#include <settingtemp.h>
#include "ports.h"
#include "portsvolt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool startPort=false,startPortV=false;
private slots:
    void readData();//Получение данных с класса Порта
    void readDataV();//Получение данных с класса Voltmetr

    void on_start_clicked();
    void on_stop_clicked();

    void on_tempPogr_clicked();//Открытие окна температурной погрешности
    void on_PSI_clicked();

    void on_calibration_clicked();//Открытие окна градуировки
    void on_tempSetting_clicked();

    void on_hexCreate_clicked();

    void on_startV_clicked();
    void on_stopV_clicked();


signals:
    void ACPDataSend(QString s);//Сигнал для отправки всех ACP данных в виджетs
    void tempDataSend(QString s);//Сигнал для отправки всех данных температуры в виджеты
    void voltDataSend(QString s); // Сигнал для отправки данных ПСИ
    void portQuit();//Сигнал закрытия порта
    void portQuitV();//Сигнал закрытия порта вольтметра
private:
    Ui::MainWindow *ui;
    PortS port;
    PortSVolt portV;
    QThread thread_1;
    QThread thread_2;
    Temp calibration;
    tempPogr tempP;
    PSI acc_tests;
    settingTemp setting;

    void loadPorts();//Поиск доступных портов
};
#endif // MAINWINDOW_H
