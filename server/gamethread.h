#ifndef GAMETHREAD_H
#define GAMETHREAD_H
#include <QDebug>
#include <QThread>
#include <QtCore>
#include <QObject>
#include <QMutex>
#include "position.h"

class GameThread:public QObject
{
    Q_OBJECT
public:
    GameThread();//构造函数
    bool end=false;//判断线程是否结束
public:
    Position *position;//定义一盘棋局在一个线程内
private slots:
    void getLocation(int id,int x,int y,int color);//获取主线程传来的用户所下棋子的位置及颜色,改变棋局状态并返回给两位用户
    void init();//对线程进行初始化
signals:
    void sendBlackPosition(int id,Position *pos,int judgeColor);//将用户落子后被改变的棋局传给黑棋用户
    void sendWhitePosition(int id,Position *pos,int judgeColor);//将用户落子后被改变的棋局传给白棋用户
    void sendID(int id);//将子线程建立后的线程id号发给主线程
    void stopThread();//停止线程
    void sendStopID(int id);//将中止线程的线程id号发给主线程
};

#endif // GAMETHREAD_H
