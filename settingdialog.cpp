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
    ui->edPhoneAddr->setText(dynamic_cast <MainWindow *>(parent)->_phoneAddr);
    ui->edPhonePort->setText(QString::number(p->_phonePort));
}

settingDialog::~settingDialog()
{

}

void settingDialog::on_buttonBox_accepted()
{
    p->_phoneAddr=ui->edPhoneAddr->text();
    p->_phonePort=ui->edPhonePort->text().toShort();
    delete ui;
}

