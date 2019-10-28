#ifndef MCUSER_H
#define MCUSER_H
#include<QObject>
#include <QWidget>
#include<QNetworkRequest>
#include<QProgressDialog>

#include "loginconfigdata.h"

class QNetworkAccessManager;
class QNetworkReply;
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
    McRequestUser(QWidget *parent = nullptr);
    void loginGet(const QUrl &rul);
    ResponseUserData loginPlay(LoginConfigData const& data);
    ResponseUserData loginSupplier(LoginConfigData const& data);
    ~McRequestUser();
private slots:
    void managerFinished(QNetworkReply*);
    void updateDownloadProgress(qint64 byteRead, qint64 total);
    void httpDownloadFinished();

private:
    void progressDialogShow(QString const& uri);
    void responseHandle(const QNetworkReply &resp);

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QProgressDialog *progressDialog;
};

}
#endif // MCUSER_H
