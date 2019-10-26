#include "settingconfig.h"

#include <QCoreApplication>
#include <QDebug>
#include <QStandardPaths>

#include "constants.h"
#include "configdata.h"

namespace McCommon {

SettingConfig::SettingConfig()
{
    settingGroupMap[Constants::DEV_SUPPLIER_GROUP] = &ConfigData::instance().setDevSupplier;
    settingGroupMap[Constants::PRO_SUPPLIER_GROUP] = &ConfigData::instance().setProSupplier;
    settingGroupMap[Constants::DEV_PLAY_GROUP] = &ConfigData::instance().setDevPlay;
    settingGroupMap[Constants::PRO_PLAY_GROUP] = &ConfigData::instance().setProPlay;

    confSettings = new  QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    qDebug() << confSettings->allKeys() << QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    qDebug() << QCoreApplication::organizationName() << "  " << QCoreApplication::applicationName() << confSettings->fileName();
    char devCafe[] = "devCafeteriq";
    confSettings->beginGroup(devCafe);
    confSettings->setValue("a", "aaaa");
    confSettings->endGroup();
    readConfig();
}

void SettingConfig::readConfig()
{
    this->readLoginValue(Constants::DEV_SUPPLIER_GROUP);
    this->readLoginValue(Constants::PRO_SUPPLIER_GROUP);
    this->readLoginValue(Constants::DEV_PLAY_GROUP);
    this->readLoginValue(Constants::PRO_PLAY_GROUP);
}

SettingConfig::~SettingConfig()
{
    delete confSettings;
}

void SettingConfig::readLoginValue(QString settingKey)
{
    bool haveItem = false;
    foreach (auto const &item, this->confSettings->allKeys()) {
          if (item.contains(settingKey,  Qt::CaseInsensitive)) {
              haveItem = true;
          }
    }
    if (!haveItem) {
        return;
    }
    if (this->settingGroupMap.contains(settingKey)) {
        auto setFun = this->settingGroupMap[settingKey];
        confSettings->beginGroup(settingKey);
        auto uri = confSettings->value(Constants::CONFIG_URI).toString();
        auto clientID = confSettings->value(Constants::CONFIG_CLIENT_ID).toString();
        auto clientSecriet = confSettings->value(Constants::CONFIG_CLIENT_SECRIET).toString();
        auto userName = confSettings->value(Constants::CONFIG_USER_NAME).toString();
        auto pwd = confSettings->value(Constants::CONFIG_USER_PWD).toString();
        auto needMinute = confSettings->value(Constants::CONFIG_PWD_NEED_MINUTE, false).toBool();
        setFun(LoginConfigData(uri, clientID, clientSecriet, userName, pwd, needMinute));
        confSettings->endGroup();
    }

}

void SettingConfig::setLoginValue(const QString &groupKey, const LoginConfigData &loginData)
{
    if (this->settingGroupMap.contains(groupKey)) {
        auto setFun = this->settingGroupMap[groupKey];
        confSettings->beginGroup(groupKey);
        confSettings->setValue(Constants::CONFIG_URI, loginData.uri);
        confSettings->setValue(Constants::CONFIG_CLIENT_ID, loginData.clientID);
        confSettings->setValue(Constants::CONFIG_CLIENT_SECRIET, loginData.clientSecriet);
        confSettings->setValue(Constants::CONFIG_USER_NAME, loginData.userName);
        confSettings->setValue(Constants::CONFIG_USER_PWD, loginData.userPwd);
        confSettings->setValue(Constants::CONFIG_PWD_NEED_MINUTE, loginData.pwdNeedMinute);
        confSettings->endGroup();
        setFun(loginData);
    }
}

}
