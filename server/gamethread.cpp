#include "gamethread.h"
#include <QDebug>
#include <QMutex>
#include <stdlib.h>

GameThread::GameThread()
{
    position=new Position();
}

void GameThread::init()
{
    position=new Position();
    emit sendID(QString::number(quintptr(QThread::currentThreadId())).toInt());
    /*qDebug()<<"White-----------";
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            qDebug()<<position->getChess(i,j);
    qDebug()<<"-----------";*/
    emit sendWhitePosition(QString::number(quintptr(QThread::currentThreadId())).toInt(),position,0);
    position->moveChess(0);
    /*qDebug()<<"Black-----------";
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            qDebug()<<position->getChess(i,j);
    qDebug()<<"-----------";*/
    emit sendBlackPosition(QString::number(quintptr(QThread::currentThreadId())).toInt(),position,0);

}
void GameThread::getLocation(int id, int x, int y, int color)
{
    qDebug()<<QString::number(quintptr(QThread::currentThreadId()));
    int m,n;
    qDebug()<<id;
    qDebug()<<QString::number(quintptr(QThread::currentThreadId())).toInt();
    if(id==QString::number(quintptr(QThread::currentThreadId())).toInt())//如果棋局所在线程为本线程
    {
    position->Turn_over_chess(x,y,color);//根据用户落子翻转棋局
    position->Remove();//去掉无用的位置信息
    position->moveChess(1-color);//获取另一位用户可下位置
    m=position->Judge();//判断该用户是否能够落子
    position->calculateScores();//计算得分
    if(m!=0)//如果另一位用户可以落子
    {
       emit sendBlackPosition(id,position,1-color);
       emit sendWhitePosition(id,position,1-color);//向黑白用户返回相应棋局信息
    }
    else//如果另一位用户不能落子
    {
       position->moveChess(color);
       n=position->Judge();//判断该用户能否落子
       if(n!=0)//如果能落子
       {
          emit sendBlackPosition(id,position,color);
          emit sendWhitePosition(id,position,color);//向黑白用户返回相应棋局信息
       }
       else//如果两位用户均不能落子,棋局结束
       {
           position->setEnd(true);//设置结束标志
           emit sendBlackPosition(id,position,color);
           emit sendWhitePosition(id,position,color);//向黑白用户返回相应棋局信息
           emit sendStopID(id);//向主线程传递结束子线程线程id
           emit stopThread();//停止线程
       }
    }
    }
}
