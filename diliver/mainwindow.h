#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSqlQueryModel>
#include <QDate>
#include "sqlopen.h"
#include "dialog.h"
#include "about.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    sqlopen *sqldb;
    QString usernames;
    QLabel *user;
    QLabel *username;
    QLabel *dbstatus;
    QLabel *dbstates;
    QSqlQueryModel *model;
    bool dbstate;
    void trans(sqlopen *a);
    void status();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();
    void connectdatabase();
    void disconnectdatabase();
    void OpenAbout();
    void on_pushButton_clicked();
    void advancedsearch();
    void neworder();
    void employeeinformation();
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
