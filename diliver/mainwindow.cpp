#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->action_2->setShortcut(tr("ctrl+O"));
    ui->action_4->setShortcut(tr("ctrl+Z"));
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(connectdatabase()));
    connect(ui->disconnect,SIGNAL(triggered(bool)),this,SLOT(disconnectdatabase()));
    connect(ui->action_4,SIGNAL(triggered(bool)),this,SLOT(OpenAbout()));
    connect(ui->action_5,SIGNAL(triggered(bool)),this,SLOT(advancedsearch()));
    connect(ui->action_6,SIGNAL(triggered(bool)),this,SLOT(employeeinformation()));
    connect(ui->action_7,SIGNAL(triggered(bool)),this,SLOT(neworder()));

    model = new QSqlQueryModel;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonBox_accepted()
{
    QSqlQuery *query=new QSqlQuery(sqldb->db);
    QString orderkey=ui->orderkey->text();
    QString company=ui->company->text();
    query->exec(QString("select *from search where orderkey=%1 and comname='%2'").arg(orderkey).arg(company));
    query->next();
    QString result;
    QString reciever;
    result=query->value(1).toString();
    if(result.compare("",Qt::CaseSensitive))
    {
    ui->sender->setText(result);
    result=query->value(2).toString();
    ui->senderphone->setText(result);
    result=query->value(4).toString();
    ui->orderkey1->setText(result);
    result=query->value(5).toString();
    ui->orderdate->setText(result);
    result=query->value(6).toString();
    ui->postman->setText(result);
    result=query->value(7).toString();
    ui->postphone->setText(result);
    result=query->value(8).toString();
    ui->stop->setText(result);
    result=query->value(9).toString();
    ui->address->setText(result.simplified());
    reciever=query->value(3).toString();
   // qDebug()<<QString("select name ,phone from customer where CUSTKEY=%1").arg(reciever);
    query->exec(QString("select name ,phone from dbo.customer where CUSTKEY=%1").arg(reciever));
    query->next();
    result=query->value(0).toString();
    ui->receiver->setText(result);
    result=query->value(1).toString();
    ui->recieverphone->setText(result);
   /*
sendkey0,sendname1,sendphone2,reciver3,orderkey4,orderdate5,postman6,postnum7,dstop8,Addr9,comname
*/
    ui->tabWidget->setCurrentIndex(1);
    }
    else
        QMessageBox::information(NULL, "Sorry", "该条不存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void MainWindow::on_buttonBox_rejected()
{
    ui->company->setText("");
    ui->orderkey->setText("");
}
void MainWindow::trans(sqlopen *a)
{
    sqldb=a;
}
void MainWindow::connectdatabase()
{
    QMessageBox box;
    box.setWindowTitle(tr("警告"));
    box.setIcon(
                QMessageBox::Warning);
    box.setText(tr("是否重新连接，应用会重启！"));
    box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);
    box.setWindowIcon(QIcon(":/new/prefix1/refresh.ico"));
    if(box.exec()==QMessageBox::Yes)
    {
    Dialog *newopen=new Dialog();
    newopen->show();
    this->close();
    }
}
void MainWindow::disconnectdatabase()
{
    QMessageBox box;
    box.setWindowTitle(tr("警告"));
    box.setIcon(
                QMessageBox::Warning);
    box.setText(tr("是否断开数据库"));
    box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);
    box.setWindowIcon(QIcon(":/new/prefix1/refresh.ico"));
    if(box.exec()==QMessageBox::Yes)
    {
    sqldb->db.close();
    dbstatus->setStyleSheet("color:red");
    dbstates->setStyleSheet("color:red");
    dbstates->setText("关闭");
    }
}

void MainWindow::on_pushButton_clicked()
{
   ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}
void MainWindow::OpenAbout()
{
    about *a=new about();
    a->show();
}
void MainWindow::status()
{
    user=new QLabel(this);
    user->setText("用户");
    username =new QLabel(this);
    username->setText(usernames);
    dbstatus=new QLabel(this);
    dbstatus->setText("数据库状态");
    dbstates=new QLabel(this);
    if(dbstate)
    {
        dbstates->setText("打开");
        dbstatus->setStyleSheet("color:green");
        dbstates->setStyleSheet("color:green");
     }
    else
    {
        dbstatus->setStyleSheet("color:red");
        dbstates->setStyleSheet("color:red");
        dbstates->setText("关闭");
    }
    ui->statusBar->addWidget(user);
    ui->statusBar->addWidget(username);
    ui->statusBar->addWidget(dbstatus);
    ui->statusBar->addWidget(dbstates);
}
void MainWindow::advancedsearch()
{
    ui->tabWidget->setCurrentIndex(2);
}
void MainWindow::neworder()
{
    QStringList stoplist;
    ui->tabWidget->setCurrentIndex(3);
    QSqlQuery *query=new QSqlQuery(sqldb->db);
    query->exec("select distinct dstop,dkey from manage_company order by dkey");
    while(query->next())
    {
        stoplist <<query->value(0).toString();
    }
    ui->comboBox_2->addItems(stoplist);

}
void MainWindow::employeeinformation()
{
    ui->tabWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_5_clicked()
{
    QSqlQuery *query=new QSqlQuery(sqldb->db);
    QString postresult;
    postresult=ui->inputp->text();
    query->exec(QString("select *from view_postman where name='%1'").arg(postresult));
    query->next();
    ui->pname->setText(query->value(0).toString());
    ui->pphone->setText(query->value(1).toString());
    ui->pcompany->setText(query->value(2).toString().simplified());
    ui->psex->setText(query->value(3).toString());
}

void MainWindow::on_pushButton_6_clicked()
{
    QSqlQuery *query=new QSqlQuery(sqldb->db);
    QString employeeresult;
    employeeresult=ui->inpute->text();
    query->exec(QString("select *from view_employee where ename='%1'").arg(employeeresult));
    query->next();
    ui->ename->setText(query->value(0).toString());
    ui->ephone->setText(query->value(1).toString());
    ui->estop->setText(query->value(2).toString().simplified());
    ui->eposition->setText(query->value(3).toString());
}

void MainWindow::on_pushButton_7_clicked()
{
    model->setQuery(QString ("select * from advancedsearch where 发件人='%1'").arg(ui->dependname->text()));
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::on_pushButton_8_clicked()
{
    model->setQuery(QString ("select * from advancedsearch where 所在站='%1'").arg(ui->dependstop->text()));
    qDebug()<<QString ("select * from advancedsearch where dstop='%1'").arg(ui->dependstop->text());
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::on_pushButton_9_clicked()
{
    model->setQuery(QString ("select * from advancedsearch where 发件日期='%1'").arg(ui->dependate->text()));
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->senderman->clear();
    ui->sphone->clear();
    ui->comboBox->clear();
    ui->recieverman->clear();
    ui->rphone->clear();
    ui->saddress->clear();
    ui->raddress->clear();
    ui->comboBox_2->clear();
}


void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QStringList comlist;
    QSqlQuery *query=new QSqlQuery(sqldb->db);
    query->exec(QString("select distinct company from manage_company where dstop='%1'").arg(ui->comboBox_2->currentText()));
    while(query->next())
    {
        comlist <<query->value(0).toString();
    }
    ui->comboBox->clear();
    ui->comboBox->addItems(comlist);
}

void MainWindow::on_pushButton_3_clicked()
{
    int de[256]={0};
    int i=1;
    //插入收发件人
    QSqlQuery *query=new QSqlQuery(sqldb->db);
    query->exec("select count(*) from customer");
    query->next();
    int a=query->value(0).toInt();
    a++;
    int s=a;
    query->exec(QString("insert into customer (custkey,name,phone) values (%1,'%2','%3')").arg(a).arg(ui->senderman->text()).arg(ui->sphone->text()));
    //qDebug()<<QString("insert into customer (custkey,name,phone) values (%1,'%2','%3')").arg(s).arg(ui->recieverman->text()).arg(ui->rphone->text());
    query->exec("select count(*) from customer");
    query->next();
    a=query->value(0).toInt();
    a++;
    int r=a;
    query->exec(QString("insert into customer (custkey,name,phone) values (%1,'%2','%3')").arg(a).arg(ui->recieverman->text()).arg(ui->rphone->text()));
    //qDebug()<<QString("insert into customer (custkey,name,phone) values (%1,'%2','%3')").arg(r).arg(ui->senderman->text());
    // ///////////////////////////////////
    query->exec("select count(*) from orders");
    query->next();
    int  b=query->value(0).toInt();
    b++;
    query->exec("select count(*)from delivery");
    query->next();
    int c=query->value(0).toInt();
    c++;
    //快递状态
    query->exec(QString("select stopkey from deliverystop where name='%1'").arg(ui->comboBox_2->currentText()));
    query->next();
    int stopkey=query->value(0).toInt();
    query->exec("select count(*) from deliverystate");
    query->next();
    int d=query->value(0).toInt();
    d++;
    query->exec(QString("insert into deliverystate (statekey,issend,isrecieved,stopkey) values (%1,%2,%3,%4)").arg(d).arg(0).arg(0).arg(stopkey));
    //qDebug()<<QString("insert into deliverystate (statekey,issend,isrecieved,stopkey) values (%1,%2,%3,%4)").arg(d).arg(0).arg(0).arg(stopkey);
    //快递
    query->exec(QString("select pnu from post_con where cname='%1'").arg(ui->comboBox->currentText()));
    while(query->next())
    {
        de[i]=query->value(0).toInt();
        i++;
    }
    query->exec(QString("insert into delivery (deliverykey,senderkey,statekey,sendaddress,recieveaddress,receiver) values (%1,%2,%3,'%4','%5',%6)").arg(c).arg(2).arg(d).arg(ui->saddress->text()).arg(ui->raddress->text()).arg(r));
    //qDebug()<<QString("insert into delivery (deliverykey,senderkey,statekey,sendaddress,recieveraddress,reciever) values (%1,%2,%3,'%4','%5',%6)").arg(c).arg(2).arg(d).arg(ui->saddress->text()).arg(ui->raddress->text()).arg(r);
    QString date=QDate::currentDate().toString("yyyy-MM-dd");
    query->exec(QString("insert into orders (orderkey,custkey,orderdate,deliverykey) values (%1,%2,'%3',%4)").arg(b).arg(s).arg(date).arg(c));
    //qDebug()<<QString("insert into orders (orderkey,custkey,orderdate,deliverykey) values (%1,%2,'%3',%4)").arg(b).arg(s).arg("2017-01-03").arg(c);
}
