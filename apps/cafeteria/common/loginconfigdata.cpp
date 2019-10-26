#include "loginconfigdata.h"
#include <QTime>
#include <QtDebug>

namespace McCommon {

LoginConfigData::LoginConfigData(QString uri, QString clientID, QString clientSecriet, QString userName, QString userPwd, bool pwdNeedMinute):
    uri(uri), clientID(clientID), clientSecriet(clientSecriet), userName(userName), userPwd(userPwd), pwdNeedMinute(pwdNeedMinute)
{

}

QUrl LoginConfigData::getURL() const
{
    QString pwd = this->userPwd;
    if (this->pwdNeedMinute) {
       // pwd.append(this->currentMinute());
    }
    auto urlStr = this->uri.arg(this->clientID).arg(this->clientSecriet).arg(this->userName).arg(pwd);
    auto url = QUrl(urlStr);
    return url;
}

QUrl LoginConfigData::getOriginURL() const
{
    return QUrl(this->uri);
}

LoginConfigData::~LoginConfigData()
{

}

QDebug operator<<(QDebug dbg, const LoginConfigData &data)
{
    dbg.nospace() << "LoginDaga: " << data.uri;
    return dbg.maybeSpace();
}

}
