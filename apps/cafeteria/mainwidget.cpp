#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QtDebug>

#include "common/mrequestcuser.h"
#include "common/configdata.h"
#include "common/settingconfig.h"
#include "supplierform.h"
#include "mcsetting.h"
#include "customerurisetting.h"

void AboutMsg();

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    connect(ui->btnLoginPlayPro, &QPushButton::clicked, this, &MainWidget::on_btnPlayProLogin_clicked);

    McCommon::SettingConfig seetingConfig;
    QTimer::singleShot(1000, this, &MainWidget::afterInit);
    connect(ui->btnSupplierWindow, &QPushButton::clicked, this, &MainWidget::onSupplierOpenWindow);
}

MainWidget::~MainWidget()
{
    delete ui;
}



void MainWidget::on_btnPlayProLogin_clicked()
{
    auto playData = McCommon::ConfigData::instance().proPlayData();
    loginGet(playData);
}

void AboutMsg()
{
    QTime time = QTime::currentTime();
    int minute = time.minute();
    QString MinuteStr = QString("%1").arg(minute, 2, 10, QChar('0'));
    QMessageBox msgBox;
    msgBox.setText("version 1.0 current minute: " +  MinuteStr);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWidget::on_btnSettingWin_clicked()
{
    McSetting *ms = new McSetting;

    ms->show();
    qDebug() << "close mc setting widget";
}

void MainWidget::afterInit()
{
    qDebug() << "run afeter init";
}

void MainWidget::on_playDev_clicked()
{
    auto playData = McCommon::ConfigData::instance().devPlayData();
    loginGet(playData);
}

void MainWidget::loginGet(const McCommon::LoginConfigData *param)
{
    if (param == nullptr) {
        McCommon::ConfigData::DataEmpyWarrmingMsgBox();
        return;
    }
    qDebug() << param->getURL();
    McCommon::McRequestUser mcures(this);
    auto revData = mcures.loginPlay(*param);
    textEdirConsoleAuthInfo(revData);
}

void MainWidget::textEdirConsoleAuthInfo(const McCommon::ResponseUserData &data)
{
    ui->textEdit->appendPlainText("userName: " + data.userName);
    ui->textEdit->appendPlainText("clientID: " + data.clientID);
    ui->textEdit->appendPlainText("clientSecret: " + data.clientSecriet);
    if (data.responseErr.isEmpty()) {
        ui->textEdit->appendPlainText("Authorization: bearer " + data.accessToken);
        ui->textEdit->appendPlainText("");
    } else {
        ui->textEdit->appendPlainText("err: " + data.err);
        ui->textEdit->appendPlainText("errDesc" + data.errDesc);
        ui->textEdit->appendPlainText("responseErr: " + data.responseErr);
        ui->textEdit->appendPlainText("");
    }
}

void MainWidget::on_btnSupplierDevLogin_clicked()
{
    auto param = McCommon::ConfigData::instance().devSuplierData();

    if (param == nullptr) {
        McCommon::ConfigData::DataEmpyWarrmingMsgBox();
        return;
    }
    McCommon::McRequestUser mcures(this);
    auto revData = mcures.loginSupplier(*param);
    textEdirConsoleAuthInfo(revData);
}

void MainWidget::on_pushButton_clicked()
{
    auto param = McCommon::ConfigData::instance().proSuplierData();

    if (param == nullptr) {
        McCommon::ConfigData::DataEmpyWarrmingMsgBox();
        return;
    }
    McCommon::McRequestUser mcures(this);
    auto revData = mcures.loginSupplier(*param);
    textEdirConsoleAuthInfo(revData);
}

void MainWidget::on_btnClearEdit_clicked()
{
    ui->textEdit->clear();
}

void MainWidget::onSupplierOpenWindow()
{
//    SupplierForm *supplierForm = new SupplierForm;
//    supplierForm->show();

    auto *customerUriSetting = new CustomerUriSetting(this);
    customerUriSetting->show();
}
