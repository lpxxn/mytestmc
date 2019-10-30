#ifndef SUPPLIERFORM_H
#define SUPPLIERFORM_H

#include <QMainWindow>

#include "flowlayout.h"

namespace Ui {
class SupplierForm;
}

class SupplierForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit SupplierForm(QWidget *parent = nullptr);
    ~SupplierForm();

    void addbuttons();
    
private slots:
    void on_btnAddDock_clicked();
    void leftDockWidgetReset();

private:
    void addNewDock();
    void addButtons(FlowLayout &layout);

private:
    QDockWidget *leftDock;
    Ui::SupplierForm *ui;
};

#endif // SUPPLIERFORM_H
