#ifndef TEMP_H
#define TEMP_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QMessageBox>

namespace Ui {
class Temp;
}

class Temp : public QWidget
{
    Q_OBJECT

public:
    QString acpData,tempData;
    int count=0;
    void DataToHex();
    explicit Temp(QWidget *parent = nullptr);
    ~Temp();

public slots:
    void on_writeOne_clicked();//Добавление записи в таблицу
    void getACP(QString s);//Получение всех данных ACP
    void getTemp(QString s);//Получение всех данных ACP
    void on_loadFromJson_clicked();//Загрузка данных из файла
signals:
    void clickTemp();
private slots:
    void on_deleteOne_clicked();//Удаление записи из таблицы
    void on_saveToJson_clicked();//Сохранение таблицы в json

private:
    Ui::Temp *ui;
};

#endif // TEMP_H
