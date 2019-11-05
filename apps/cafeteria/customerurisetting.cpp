#include "customerurisetting.h"
#include "ui_customeurisetting.h"

CustomerUriSetting::CustomerUriSetting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CostomeURISetting)
{
    ui->setupUi(this);
    QWidget::setWindowFlags(this->windowFlags()|Qt::Dialog);
    QWidget::setWindowModality(Qt::WindowModal);
    if (parent == nullptr) {
        this->setAttribute(Qt::WA_DeleteOnClose);
    }
}

CustomerUriSetting::~CustomerUriSetting()
{
    delete ui;
}
