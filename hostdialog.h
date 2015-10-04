#ifndef HOSTDIALOG_H
#define HOSTDIALOG_H

#include <QDialog>

namespace Ui {
class HostDialog;
}

class HostDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HostDialog(QString host, int port, QWidget *parent = 0);
    ~HostDialog();

    QString getHost() const;
    int getPort() const;

private:
    Ui::HostDialog *ui;
};

#endif // HOSTDIALOG_H
