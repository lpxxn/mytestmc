#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "common/loginconfigdata.h"
#include "common/mrequestcuser.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_btnPlayProLogin_clicked();

    void on_btnSettingWin_clicked();

    void afterInit();

    void on_playDev_clicked();

    void on_btnSupplierDevLogin_clicked();

    void on_pushButton_clicked();

    void on_btnClearEdit_clicked();

private:
    void loginGet(const McCommon::LoginConfigData *param);
    void textEdirConsoleAuthInfo(const McCommon::ResponseUserData &data);

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
