#ifndef POSITION_H
#define POSITION_H

#define EMPTY -1
#define BLACK 0
#define WHITE 1
#define AVAILABLE 2

#include <QDataStream>

class Position
{
public:
    Position();
    //设置i，j位置的chess
    void setChess(int x,int y,int chess);
    //得到i，j位置的chess
    int getChess (int x,int y) const;
    //得到黑子的个数
    int getBlackNum();
    //得到end的值
    bool getEnd();
    //得到白子的个数
    int getWhiteNum();
public:
    //序列化函数
    friend QDataStream &operator<<(QDataStream & , const Position &);
    friend QDataStream &operator>>(QDataStream & , Position &);
private:
    //棋局
    int chessPos[8][8];
    //黑子的个数
    int blackNum;
    //白子的个数
    int whiteNum;
    //棋局是否结束
    bool end;
};

#endif // POSITION_H
