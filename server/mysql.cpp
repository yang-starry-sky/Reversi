#include "mysql.h"
MySql::MySql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("flip_chess");//数据库名
    db.setUserName("root");
    db.setPassword("136955");   //密码
    if (!db.open()) {
    QMessageBox::critical(0, QObject::tr("无法打开数据库"),
    "无法创建数据库连接！ ", QMessageBox::Cancel);

    }
}

QSqlQuery MySql::selectClient(QString sql)
{
    QSqlQuery query(db);
    query.exec(sql);
    return query;
}

void MySql::insertClient(QString sql)
{
    QSqlQuery query(db);
    query.exec(sql);
}

void MySql::deleteClient(QString sql)
{
    QSqlQuery query(db);
    query.exec(sql);
}
void MySql::updateClient(QString sql){
    QSqlQuery query(db);
    query.exec(sql);
}

void MySql::emptyClient()
{
    QSqlQuery query(db);
    query.exec("TRUNCATE client_thread");
}
