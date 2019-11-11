#ifndef CUSTOMERURISETTING_H
#define CUSTOMERURISETTING_H

#include <QDir>
#include <QtSql>
#include <QMainWindow>

#include "common/kvcomboboxdelegate.h"

namespace Ui {
class CostomeURISetting;
}

class CustomerUriSetting : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerUriSetting(QWidget *parent = nullptr);
    ~CustomerUriSetting();

protected:
    bool openDb(const QString &dbPath = QDir::currentPath() + "/postmandb.db3");
    void openTable();

private:
    Ui::CostomeURISetting *ui;
    QSqlDatabase db;
    QSqlTableModel *tableModel;
    QItemSelectionModel *itemSelectionModel;

    McCommon::KvComboBoxDelegate projectDelegate;
};

#endif // CUSTOMERURISETTING_H
