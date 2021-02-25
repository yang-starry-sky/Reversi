#include "position.h"
#include<stdio.h>
#include <QDebug>
Position::Position()
{
    int i,j;
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<LINE;j++)
        {
            setChess(i,j,EMPTY);
        }
    }
    setChess(ROW/2,LINE/2,WHITE);
    setChess(ROW/2-1,LINE/2-1,WHITE);
    setChess(ROW/2,LINE/2-1,BLACK);
    setChess(ROW/2-1,LINE/2,BLACK);
    setBlackNum(2);
    setWhiteNum(2);
    end=false;
}

void Position::calculateScores()
{
    int i,j,black=0,white=0;
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<LINE;j++)
        {
            if(getChess(i,j)==BLACK)
            {
                black++;
            }
            else if(getChess(i,j)==WHITE)
            {
                white++;
            }
        }
    }
    setBlackNum(black);
    setWhiteNum(white);
}
void Position::search(int x,int y,int color)
{
    int i,j;
    if(color==0)
    {
        for(i=x,j=y+1;getChess(i,j)==WHITE&&j<LINE-1;)
        {
            j++;
            if(getChess(i,j)==BLACK||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x,j=y-1;getChess(i,j)==WHITE&&j>0;)
        {
            j--;
            if(getChess(i,j)==BLACK||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x+1,j=y;getChess(i,j)==WHITE&&i<ROW-1;)
        {
            i++;
            if(getChess(i,j)==BLACK||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x-1,j=y;getChess(i,j)==WHITE&&i>0;)
        {
            i--;
            if(getChess(i,j)==BLACK||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x+1,j=y+1;getChess(i,j)==WHITE&&j<LINE-1&&i<ROW-1;)
        {
            j++;
            i++;
            if(getChess(i,j)==BLACK||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x-1,j=y-1;getChess(i,j)==WHITE&&j>0&&i>0;)
        {
            j--;
            i--;
            if(getChess(i,j)==BLACK||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x+1,j=y-1;getChess(i,j)==WHITE&&j>0&&i<ROW-1;)
        {
            j--;
            i++;
            if(getChess(i,j)==BLACK||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x-1,j=y+1;getChess(i,j)==WHITE&&j<LINE-1&&i>0;)
        {
            j++;
            i--;
            if(getChess(i,j)==BLACK||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
    }
    else if(color==1)
    {
        for(i=x,j=y+1;getChess(i,j)==BLACK&&j<LINE-1;)
        {
            j++;
            if(getChess(i,j)==WHITE||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x,j=y-1;getChess(i,j)==BLACK&&j>0;)
        {
            j--;
            if(getChess(i,j)==WHITE||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x+1,j=y;getChess(i,j)==BLACK&&i<ROW-1;)
        {
            i++;
            if(getChess(i,j)==WHITE||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x-1,j=y;getChess(i,j)==BLACK&&i>0;)
        {
            i--;
            if(getChess(i,j)==WHITE||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x+1,j=y+1;getChess(i,j)==BLACK&&j<LINE-1&&i<ROW-1;)
        {
            j++;
            i++;
            if(getChess(i,j)==WHITE||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x-1,j=y-1;getChess(i,j)==BLACK&&j>0&&i>0;)
        {
            j--;
            i--;
            if(getChess(i,j)==WHITE||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x+1,j=y-1;getChess(i,j)==BLACK&&j>0&&i<ROW-1;)
        {
            j--;
            i++;
            if(getChess(i,j)==WHITE||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
        for(i=x-1,j=y+1;getChess(i,j)==BLACK&&j<LINE-1&&i>0;)
        {
            j++;
            i--;
            if(getChess(i,j)==WHITE||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==EMPTY)
            {
                setChess(i,j,AVAILABLE);
                break;
            }
        }
    }
    else
    {
        qDebug("some error happened.....");
    }
}

void Position::moveChess(int color)
{
    int i,j;
    if(color==0)
    {
        for(i=0;i<ROW;i++)
        {
            for(j=0;j<LINE;j++)
            {
                if(getChess(i,j)==BLACK)
                {
                    search(i,j,0);
                }
            }
        }
    }
    else if(color==1)
    {
        for(i=0;i<ROW;i++)
        {
            for(j=0;j<LINE;j++)
            {
                if(getChess(i,j)==WHITE)
                {
                    search(i,j,1);
                }
            }
        }
    }
    else
    {
        qDebug("some error happened.....\n");
    }
}
void Position::Turn_over_chess(int x,int y,int color)
{
    int i,j,m,n;
    if(color==0)
    {
        setChess(x,y,BLACK);
        for(i=x,j=y+1;getChess(i,j)==WHITE&&j<LINE-1;)
        {
            j++;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==BLACK)
            {
                for(m=x,n=y+1;n<j;n++)
                setChess(m,n,BLACK);
                break;
            }
        }
        for(i=x,j=y-1;getChess(i,j)==WHITE&&j>0;)
        {
            j--;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==BLACK)
            {
                for(m=x,n=y-1;n>j;n--)
                setChess(m,n,BLACK);
                break;
            }
        }
        for(i=x+1,j=y;getChess(i,j)==WHITE&&i<ROW-1;)
        {
            i++;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==BLACK)
            {
                for(m=x+1,n=y;m<i;m++)
                setChess(m,n,BLACK);
                break;
            }
        }
        for(i=x-1,j=y;getChess(i,j)==WHITE&&i>0;)
        {
            i--;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==BLACK)
            {
                for(m=x-1,n=y;m>i;m--)
                setChess(m,n,BLACK);
                break;
            }
        }
        for(i=x+1,j=y+1;getChess(i,j)==WHITE&&i<ROW-1&&j<LINE-1;)
        {
            i++;
            j++;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==BLACK)
            {
                for(m=x+1,n=y+1;m<i&&n<j;m++,n++)
                setChess(m,n,BLACK);
                break;
            }
        }
        for(i=x-1,j=y-1;getChess(i,j)==WHITE&&i>0&&j>0;)
        {
            i--;
            j--;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==BLACK)
            {
                for(m=x-1,n=y-1;m>i&&n>j;m--,n--)
                setChess(m,n,BLACK);
                break;
            }
        }
        for(i=x+1,j=y-1;getChess(i,j)==WHITE&&i<ROW-1&&j>0;)
        {
            i++;
            j--;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==BLACK)
            {
                for(m=x+1,n=y-1;m<i&&n>j;m++,n--)
                setChess(m,n,BLACK);
                break;
            }
        }
        for(i=x-1,j=y+1;getChess(i,j)==WHITE&&i>0&&j<LINE-1;)
        {
            i--;
            j++;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==BLACK)
            {
                for(m=x-1,n=y+1;m>i&&n<j;m--,n++)
                setChess(m,n,BLACK);
                break;
            }
        }
    }
    else if(color==1)
    {
        setChess(x,y,WHITE);
        for(i=x,j=y+1;getChess(i,j)==BLACK&&j<LINE-1;)
        {
            j++;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==WHITE)
            {
                for(m=x,n=y+1;n<j;n++)
                setChess(m,n,WHITE);
                break;
            }
        }
        for(i=x,j=y-1;getChess(i,j)==BLACK&&j>0;)
        {
            j--;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==WHITE)
            {
                for(m=x,n=y-1;n>j;n--)
                setChess(m,n,WHITE);
                break;
            }
        }
        for(i=x+1,j=y;getChess(i,j)==BLACK&&i<ROW-1;)
        {
            i++;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==WHITE)
            {
                for(m=x+1,n=y;m<i;m++)
                setChess(m,n,WHITE);
                break;
            }
        }
        for(i=x-1,j=y;getChess(i,j)==BLACK&&i>0;)
        {
            i--;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==WHITE)
            {
                for(m=x-1,n=y;m>i;m--)
                setChess(m,n,WHITE);
                break;
            }
        }
        for(i=x+1,j=y+1;getChess(i,j)==BLACK&&i<ROW-1&&j<LINE-1;)
        {
            i++;
            j++;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==WHITE)
            {
                for(m=x+1,n=y+1;m<i&&n<j;m++,n++)
                setChess(m,n,WHITE);
                break;
            }
        }
        for(i=x-1,j=y-1;getChess(i,j)==BLACK&&i>0&&j>0;)
        {
            i--;
            j--;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==WHITE)
            {
                for(m=x-1,n=y-1;m>i&&n>j;m--,n--)
                setChess(m,n,WHITE);
                break;
            }
        }
        for(i=x+1,j=y-1;getChess(i,j)==BLACK&&i<ROW-1&&j>0;)
        {
            i++;
            j--;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==WHITE)
            {
                for(m=x+1,n=y-1;m<i&&n>j;m++,n--)
                setChess(m,n,WHITE);
                break;
            }
        }
        for(i=x-1,j=y+1;getChess(i,j)==BLACK&&i>0&&j<LINE-1;)
        {
            i--;
            j++;
            if(getChess(i,j)==EMPTY||getChess(i,j)==AVAILABLE)
            break;
            else if(getChess(i,j)==WHITE)
            {
                for(m=x-1,n=y+1;m>i&&n<j;m--,n++)
                setChess(m,n,WHITE);
                break;
            }
        }
    }
    else
    {
        qDebug("some error happened...\n");
    }
    calculateScores();
}
void Position::Remove()
{
    int i,j;
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<LINE;j++)
        {
            if(getChess(i,j)==AVAILABLE)
            {
                setChess(i,j,EMPTY);;
            }
        }
    }
}
int Position::Judge()
{
    int i,j;
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<LINE;j++)
        {
            if(getChess(i,j)==AVAILABLE)
            {
                return 1;
            }
        }
    }
    return 0;
}
QDataStream & operator <<(QDataStream & output, const Position &obj){
    output<<obj.blackNum<<obj.whiteNum<<obj.end;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            output<<obj.getChess(i,j);
    return output;
}

QDataStream & operator>>(QDataStream & input, Position & obj){
    input>>obj.blackNum>>obj.whiteNum>>obj.end;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++){
            int elem;
            input>>elem;
            obj.setChess(i,j,elem);
        }
    return input;
}
