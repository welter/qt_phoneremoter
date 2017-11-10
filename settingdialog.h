#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
//#include <mainwindow.h>
namespace Ui {
class settingDialog;
}
class MainWindow;
class settingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingDialog(QWidget *parent = 0);
    ~settingDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::settingDialog *ui;
    MainWindow *p;
};

#endif // SETTINGDIALOG_H
