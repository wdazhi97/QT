#ifndef SQLOPEN_H
#define SQLOPEN_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QMessageBox>
class sqlopen
{
public:
    QSqlDatabase db;
    sqlopen();
    bool opensqlserver(QString user,QString password);
};

#endif // SQLOPEN_H
