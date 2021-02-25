#include "position.h"

Position::Position()
{
    end=false;
}

int Position::getChess(int x, int y) const
{
    return chessPos[x][y];
}

void Position::setChess(int x, int y, int chess)
{
    chessPos[x][y]=chess;
}

int Position::getBlackNum()
{
    return blackNum;
}

int Position::getWhiteNum()
{
    return whiteNum;
}

bool Position::getEnd()
{
    return end;
}

QDataStream & operator <<(QDataStream & output, const Position &obj)
{
    output<<obj.blackNum<<obj.whiteNum<<obj.end;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            output<<obj.getChess(i,j);
    return output;
}

QDataStream & operator>>(QDataStream & input, Position & obj)
{
    input>>obj.blackNum>>obj.whiteNum>>obj.end;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            int elem;
            input>>elem;
            obj.setChess(i,j,elem);
        }
    return input;
}

