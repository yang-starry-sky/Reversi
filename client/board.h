#ifndef BOARD_H
#define BOARD_H

#include "position.h"
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QTime>
#include <QMouseEvent>

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);
    ~Board();

private:
    Ui::Board *ui;

    int posX;
    int posY;
    //是否可以响应鼠标点击事件
    bool flag;

    Position *position;
    //从主窗口获取数据
    void getData(Position pos);
protected:
    void mousePressEvent(QMouseEvent * event);
};

#endif // BOARD_H
