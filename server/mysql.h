#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

class MySql
{
public :
    MySql();

    QSqlQuery selectClient(QString sql);
    void insertClient(QString sql);
    void deleteClient(QString sql);
    void updateClient(QString sql);
    void emptyClient();
private:
    QSqlDatabase db;
};

#endif // CONNECTION_H
