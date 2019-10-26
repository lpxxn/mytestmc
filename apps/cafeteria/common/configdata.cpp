#include "configdata.h"


namespace McCommon {

ConfigData &ConfigData::instance()
{
    static ConfigData instance;
    return instance;
}

void ConfigData::setDevSupplier(const LoginConfigData& copy)
{
    instance().initLoginData(instance().devSupplier, copy);
}

void ConfigData::setProSupplier(const LoginConfigData& copy)
{
    instance().initLoginData(instance().proSupplier, copy);
}

void ConfigData::setDevPlay(const LoginConfigData& copy)
{
    instance().initLoginData(instance().devPlay, copy);
}

void ConfigData::setProPlay(const LoginConfigData& copy)
{
    instance().initLoginData(instance().proPlay, copy);
}

const LoginConfigData *ConfigData::devSuplierData() const
{
    return this->devSupplier;
}

const LoginConfigData *ConfigData::proSuplierData() const
{
    return this->proSupplier;
}

const LoginConfigData *ConfigData::devPlayData() const
{
    return this->devPlay;
}

const LoginConfigData *ConfigData::proPlayData() const
{
    return this->proPlay;
}

void ConfigData::DataEmpyWarrmingMsgBox()
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Warning);
    msg.setText("请配置数据");
    msg.addButton(QMessageBox::Ok);
    msg.exec();
}

ConfigData::ConfigData()
{

}

void ConfigData::initLoginData(LoginConfigData *&data, const LoginConfigData& copy)
{
    if (data== nullptr) {
        data = new LoginConfigData(copy);
    } else {
        data->uri = copy.uri;
        data->clientID = copy.clientID;
        data->clientSecriet = copy.clientSecriet;
        data->userName = copy.userName;
        data->userPwd = copy.userPwd;
        data->pwdNeedMinute = copy.pwdNeedMinute;
    }
}

ConfigData::~ConfigData()
{
    if (this->devSupplier != nullptr) {
        delete this->devSupplier;
        this->devSupplier = nullptr;
    }

    if (this->proSupplier != nullptr) {
        delete this->proSupplier;
        this->proSupplier = nullptr;
    }
    if (this->devPlay != nullptr) {
        delete this->devPlay;
        this->devPlay = nullptr;
    }
    if (this->proPlay != nullptr) {
        delete this->proPlay;
        this->proPlay = nullptr;
    }
}

}
