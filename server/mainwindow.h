#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mysql.h"
#include "position.h"
#include <QWidget>
#include "gamethread.h"
#include <QCloseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMutex>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int getThread_id();//获取新开启子线程的线程id
private:
    QTcpServer *tcpServer;//tcp服务器
    QList<QTcpSocket*> tcpClient;//客户端连接列表
    QTcpSocket *currentClient;//现在连接的客户端
    void sendData(QTcpSocket* client,Position *pos,int color,int judgeColor);//向客户端传递数据
    MySql *mysql;//数据库

private slots:
    void NewConnectionSlot();//新建连接信号槽
    void disconnectedSlot();//断开连接信号槽
    void ReadData();//获取客户端传递的数据
    void getBlackPosition(int id,Position * pos,int judgeColor);//从子线程获取棋局信息并返回给黑棋用户
    void getWhitePosition(int id,Position * pos,int judgeColor);//从子线程获取棋局信息并返回给白棋用户
    void getID(int id);//获取新线程的线程id
    void getStopID(int id);//获取棋局结束后中止线程的id,从而删去数据库中相关信息
private:
    GameThread *thread1;
    GameThread *thread2;//完成棋局逻辑的类的实体
    QThread *threadA;
    QThread *threadB;//movetothread的对象,即运行的子线程
    int Thread_id;//保存新建线程的线程Id
signals:
    void sendLocation(int id,int x,int y,int color);//将客户端传入服务器的用户落子信息发送给该用户所在棋局的线程
    void startinit1();//对线程1初始化
    void startinit2();//对线程2初始化
};

#endif // MAINWINDOW_H
