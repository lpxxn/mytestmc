#include "mrequestcuser.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QString>
#include <QTime>

#include <QJsonDocument>
#include <QJsonObject>

#include "util.h"

namespace McCommon {

McRequestUser::McRequestUser(QObject *parent):QObject(parent)
{
    manager = new QNetworkAccessManager();
    progressDialog = new QProgressDialog();
    progressDialog->setCancelButton(nullptr);
    //QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply *)));
    QObject::connect(manager, &QNetworkAccessManager::finished, this, &McRequestUser::managerFinished);
    //    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
    //        if (reply->error()) {
    //            qDebug() << reply->errorString();
    //            return;
    //        }

    //        QString answer = reply->readAll();

    //        qDebug() << answer;
    //    }
    //);
}

McRequestUser::McRequestUser(QWidget *parent):QObject(parent)
{
    manager = new QNetworkAccessManager();
    progressDialog = new QProgressDialog(parent);
    progressDialog->setCancelButton(nullptr);
    //QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply *)));
    QObject::connect(manager, &QNetworkAccessManager::finished, this, &McRequestUser::managerFinished);
}

void McRequestUser::loginGet(const QUrl &url)
{
    request.setUrl(url);
    qDebug() << request.url().url();
    QNetworkReply *response = manager->get(request);

    if (response->error()) {
        qDebug() << response->errorString();
    }
    responseHandle(*response);

    //qDebug() << rese->readAll();// will be empty. will run managerFinished
    qDebug() << "finshed request";
}

ResponseUserData McRequestUser::loginPlay(const LoginConfigData &data)
{   
    QString pwd = data.userPwd;
    if (data.pwdNeedMinute) {
        pwd.append(currentMinute());
    }
    auto urlStr = data.uri.arg(data.clientID).arg(data.clientSecriet).arg(data.userName).arg(pwd);
    auto url = QUrl(urlStr);
    this->request.setUrl(url);

    qDebug() << urlStr << "\n" << request.url().url();
    QNetworkReply *response = manager->get(request);
    responseHandle(*response);
    //qDebug() << rese->readAll();// will be empty. will run managerFinished
    qDebug() << "finshed request";

    QByteArray buffer = response->readAll();
    qDebug() << "response body: "<< buffer;

    ResponseUserData revData;
    revData.clientID = data.clientID;
    revData.clientSecriet = data.clientSecriet;
    revData.userName = data.userName;
    if (response->error()) {
        revData.responseErr = response->errorString();
        qDebug() << revData.responseErr;
        //return;
    }

    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonReply = jsonDoc.object();
    if (jsonReply.contains("error")) {
        revData.err = jsonReply["error"].toString();
        revData.errDesc = jsonReply["error_description"].toString();
    } else {
        revData.accessToken = jsonReply["access_token"].toString();
        revData.refreshToken = jsonReply["refresh_token"].toString();

    }
    qDebug() << revData;
    return revData;
}

ResponseUserData McRequestUser::loginSupplier(const LoginConfigData &data)
{
    QVariantMap jsonMap;
    jsonMap.insert("responseType", "token");
    jsonMap.insert("grantType", "token");
    jsonMap.insert("type", 2);
    jsonMap.insert("username", data.userName);
    jsonMap.insert("password", data.userPwd);
    QVariant a = QVariant(jsonMap);
    QJsonDocument doc = QJsonDocument::fromVariant(a);
    auto jsonString = doc.toJson();

    this->request.setUrl(data.uri);
    this->request.setRawHeader("clientID", data.clientID.toUtf8());
    this->request.setRawHeader("clientSecret", data.clientSecriet.toUtf8());
    this->request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *response = manager->post(request, jsonString);

    responseHandle(*response);
    //qDebug() << rese->readAll();// will be empty. will run managerFinished
    qDebug() << "finshed request";

    QByteArray buffer = response->readAll();
    qDebug() << "response body: "<< buffer;

    ResponseUserData revData;
    revData.clientID = data.clientID;
    revData.clientSecriet = data.clientSecriet;
    revData.userName = data.userName;
    if (response->error()) {
        revData.responseErr = response->errorString();
        qDebug() << revData.responseErr;
        //return;
    }

    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonReply = jsonDoc.object();
    if (jsonReply.contains("error")) {
        revData.err = jsonReply["error"].toString();
        revData.errDesc = jsonReply["error_description"].toString();
    } else {
        QJsonObject dataBody = jsonReply["data"].toObject();
        revData.accessToken = dataBody["accessToken"].toString();
        revData.refreshToken = dataBody["refreshToken"].toString();

    }
    qDebug() << revData;
    return revData;
}

McRequestUser::~McRequestUser()
{
    delete manager;
    delete progressDialog;
}

void McRequestUser::managerFinished(QNetworkReply *)
{
//    QByteArray buffer = response->readAll();
//    qDebug() << "response body: "<< buffer;

//    if (response->error()) {
//        qDebug() << response->errorString();
//        //return;
//    }

//    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
//    QJsonObject jsonReply = jsonDoc.object();
//    if (jsonReply.contains("error")) {
//        qDebug() << jsonReply["error"].toString();
//        qDebug() << jsonReply["error_description"].toString();
//        return;
//    }
//    QString accessToken = jsonReply["access_token"].toString();
    //    qDebug() << "accessToken: "<< accessToken;
}

void McRequestUser::updateDownloadProgress(qint64 byteRead, qint64 total)
{
    this->progressDialog->setMaximum(int(total));
    this->progressDialog->setValue(int(byteRead));
}

void McRequestUser::httpDownloadFinished()
{
   this->progressDialog->hide();
}

void McRequestUser::progressDialogShow(const QString &uri)
{
    progressDialog->setLabelText(uri);

}

void McRequestUser::responseHandle(const QNetworkReply &resp)
{
    connect(&resp, &QNetworkReply::downloadProgress, this, &McRequestUser::updateDownloadProgress);
    connect(&resp, &QNetworkReply::finished, this, &McRequestUser::httpDownloadFinished);
    this->progressDialog->show();
    QEventLoop loop;
    connect(&resp, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

QDebug operator<<(QDebug dbg, const ResponseUserData &data)
{
    dbg.nospace() << "responseData: AccessToken: " << data.accessToken << " refreshToekn: " << data.refreshToken << " clientID: " << data.clientID << " clientSecriet: " << data.clientSecriet
                  << "\n" << data.responseErr << " err :" << data.err << " errDesc: " << data.errDesc;
    return dbg.maybeSpace();
}

}
