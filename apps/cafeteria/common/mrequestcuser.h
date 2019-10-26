#ifndef MCUSER_H
#define MCUSER_H
#include<QObject>
#include<QNetworkRequest>

#include "loginconfigdata.h"

class QNetworkAccessManager;
class QNetworkReply;
namespace McCommon {

class ResponseUserData {
public:
    QString accessToken;
    QString refreshToken;
    QString clientID;
    QString clientSecriet;
    QString userName;
    QString err;
    QString errDesc;
    QString responseErr;
};

QDebug operator<<(QDebug dbg, const ResponseUserData &data);

class McRequestUser : public QObject
{
    Q_OBJECT
public:
    McRequestUser(QObject *parent = nullptr);
    void loginGet(const QUrl &rul);
    ResponseUserData loginPlay(LoginConfigData const& data);
    ResponseUserData loginSupplier(LoginConfigData const& data);
    ~McRequestUser();
private slots:
    void managerFinished(QNetworkReply*);

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
};

}
#endif // MCUSER_H
