#ifndef SUPPLIERFORM_H
#define SUPPLIERFORM_H

#include <QWidget>

namespace Ui {
class SupplierForm;
}

class SupplierForm : public QWidget
{
    Q_OBJECT

public:
    explicit SupplierForm(QWidget *parent = nullptr);
    ~SupplierForm();

private:
    Ui::SupplierForm *ui;
};

#endif // SUPPLIERFORM_H
