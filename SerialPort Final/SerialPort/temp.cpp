#include "temp.h"
#include "ui_temp.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QString>


Temp::Temp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Temp)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(11);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"АЦП \n последовательный \n выход"<<"АЦП \n обратный \n выход"<<"t");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    QFont font;
    font.setPointSize(15);
    ui->tempEdit->setFont(font);
    ui->ACPEdit->setFont(font);
    ui->tableWidget->setFont(font);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

Temp::~Temp()
{
    delete ui;
}

void Temp::on_writeOne_clicked()
{
    if(acpData.size()>3 && count<11)
    {

        QTableWidgetItem *tb = new QTableWidgetItem(acpData);
        QTableWidgetItem *tb1 = new QTableWidgetItem(tempData);//

        ui->tableWidget->setItem(count,0,tb);
        ui->tableWidget->setItem(count,2,tb1);

        acpData.clear();
        tempData.clear();

        count=count+1;
    }
    else if(acpData.size()>3 && count<22){
        QTableWidgetItem *tb = new QTableWidgetItem(acpData);
        ui->tableWidget->setItem(22-count-1,1,tb);
        count=count+1;
    }
    else if(count>1 && acpData.size()>2)QMessageBox::critical(this,"Write error","No place to write!");
    else QMessageBox::critical(this,"Write error","No data to write!");
}

void Temp::on_deleteOne_clicked(){
    if(count>11){
        count=count-1;
        ui->tableWidget->setItem(21-count,1,NULL);
    }
    else if(count>0){
        count=count-1;
        ui->tableWidget->setItem(count,0,NULL);
        ui->tableWidget->setItem(count,2,NULL);
    }else QMessageBox::critical(this,"Delete error","No data to delete!");
}

void Temp::getACP(QString s){

    ui->ACPEdit->setText(s);
    acpData=s;

}

void Temp::getTemp(QString s){

    ui->tempEdit->setText(s);
    tempData=s;
}

void Temp::on_saveToJson_clicked()
{

    QString path;
    path=QFileDialog::getSaveFileName();
    QFile fileJson(path);
    fileJson.open(QIODevice::WriteOnly);

    QJsonObject json;
    json["rowCount"] = ui->tableWidget->rowCount();
    json["columnCount"] = ui->tableWidget->columnCount();

    QJsonArray data;
    for(int i= 0; i<ui->tableWidget->rowCount(); i++){
        QJsonArray row;
        for(int j=0; j<ui->tableWidget->columnCount(); j++){
            if(ui->tableWidget->item(i,j)!=0 && j!=1){
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

void Temp::on_loadFromJson_clicked()
{

    QString val;
    QFile file;
    file.setFileName(QFileDialog::getOpenFileName());
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    val = file.readAll();


    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject json = doc.object();
    QJsonArray data = json["data"].toArray();

    while(count>0){
        on_deleteOne_clicked();
    }

    for(int i=0;i<data.size();i++){
        if(data[i].toArray().size()>0){//Если в ячейках не пусто
            QJsonArray arr = data[i].toArray();
            count++;
            for (int j=0;j<3;j++){
                if(j==0){
                    QTableWidgetItem *tb = new QTableWidgetItem(arr[j].toString());
                    ui->tableWidget->setItem(i,j,tb);
                }
                if(j==1){
                    QTableWidgetItem *tb = new QTableWidgetItem(arr[j].toString());
                    ui->tableWidget->setItem(i,j+1,tb);
                }
            }
        }
    }
    file.close();
}

void Temp::DataToHex()
{
    int countSave=count;
    if(count>11){
        count=11;
    }
    QFile file;
    file.setFileName("Dav_113.hex");
    file.open(QIODevice::WriteOnly);
    file.write(":020000040000FA");
    file.write("\n");

    QString hex;// строка для hex файла
    QString dataS[16];
    QString dataS2[16];
    char start=':';

    while (count>0){
        QString sizeData=ui->tableWidget->item(count-1,0)->text();
        sizeData = QString("%1").arg(sizeData.toUInt(),0,16);
        if (sizeData.size()==1)
        {
            sizeData.push_back("000");
        }
        else if(sizeData.size()==2)
        {
            sizeData.push_back("00");

        }else if(sizeData.size()==3)
        {
            sizeData.push_back("0");
        }
        dataS[count-1]=sizeData.left(2);
        dataS2[count-1]=sizeData.right(2);
        count--;
    }
    count=countSave;
    if(count>11){
        count=11;
    }

    quint16 LoadOffset=0xF140;//адрес
    quint16 rectyp=0x00;//тип записи
    quint16 crc=0x00;

    unsigned long int CHKSUM;

    quint16 reclen=0;//Количество байт в строке
    int j=0;
    QString infoS;

    while(j<count){
        if(reclen<2){
            reclen+=2;
            crc=crc+dataS[j].toInt(nullptr,16);
            infoS+=dataS[j];
            if(crc>0x100){
                crc=(crc-0x100);
            }
            crc=crc+dataS2[j].toInt(nullptr,16);
            infoS+=dataS2[j];
            if(crc>0x100){
                crc=(crc-0x100);
            }
            quint16 Load1=LoadOffset>>8;//Первая половина
            quint16 Load2=LoadOffset&0xFF;//Вторая половина
            crc=crc+reclen;
            if(crc>0x100){
                crc=(crc-0x100);
            }
            crc=crc+Load1;
            if(crc>0x100){
                crc=(crc-0x100);
            }
            crc=crc+Load2;
            if(crc>0x100){
                crc=(crc-0x100);
            }
            crc=crc+rectyp;
            if(crc>0x100){
                crc=(crc-0x100);
            }
            QString z;
            CHKSUM=(0x100-crc);
            hex+=start;
            hex+="0";
            hex+=QString("%1").arg(reclen,0,16);
            z=QString("%1").arg(LoadOffset,0,16);
            hex+=z;
            z=QString("%1").arg(rectyp,0,16);
            z.push_back("0");
            hex+=z;
            hex+=infoS;
            z=QString("%1").arg(CHKSUM,0,16);
            if(z.size()<2)z.push_front("0");
            hex+=z;
            hex.toStdString();
            file.write(hex.toUtf8().toUpper());
            file.write("\n");

            hex.clear();
            crc=0;
            infoS.clear();
            reclen=0;
            LoadOffset+=0x0002;
        }

        j++;
    }

    file.close();
}

