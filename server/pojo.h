#ifndef POJO_H
#define POJO_H


class pojo
{
public:
    int chessPos[8][8];//棋盘各位置信息矩阵
    int blackNum;//黑子总数
    int whiteNum;//白字总数
    bool end;//判定棋局是否结束
public:
    pojo();
    void setChess(int x,int y,int chess);//改变棋子状态
    void setBlackNum(int black);//改变黑棋总分
    void setWhiteNum(int white);//改变白棋总分
    int getChess(int x,int y) const;//获取某位置棋子状态
    int getBlackNum() const;//获取黑棋总分
    int getWhiteNum() const;//获取白棋总分
    bool getEnd();//获取棋局结束信息
    void setEnd(bool flag);//设置棋局结束信息
};

#endif // POJO_H
