#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <sqlopen.h>
#include <mainwindow.h>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    sqlopen *open;
    QString username;
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
