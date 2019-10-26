#ifndef LOGINDATA_H
#define LOGINDATA_H

#include <QSettings>
#include <QUrl>

namespace McCommon {

class LoginConfigData
{
public:
    LoginConfigData(QString uri, QString clientID, QString clientSecriet, QString userName, QString userPwd, bool pwdNeedMinute);
    virtual QUrl getURL() const;

    QUrl getOriginURL() const;

    virtual ~LoginConfigData();
public:
    QString uri;
    QString clientID;
    QString clientSecriet;
    QString userName;
    QString userPwd;
    bool pwdNeedMinute;
};

QDebug operator<<(QDebug dbg, const LoginConfigData &data);
}
#endif // LOGINDATA_H
