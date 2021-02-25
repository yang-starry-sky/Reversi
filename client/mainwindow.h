#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <qhostinfo.h>
#include <QDataStream>
#include <QtNetwork>
#include "position.h"
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QMouseEvent>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //
    QTcpSocket *tcpClient;
    void sendMessage();
private slots:
    //获取服务器传过来的棋局
    void ReadData();
    //连接错误处理
    void ReadError(QAbstractSocket::SocketError);
    //当点击连接按钮时
    void on_conServer_clicked();
private:
    //黑子和白子的数量
    int blackNum;
    int whiteNum;
    //鼠标位置
    int posX;
    int posY;
    //是否可以响应鼠标点击事件
    bool flag;
    //标识本客户端是黑方还是白方
    int color;
    //存储现有棋局
    Position *position;

    //更新棋盘上的棋子
    void updateBoard();
    //消去可下子的位置
    void setUnAvailable();
    //计算黑白棋的数目
    void calculateNum();
protected:
    //重写鼠标点击事件
    void mousePressEvent(QMouseEvent * event);



};

#endif // MAINWINDOW_H
