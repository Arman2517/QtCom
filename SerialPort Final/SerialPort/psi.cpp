#include "psi.h"
#include "ui_psi.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QDebug>
#include <QByteArray>

PSI::PSI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PSI)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Давление"<<"Выходное\nнапряжение");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<1;j++){
            QString s=QString::number((double)(i+1)/10);
            QTableWidgetItem *tb = new QTableWidgetItem(s);
            ui->tableWidget->setItem(i,j,tb);
        }
    }
}

PSI::~PSI()
{
    delete ui;
}

void PSI::on_save_clicked()
{
    QString path;
    path=QFileDialog::getSaveFileName();
    QFile fileJson(path);
    fileJson.open(QIODevice::WriteOnly);

    QJsonObject json;
    json["rowCount"] = ui->tableWidget->rowCount();
    json["columnCount"] = ui->tableWidget->columnCount();

    QJsonArray data;
    for(int i= 0 ; i<ui->tableWidget->rowCount(); i++){
        QJsonArray row;
        for(int j=0; j<ui->tableWidget->columnCount(); j++){
            if(ui->tableWidget->item(i,j)!=0){
                row.append(QJsonValue(ui->tableWidget->item(i,j)->text()));
            }
        }
        data.append(row);
    }
    json["data"] = data;
    QJsonDocument saveDoc(json);
    fileJson.write(saveDoc.toJson());
    fileJson.close();

}

void PSI::on_loadFromJson_clicked()
{
    while(countTemps>0){
        on_deleteOne_clicked();
    }
    QString path;
    path = QFileDialog::getOpenFileName();
    QString val;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    val = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject json = doc.object();
    QJsonArray data = json["data"].toArray();

    for(int i=0;i<data.size();i++){
        if(data.at(i)!="" && data[i].toArray().size()>1){
            countTemps++;
            QJsonArray arr = data[i].toArray();
            for (int j=0;j<2;j++) {
                QTableWidgetItem *tb = new QTableWidgetItem(arr[j].toString());
                ui->tableWidget->setItem(i,j,tb);
            }
        }
    }
    file.close();
}

void PSI::getVolt(QString s)
{
    ui->lineEdit->setText(s);
    voltData=s;
}

void PSI::on_writeOne_clicked()
{
    QString x1;
    if(voltData.size()>0 && countTemps<10)
    {
        x1=voltData;
        voltData="";
        QTableWidgetItem *tb = new QTableWidgetItem(x1);
        ui->tableWidget->setItem(countTemps,1,tb);
        countTemps=countTemps+1;

    }else if(countTemps>1 && voltData.size()>0) QMessageBox::critical(this,"Write error","No place to write!");
    else QMessageBox::critical(this,"Write error","No data to write!");

}

void PSI::on_deleteOne_clicked()
{
    if(countTemps>0){
        countTemps=countTemps-1;
        ui->tableWidget->setItem(countTemps,1,NULL);
    }else QMessageBox::critical(this,"Delete error","No data to delete!");
}



