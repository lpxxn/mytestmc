#include "supplierform.h"
#include "ui_supplierform.h"

SupplierForm::SupplierForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierForm)
{
    ui->setupUi(this);
}

SupplierForm::~SupplierForm()
{
    delete ui;
}
