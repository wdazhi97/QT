#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(300,150);
    ui->password->setEchoMode(QLineEdit::Password);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    open=new sqlopen();
    if(open->opensqlserver(ui->user->text(),ui->password->text()))
      {
       username=ui->user->text();
       this->close();
    MainWindow *w;
    w=new MainWindow();
    w->usernames=username;
    w->dbstate=true;
    w->trans(open);
    w->status();
    w->show();
    }
}


void Dialog::on_pushButton_2_clicked()
{
    this->close();
}
