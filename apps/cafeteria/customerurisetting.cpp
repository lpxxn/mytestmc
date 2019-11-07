#include "customerurisetting.h"
#include "ui_customeurisetting.h"

#include <QDir>

CustomerUriSetting::CustomerUriSetting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CostomeURISetting)
{
    ui->setupUi(this);
    //QWidget::setWindowFlags(this->windowFlags()|Qt::Dialog);
    //QWidget::setWindowModality(Qt::WindowModal);

    // as modal type
    QMainWindow::setWindowModality(Qt::ApplicationModal);
    if (parent == nullptr) {
        this->setAttribute(Qt::WA_DeleteOnClose);
    }
}

CustomerUriSetting::~CustomerUriSetting()
{
    delete ui;
}
