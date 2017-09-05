#include "sqlopen.h"

sqlopen::sqlopen()
{

}
bool sqlopen::opensqlserver(QString user,QString password)
{

    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString::fromLocal8Bit("test"));
    db.setHostName("localhost");
    db.setUserName(user);
    db.setPassword(password);
    QSqlError error=db.lastError();
    if(!db.open())
    {
       QMessageBox::critical(NULL, "Error", "密码或用户名错误", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
       return false;
    }
    else
       QMessageBox::information(NULL, "Welcom", "数据库连接成功", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return true;
}
