#ifndef POSITION_H
#define POSITION_H

#define ROW 8//棋盘行数
#define LINE 8//棋盘列数
#define EMPTY -1//标记该位置未下棋子
#define BLACK 0//标记该位置所下棋子为黑色棋子
#define WHITE 1//标记该位置所下棋子为白色棋子
#define AVAILABLE 2//标记该位置为用户可以落子的位置
#include "pojo.h"
#include <QDebug>
#include <QDataStream>

class Position:public pojo
{
public:
    Position();//构造函数
    void calculateScores();//计算黑棋白棋总分
    void search(int x,int y,int color);//按照当前棋局信息为用户标记可下位置
    void moveChess(int color);//按照当前棋局信息为用户标记可下位置
    int Judge();//判断用户是否有能够落子位置
    void Turn_over_chess(int x,int y,int color);//根据用户所下棋子对满足翻转要求的敌方棋子进行翻转
    void Remove();//消去棋盘中多余的标记信息

public:
    friend QDataStream &operator<<(QDataStream & , const Position &);
    friend QDataStream &operator>>(QDataStream & , Position &);
};

#endif // POSITION_H
