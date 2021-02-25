#include "pojo.h"

pojo::pojo()
{

}

void pojo::setEnd(bool flag){
    end=flag;
}
bool pojo::getEnd(){
    return end;
}

int pojo::getChess(int x, int y) const{
    return chessPos[x][y];
}

void pojo::setChess(int x, int y, int chess){
    chessPos[x][y]=chess;
}

void pojo::setBlackNum(int black){
    blackNum=black;
}

void pojo::setWhiteNum(int white){
    whiteNum=white;
}

int pojo::getBlackNum()const{
    return blackNum;
}
int pojo::getWhiteNum()const{
    return whiteNum;
}
