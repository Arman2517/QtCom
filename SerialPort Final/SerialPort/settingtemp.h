#ifndef SETTINGTEMP_H
#define SETTINGTEMP_H

#include <QWidget>

namespace Ui {
class settingTemp;
}

class settingTemp : public QWidget
{
    Q_OBJECT

public:
    explicit settingTemp(QWidget *parent = nullptr);
    ~settingTemp();

private slots:
    void on_save_clicked();

    void on_loadFromJson_clicked();

private:
    Ui::settingTemp *ui;
};

#endif // SETTINGTEMP_H
