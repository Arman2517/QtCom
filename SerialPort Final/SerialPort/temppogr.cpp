#include "temppogr.h"
#include "ui_temppogr.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <QMessageBox>

tempPogr::tempPogr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tempPogr)
{
    ui->setupUi(this);

    QFont font;
    font.setPointSize(15);
    ui->tempEdit->setFont(font);
    ui->ACPEdit->setFont(font);

    ui->tb1->setRowCount(2);
    ui->tb1->setColumnCount(3);
    ui->tb1->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb1->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb1->setHorizontalHeaderLabels(QStringList()<<"-40"<<"AЦП"<<"t");
    for(int i=0;i<2;i++){
        QTableWidgetItem *ot = new QTableWidgetItem(i);//заполнение первого столбца
        ui->tb1->setItem(i,0,ot);
    }

    ui->tb2->setRowCount(2);
    ui->tb2->setColumnCount(3);
    ui->tb2->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb2->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb2->setHorizontalHeaderLabels(QStringList()<<"-10"<<"AЦП"<<"t");
    for(int i=0;i<2;i++){
        QTableWidgetItem *ot = new QTableWidgetItem(i);//заполнение первого столбца
        ui->tb2->setItem(i,0,ot);
    }

    ui->tb3->setRowCount(2);
    ui->tb3->setColumnCount(3);
    ui->tb3->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb3->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb3->setHorizontalHeaderLabels(QStringList()<<"25"<<"AЦП"<<"t");
    for(int i=0;i<2;i++){
        QTableWidgetItem *ot = new QTableWidgetItem(i);//заполнение первого столбца
        ui->tb3->setItem(i,0,ot);
    }

    ui->tb4->setRowCount(2);
    ui->tb4->setColumnCount(3);
    ui->tb4->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb4->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb4->setHorizontalHeaderLabels(QStringList()<<"40"<<"AЦП"<<"t");
    for(int i=0;i<2;i++){
        QTableWidgetItem *ot = new QTableWidgetItem(i);//заполнение первого столбца
        ui->tb4->setItem(i,0,ot);
    }

    ui->tb5->setRowCount(2);
    ui->tb5->setColumnCount(3);
    ui->tb5->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tb5->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tb5->setHorizontalHeaderLabels(QStringList()<<"60"<<"AЦП"<<"t");
    for(int i=0;i<2;i++){
        QTableWidgetItem *ot = new QTableWidgetItem(i);//заполнение первого столбца
        ui->tb5->setItem(i,0,ot);
    }
}

void tempPogr::getPogrACP(QString s){

    ui->ACPEdit->setText(s);
    acpData=s;
}

void tempPogr::getPogrTemp(QString s){
    ui->tempEdit->setText(s);
    tempData=s;
}

void tempPogr::on_write_one_clicked(){

    if(ui->rb1->isChecked()){
        if(write_table(ui->tb1,countTb1)==1) countTb1=countTb1+1;
    }
    if(ui->rb2->isChecked()){
        if(write_table(ui->tb2,countTb2)==1) countTb2=countTb2+1;
    }
    if(ui->rb3->isChecked()){
        if(write_table(ui->tb3,countTb3)==1) countTb3=countTb3+1;
    }
    if(ui->rb4->isChecked()){
        if(write_table(ui->tb4,countTb4)==1) countTb4=countTb4+1;
    }
    if(ui->rb5->isChecked()){
        if(write_table(ui->tb5,countTb5)==1)countTb5=countTb5+1;
    }
}

bool tempPogr::write_table(QTableWidget *tw,int &count)
{
    if(acpData.size()>3 && count<2)
    {
        QTableWidgetItem *tb = new QTableWidgetItem(acpData);
        QTableWidgetItem *tb1 = new QTableWidgetItem(tempData);
        tw->setItem(count,1,tb);
        tw->setItem(count,2,tb1);
        acpData="";
        tempData="";

    }
    else if(count>1 && acpData.size()>3){
        QMessageBox::critical(this,"Write error","No place to write!");
        return false;
    }
    else{
        QMessageBox::critical(this,"Write error","No data to write!");
        return false;
    }
    return true;
}

void tempPogr::on_delete_one_clicked(){
    if(ui->rb1->isChecked()){
        delete_table(ui->tb1,countTb1);
    }
    if(ui->rb2->isChecked()){
        delete_table(ui->tb2,countTb2);
    }
    if(ui->rb3->isChecked()){
        delete_table(ui->tb3,countTb3);
    }
    if(ui->rb4->isChecked()){
        delete_table(ui->tb4,countTb4);
    }
    if(ui->rb5->isChecked()){
        delete_table(ui->tb5,countTb5);
    }
}

void tempPogr::delete_table(QTableWidget *tw, int &count){
    if(count>0){
        count=count-1;
        tw->setItem(count,1,NULL);
        tw->setItem(count,2,NULL);
    } else QMessageBox::critical(this,"Delete error","Nothing to delete!");
}

void tempPogr::on_save_clicked()
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

    while(data.count()){
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
    for(int i=0; i<ui->tb3->rowCount(); i++){
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

void tempPogr::on_loadFromJson_clicked()
{
    while (countTb1>0){
        delete_table(ui->tb1,countTb1);
    }
    while (countTb2>0){
        delete_table(ui->tb2,countTb2);
    }
    while (countTb3>0){
        delete_table(ui->tb3,countTb3);
    }
    while (countTb4>0){
        delete_table(ui->tb4,countTb4);
    }
    while (countTb5>0){
        delete_table(ui->tb5,countTb5);
    }

    QString val;
    QFile file;
    file.setFileName(QFileDialog::getOpenFileName());
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    val = file.readAll();


    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject json = doc.object();


    QString tb;
    tb="tb1";
    procJson(json[tb].toArray(),countTb1,*ui->tb1);

    tb="tb2";
    procJson(json[tb].toArray(),countTb2,*ui->tb2);

    tb="tb3";
    procJson(json[tb].toArray(),countTb3,*ui->tb3);

    tb="tb4";
    procJson(json[tb].toArray(),countTb4,*ui->tb4);

    tb="tb5";
    procJson(json[tb].toArray(),countTb5,*ui->tb5);
    file.close();
}

void tempPogr::procJson(QJsonArray data,int &count,QTableWidget &tw)
{
    for(int i=0;i<data.size();i++){
        QJsonArray arr = data[i].toArray();
        if(arr.size()>1 && arr[1]!=""){
            for (int j=0;j<3;j++) {//можно начать с j=1;
                QTableWidgetItem *tb = new QTableWidgetItem(arr[j].toString());
                tw.setItem(i,j,tb);
            }
            count=count+1;
        }
    }
}


tempPogr::~tempPogr()
{
    delete ui;
}


void tempPogr::DataToHex()
{
    QFile file;
    file.setFileName("Dav_113.hex");
    file.open(QIODevice::Append);

    QString hex;// Строка для hex файла

    char start=':';

    tbCheck(ui->tb1,0);
    tbCheck(ui->tb2,1);
    tbCheck(ui->tb3,2);
    tbCheck(ui->tb4,3);
    tbCheck(ui->tb5,4);

    QString dataSS[32];

    int j=0;
    for(int i=0;i<10;i+=2){
        dataSS[i]=dataS0[j];
        dataSS[i+1]=dataS3[j];
        dataSS[i+10]=dataS1[j];
        dataSS[i+11]=dataS4[j];
        dataSS[i+20]=dataS2[j];
        dataSS[i+21]=dataS5[j];
        j++;
    }

    quint16 LoadOffset=0xF158;//адрес
    quint16 rectyp=0x00;//тип записи
    quint16 crc=0x00;//контрольная сумма

    unsigned long int CHKSUM;

    quint16 reclen=0;//Количество байт в строке
    QString infoS;

    for(int j=0;j<30;j+=2){
        if(reclen<2){
            reclen+=2;
            crc=crc+dataSS[j].toInt(nullptr,16);//перевод из шестнадцатеричной
            infoS+=dataSS[j];
            if(crc>0x100){
                crc=(crc-0x100);
            }
            crc=crc+dataSS[j+1].toInt(nullptr,16);//перевод из шестнадцатеричной
            infoS+=dataSS[j+1];
            if(crc>0x100){
                crc=(crc-0x100);
            }
            crc=crc+reclen;
            if(crc>0x100){
                crc=(crc-0x100);
            }
            crc=crc+(LoadOffset>>8);
            if(crc>0x100){
                crc=(crc-0x100);
            }
            crc=crc+(LoadOffset&0xFF);
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
    }

    file.write(":00000001FF");
    file.close();
}

void tempPogr::sizeCheck(QString *sizeData){
    if (sizeData->size()==1)
    {
        sizeData->push_back("000");
    }
    else if(sizeData->size()==2)
    {
        sizeData->push_back("00");

    }else if(sizeData->size()==3)
    {
        sizeData->push_back("0");
    }

}
void tempPogr::tbCheck(QTableWidget *tb,int i)
{
    sizeData=tb->item(0,1)->text();//null
    sizeData2=tb->item(1,1)->text();//nom
    sizeData3=tb->item(0,2)->text();//температура
    sizeData = QString("%1").arg(sizeData.toUInt(),0,16);
    sizeData2 = QString("%1").arg(sizeData2.toUInt(),0,16);
    sizeData3 = QString("%1").arg(sizeData3.toUInt(),0,16);
    sizeCheck(&sizeData);
    sizeCheck(&sizeData2);
    sizeCheck(&sizeData3);
    dataS0[i]=sizeData.left(2);
    dataS1[i]=sizeData2.left(2);
    dataS2[i]=sizeData3.left(2);
    dataS3[i]=sizeData.right(2);
    dataS4[i]=sizeData2.right(2);
    dataS5[i]=sizeData3.right(2);
}

