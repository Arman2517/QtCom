#ifndef PSI_H
#define PSI_H

#include <QWidget>

namespace Ui {
class PSI;
}

class PSI : public QWidget
{
    Q_OBJECT

public:

    explicit PSI(QWidget *parent = nullptr);
    ~PSI();
    QString voltData;
    int countTemps=0;

private slots:
    void on_save_clicked();
    void on_loadFromJson_clicked();
    void on_writeOne_clicked();
    void on_deleteOne_clicked();

public slots:
    void getVolt(QString s);//Получение всех данных volt

private:
    Ui::PSI *ui;
};

#endif // PSI_H
