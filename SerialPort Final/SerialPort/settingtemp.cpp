#include "settingtemp.h"
#include "ui_settingtemp.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

settingTemp::settingTemp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingTemp)
{
    ui->setupUi(this);

    ui->tb1->setRowCount(2);
    ui->tb1->setColumnCount(3);
    ui->tb1->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb1->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb1->verticalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb1->verticalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb1->setHorizontalHeaderLabels(QStringList()<<"-40"<<"AЦП"<<"t");
    for(int i=0;i<ui->tb1->rowCount();i++){
        for(int j=0;j<ui->tb1->columnCount();j++){
            ui->tb1->setItem(i,j,new QTableWidgetItem());
        }
    }

    ui->tb2->setRowCount(2);
    ui->tb2->setColumnCount(3);
    ui->tb2->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb2->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb2->verticalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb2->verticalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb2->setHorizontalHeaderLabels(QStringList()<<"-10"<<"AЦП"<<"t");
    for(int i=0;i<ui->tb2->rowCount();i++){
        for(int j=0;j<ui->tb2->columnCount();j++){
            ui->tb2->setItem(i,j,new QTableWidgetItem());
        }
    }

    ui->tb3->setRowCount(2);
    ui->tb3->setColumnCount(3);
    ui->tb3->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb3->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb3->verticalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb3->verticalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb3->setHorizontalHeaderLabels(QStringList()<<"25"<<"AЦП"<<"t");
    for(int i=0;i<ui->tb3->rowCount();i++){
        for(int j=0;j<ui->tb3->columnCount();j++){
            ui->tb3->setItem(i,j,new QTableWidgetItem());
        }
    }

    ui->tb4->setRowCount(2);
    ui->tb4->setColumnCount(3);
    ui->tb4->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb4->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb4->verticalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb4->verticalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb4->setHorizontalHeaderLabels(QStringList()<<"40"<<"AЦП"<<"t");
    for(int i=0;i<ui->tb4->rowCount();i++){
        for(int j=0;j<ui->tb4->columnCount();j++){
            ui->tb4->setItem(i,j,new QTableWidgetItem());
        }
    }

    ui->tb5->setRowCount(2);
    ui->tb5->setColumnCount(3);
    ui->tb5->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb5->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb5->verticalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb5->verticalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb5->setHorizontalHeaderLabels(QStringList()<<"60"<<"AЦП"<<"t");
    for(int i=0;i<ui->tb5->rowCount();i++){
        for(int j=0;j<ui->tb5->columnCount();j++){
            ui->tb5->setItem(i,j,new QTableWidgetItem());
        }
    }
}

settingTemp::~settingTemp()
{
    delete ui;
}

void settingTemp::on_save_clicked()
{
    QString path;
    path=QFileDialog::getSaveFileName();
    QFile fileJson(path);
    fileJson.open(QIODevice::WriteOnly);

    QJsonObject json;
    json["rowCount"] = ui->tb1->rowCount();
    json["columnCount"] = ui->tb1->columnCount();

    QJsonArray data;
    for(int i= 0 ; i<ui->tb1->rowCount(); i++){
        QJsonArray row;
        for(int j=0; j<ui->tb1->columnCount(); j++){
            if(ui->tb1->item(i,j)!=0){
                row.append(QJsonValue(ui->tb1->item(i,j)->text()));
            }
        }
        data.append(row);
    }
    json["tb1"] = data;

    while(data.count()){//очистка массива
        data.pop_back();
    }

    for(int i= 0 ; i<ui->tb2->rowCount(); i++){
        QJsonArray row;
        for(int j=0; j<ui->tb2->columnCount(); j++){
            if(ui->tb2->item(i,j)!=0){
                row.append(QJsonValue(ui->tb2->item(i,j)->text()));
            }
        }
        data.append(row);
    }
    json["tb2"] = data;

    while(data.count()){
        data.pop_back();
    }
    for(int i= 0 ; i<ui->tb3->rowCount(); i++){
        QJsonArray row;
        for(int j=0; j<ui->tb3->columnCount(); j++){
            if(ui->tb3->item(i,j)!=0){
                row.append(QJsonValue(ui->tb3->item(i,j)->text()));
            }
        }
        data.append(row);
    }
    json["tb3"] = data;

    while(data.count()){
        data.pop_back();
    }

    for(int i= 0 ; i<ui->tb4->rowCount(); i++){
        QJsonArray row;
        for(int j=0; j<ui->tb4->columnCount(); j++){
            if(ui->tb4->item(i,j)!=0){
                row.append(QJsonValue(ui->tb4->item(i,j)->text()));
            }
        }
        data.append(row);
    }
    json["tb4"] = data;

    while(data.count()){
        data.pop_back();
    }

    for(int i= 0 ; i<ui->tb5->rowCount(); i++){
        QJsonArray row;
        for(int j=0; j<ui->tb5->columnCount(); j++){
            if(ui->tb5->item(i,j)!=0){
                row.append(QJsonValue(ui->tb5->item(i,j)->text()));
            }
        }
        data.append(row);
    }
    json["tb5"] = data;
    QJsonDocument saveDoc(json);
    fileJson.write(saveDoc.toJson());
    fileJson.close();
}

void settingTemp::on_loadFromJson_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName();
    QString val;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    val = file.readAll();


    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject json = doc.object();

    QString tb;
    tb="tb1";
    QJsonArray data = json[tb].toArray();
    for(int i=0;i<data.size();i++){
        if(data.at(i)!=""){
            QJsonArray arr = data[i].toArray();
            for (int j=0;j<3;j++) {
                QTableWidgetItem *tb = new QTableWidgetItem(arr[j].toString());
                ui->tb1->setItem(i,j,tb);
            }
        }
    }
    tb="tb2";
    data = json[tb].toArray();
    for(int i=0;i<data.size();i++){
        if(data.at(i)!=""){
            QJsonArray arr = data[i].toArray();
            for (int j=0;j<3;j++) {
                QTableWidgetItem *tb = new QTableWidgetItem(arr[j].toString());
                ui->tb2->setItem(i,j,tb);
            }
        }
    }
    tb="tb3";
    data = json[tb].toArray();
    for(int i=0;i<data.size();i++){
        if(data.at(i)!=""){
            QJsonArray arr = data[i].toArray();
            for (int j=0;j<3;j++) {
                QTableWidgetItem *tb = new QTableWidgetItem(arr[j].toString());
                ui->tb3->setItem(i,j,tb);
            }
        }
    }
    tb="tb4";
    data = json[tb].toArray();
    for(int i=0;i<data.size();i++){
        if(data.at(i)!=""){
            QJsonArray arr = data[i].toArray();
            for (int j=0;j<3;j++) {
                QTableWidgetItem *tb = new QTableWidgetItem(arr[j].toString());
                ui->tb4->setItem(i,j,tb);
            }
        }
    }
    tb="tb5";
    data = json[tb].toArray();
    for(int i=0;i<data.size();i++){
        if(data.at(i)!=""){
            QJsonArray arr = data[i].toArray();
            for (int j=0;j<3;j++) {
                QTableWidgetItem *tb = new QTableWidgetItem(arr[j].toString());
                ui->tb5->setItem(i,j,tb);
            }
        }
    }
    file.close();
}
