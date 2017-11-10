#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <mainwindow.h>
settingDialog::settingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingDialog)
{
//    char * _p=parent;
    p=dynamic_cast <MainWindow *>(parent);
    ui->setupUi(this);
    ui->textEdit->setText(dynamic_cast <MainWindow *>(parent)->_phoneAddr);
}

settingDialog::~settingDialog()
{
    delete ui;
}

void settingDialog::on_buttonBox_accepted()
{

}
