#ifndef CONFIGDATA_H
#define CONFIGDATA_H
#include <QString>
#include <QUrl>
#include <QMessageBox>

#include "loginconfigdata.h"

namespace McCommon {
class ConfigData
{
public:
    static ConfigData& instance();

    ConfigData(ConfigData const&)      =delete;
    void operator=(ConfigData const&)  =delete;
    static void setDevSupplier(const LoginConfigData& copy);
    static void setProSupplier(const LoginConfigData& copy);
    static void setDevPlay(const LoginConfigData& copy);
    static void setProPlay(const LoginConfigData& copy);

    const LoginConfigData* devSuplierData() const;
    const LoginConfigData* proSuplierData() const;
    const LoginConfigData* devPlayData() const;
    const LoginConfigData* proPlayData() const;

    static void DataEmpyWarrmingMsgBox();

    ~ConfigData();

private:
    ConfigData();
    void initLoginData(LoginConfigData *&data, const LoginConfigData& copy);


    LoginConfigData *devSupplier = nullptr;
    LoginConfigData *proSupplier = nullptr;
    LoginConfigData *devPlay = nullptr;
    LoginConfigData *proPlay = nullptr;

};


}

#endif // CONFIGDATA_H
