#ifndef MCSETTING_H
#define MCSETTING_H

#include <QWidget>

#include <common/settingconfig.h>

namespace Ui {
class McSetting;
}

class McSetting : public QWidget
{
    Q_OBJECT

public:
    explicit McSetting(QWidget *parent = nullptr);
    ~McSetting();

private:
    void closeEvent(QCloseEvent *event);
    bool checkEditControl(bool withMsg = true) const;
    void readLoginDataToControl() const;


private slots:
    void on_saveBtn_clicked();
private:
    Ui::McSetting *ui;
    McCommon::SettingConfig *settingConfig;
};

#endif // MCSETTING_H
