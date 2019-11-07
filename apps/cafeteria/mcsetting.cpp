#include <QDebug>
#include <QCloseEvent>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>

#include "mcsetting.h"
#include "ui_mcsetting.h"
#include "common/loginconfigdata.h"
#include "common/configdata.h"
#include "common/constants.h"

enum A {
    Aa,
    Ab
};

McSetting::McSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::McSetting)
{
    ui->setupUi(this);
    A a = A::Aa;
    if (a == 0) {

    }
    qDebug() << "adfasdf";
    //this->setWindowFlag(Qt::Window);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog); //去除窗体边框
    //this->setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭
    this->setWindowFlag(Qt::Dialog);
    //this->setWindowModality(Qt::ApplicationModal);
    this->setWindowModality(Qt::WindowModal);
    //this->setAttribute(Qt::WA_ShowModal, true);// 已经丢弃了
    if (parent == nullptr) {
        this->setAttribute(Qt::WA_DeleteOnClose, true);
    }
    connect(ui->btnSave, &QPushButton::clicked, this, &McSetting::on_saveBtn_clicked);
    this->settingConfig = new McCommon::SettingConfig();
    readLoginDataToControl();
}

McSetting::~McSetting()
{
    delete ui;
    delete settingConfig;
    qDebug() << "~~McSetting()";
}

void McSetting::closeEvent(QCloseEvent *event)
{
    qDebug() << "closeEvnet";
    if (checkEditControl()) {
        //        event->accept();
        //        return;
    }
    //event->ignore();
    event->accept();
}

bool McSetting::checkEditControl(bool withMsg) const
{
    auto leList = this->findChildren<QLineEdit*>();
    foreach (const auto &item, leList) {
        if (item->text().trimmed().isEmpty()) {
            if (withMsg) {
                QMessageBox msg;
                msg.setText("请完整输入所有数据，并保存！");
                msg.setIcon(QMessageBox::Warning);
                msg.addButton(QMessageBox::Ok);
                msg.exec();
            }
            return false;
        }

    }
    return true;
}

void McSetting::readLoginDataToControl() const
{
    auto devSupplier = McCommon::ConfigData::instance().devSuplierData();
    if (devSupplier != nullptr) {
        this->ui->supplierDevUrl->setText(devSupplier->uri);
        this->ui->supplierDevClientID->setText(devSupplier->clientID);
        this->ui->supplierDevClientSecriet->setText(devSupplier->clientSecriet);
        this->ui->supplierDevUserName->setText(devSupplier->userName);
        this->ui->supplierDevPwd->setText(devSupplier->userPwd);
        this->ui->supplierDevMinute->setChecked(devSupplier->pwdNeedMinute);
    }
    auto proSupplier = McCommon::ConfigData::instance().proSuplierData();
    if (proSupplier != nullptr) {
        this->ui->supplierProUrl->setText(proSupplier->uri);
        this->ui->supplierProClientID->setText(proSupplier->clientID);
        this->ui->supplierProClientSecriet->setText(proSupplier->clientSecriet);
        this->ui->supplierProUserName->setText(proSupplier->userName);
        this->ui->supplierProPwd->setText(proSupplier->userPwd);
        this->ui->supplierProMinute->setChecked(proSupplier->pwdNeedMinute);
    }

    auto devPlay = McCommon::ConfigData::instance().devPlayData();
    if (devPlay != nullptr) {
        this->ui->playDevUrl->setText(devPlay->uri);
        this->ui->playDevClientID->setText(devPlay->clientID);
        this->ui->playDevClientSecriet->setText(devPlay->clientSecriet);
        this->ui->playDevUserName->setText(devPlay->userName);
        this->ui->playDevPwd->setText(devPlay->userPwd);
        this->ui->playDevMinute->setChecked(devPlay->pwdNeedMinute);
    }
    auto proPlay = McCommon::ConfigData::instance().proPlayData();
    if (proPlay != nullptr) {
        this->ui->playProUrl->setText(proPlay->uri);
        this->ui->playProClientID->setText(proPlay->clientID);
        this->ui->playProClientSecriet->setText(proPlay->clientSecriet);
        this->ui->playProUserName->setText(proPlay->userName);
        this->ui->playProPwd->setText(proPlay->userPwd);
        this->ui->playProMinute->setChecked(proPlay->pwdNeedMinute);
    }
}

void McSetting::on_saveBtn_clicked()
{
    if (!checkEditControl()) {
        return;
    }
    McCommon::LoginConfigData devSupplier(this->ui->supplierDevUrl->text(), this->ui->supplierDevClientID->text(), this->ui->supplierDevClientSecriet->text(), this->ui->supplierDevUserName->text(), this->ui->supplierDevPwd->text(), this->ui->supplierDevMinute->isChecked());
    McCommon::LoginConfigData proSupplier(this->ui->supplierProUrl->text(), this->ui->supplierProClientID->text(), this->ui->supplierProClientSecriet->text(), this->ui->supplierProUserName->text(), this->ui->supplierProPwd->text(), this->ui->supplierProMinute->isChecked());
    McCommon::LoginConfigData devPlay(this->ui->playDevUrl->text(), this->ui->playDevClientID->text(), this->ui->playDevClientSecriet->text(), this->ui->playDevUserName->text(), this->ui->playDevPwd->text(), this->ui->playDevMinute->isChecked());
    McCommon::LoginConfigData proPlay(this->ui->playProUrl->text(), this->ui->playProClientID->text(), this->ui->playProClientSecriet->text(), this->ui->playProUserName->text(), this->ui->playProPwd->text(), this->ui->playProMinute->isChecked());
    this->settingConfig->setLoginValue(McCommon::Constants::DEV_SUPPLIER_GROUP, devSupplier);
    this->settingConfig->setLoginValue(McCommon::Constants::PRO_SUPPLIER_GROUP, proSupplier);
    this->settingConfig->setLoginValue(McCommon::Constants::DEV_PLAY_GROUP, devPlay);
    this->settingConfig->setLoginValue(McCommon::Constants::PRO_PLAY_GROUP, proPlay);
}
