#include "board.h"
#include "ui_board.h"

Board::Board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//设置子窗口属性
    this->hide();

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++){
            QLabel *label=new QLabel(this);
            QString s="label";
            s+= QString("%1").arg(i);
            s+= QString("%1").arg(j);
            label->setObjectName(s);
            label->setText("");
            label->setGeometry(i*100,j*100,100,100);
        }

    position=new Position();
    flag=true;
}

Board::~Board()
{
    delete ui;
}

void Board::mousePressEvent(QMouseEvent *event){

    if(flag){
        qDebug()<<flag;
        posX=event->pos().x()/100;
        posY=event->pos().y()/100;
        QString s="label";
        s+= QString("%1").arg(posY);
        s+= QString("%1").arg(posY);
        QLabel *label = this->findChild<QLabel*>(s);


        if(position->getChess(posX,posY)==AVAILABLE){
            flag=false;
            qDebug()<<flag;
            QTime t;
            t.start();
            while(t.elapsed()<1000)
                QCoreApplication::processEvents();

            //向服务器传递点击的位置
            getData();
            //等待对方下棋（等待服务器再次更新
            flag=true;
        }
    }

}
void Board::getData(Position pos){
    position->updatePostion(pos);
}
