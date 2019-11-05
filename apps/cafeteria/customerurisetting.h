#ifndef CUSTOMERURISETTING_H
#define CUSTOMERURISETTING_H

#include <QMainWindow>

namespace Ui {
class CostomeURISetting;
}

class CustomerUriSetting : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerUriSetting(QWidget *parent = nullptr);
    ~CustomerUriSetting();

private:
    Ui::CostomeURISetting *ui;
};

#endif // CUSTOMERURISETTING_H
