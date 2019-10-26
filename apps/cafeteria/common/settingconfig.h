#ifndef SETTINGCONFIG_H
#define SETTINGCONFIG_H
#include <QSettings>
#include <QMap>
#include "loginconfigdata.h"

namespace McCommon {

using setLogiFunc =  void (const LoginConfigData &);

class SettingConfig
{
public:
    SettingConfig();
    void readConfig();
    void setLoginValue(const QString &groupKey, const LoginConfigData &loginData);

    ~SettingConfig();

private:

    void readLoginValue(QString settingKey);

private:
    QMap<QString, setLogiFunc*> settingGroupMap;
    QSettings *confSettings;
};
}
#endif // SETTINGCONFIG_H
