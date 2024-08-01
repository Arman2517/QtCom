#ifndef TEMPPOGR_H
#define TEMPPOGR_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class tempPogr;
}

class tempPogr : public QWidget
{
    Q_OBJECT

public:
    QString acpData,tempData;
    int countTb1=0,countTb2=0,countTb3=0,countTb4=0,countTb5=0;
    QString sizeData;//null
    QString sizeData2;//nom
    QString sizeData3;//температура
    QString dataS0[16];
    QString dataS1[16];
    QString dataS2[16];
    QString dataS3[16];
    QString dataS4[16];
    QString dataS5[16];
    void DataToHex();
    void sizeCheck(QString *sizeData);
    void tbCheck(QTableWidget *tb,int i);
    explicit tempPogr(QWidget *parent = nullptr);
    ~tempPogr();

public slots:
    void getPogrACP(QString s);//Получение всех данных ACP
    void getPogrTemp(QString s);//Получение всех данных temp
    void on_loadFromJson_clicked();//Нажатие на кнопку загрузить из файла
private slots:
    void on_save_clicked();
    void on_write_one_clicked();
    void on_delete_one_clicked();
private:
    void procJson(QJsonArray data,int &count,QTableWidget &tw);
    bool write_table(QTableWidget *tw,int &count);
    void delete_table(QTableWidget *tw,int &count);
    Ui::tempPogr *ui;
};

#endif // TEMPPOGR_H
