#include "hostdialog.h"
#include "ui_hostdialog.h"

HostDialog::HostDialog(
        QString host,
        int port,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HostDialog)
{
    ui->setupUi(this);
    ui->hostLineEdit->setText(host);
    ui->portSpinBox->setValue(port);
}

HostDialog::~HostDialog()
{
    delete ui;
}


QString HostDialog::getHost() const{
    return ui->hostLineEdit->text();
}
int HostDialog::getPort() const{
    return ui->portSpinBox->value();
}
