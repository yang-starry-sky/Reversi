#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->blackNumber->setDigitCount(2);
    ui->whiteNumber->setDigitCount(2);

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
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
    tcpClient = new QTcpSocket(this);   //实例化tcpClient
    tcpClient->abort();                 //取消原有连接
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), \
                this, SLOT(ReadError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    tcpClient->disconnectFromHost();
    if (tcpClient->state() == QAbstractSocket::UnconnectedState \
        || tcpClient->waitForDisconnected(1000))  //已断开连接则进入if
        {
           qDebug()<<"断开"<<endl;
         }
    delete ui;
}

void MainWindow::ReadData()
{
    QByteArray buffer = tcpClient->readAll();
    if(!buffer.isEmpty())
    {
        QDataStream in(&buffer,QIODevice::ReadOnly);
        in>>color;
        int judgeColor;
        in>>judgeColor;
        in>>*position;
        calculateNum();
        if(color!=judgeColor)
            setUnAvailable();
        updateBoard();
        if(position->getEnd())
        {
            QString s;
            if(blackNum>whiteNum)
            {
                s="黑方胜利！";
            }
            else if(blackNum<whiteNum)
            {
                s="白方胜利！";
            }
            else
                s="平局！";
            QMessageBox::information(0,"棋局结束",s,QMessageBox::Yes);
            tcpClient->disconnectFromHost();
            if (tcpClient->state() == QAbstractSocket::UnconnectedState \
                || tcpClient->waitForDisconnected(1000))  //已断开连接则进入if{}
                {
                   qDebug()<<"断开"<<endl;
                 }
            ui->conServer->setEnabled(true);
        }
    }
    qDebug()<<"read end";
}

void MainWindow::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because %1").arg(tcpClient->errorString()));
}

void MainWindow::sendMessage()
{
    //用于暂存要发送的数据
    QByteArray block;
    //使用数据流写入数据
    QDataStream out(&block,QIODevice::WriteOnly);

    out<<posX;
    out<<posY;
    tcpClient->write(block,block.size());

    block.resize(0);
}

void MainWindow::on_conServer_clicked()
{
    tcpClient->connectToHost(ui->ip->text(), ui->port->text().toInt());
    if (tcpClient->waitForConnected(1000))  // 连接成功则进入if
    {
        qDebug()<<"成功"<<endl;
        ui->conServer->setEnabled(false);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().x()<=800&&event->pos().y()<=800)
    {
        if(flag)
        {
            posX=event->pos().x()/100;
            posY=event->pos().y()/100;
            if(position->getChess(posX,posY)==2)
            {
                flag=false;
                QString s="label";
                s+= QString("%1").arg(posX);
                s+= QString("%1").arg(posY);
                QLabel *label = this->findChild<QLabel*>(s);
                if(color==0)
                    label->setStyleSheet("border-image: url(:/res/black);");
                else
                    label->setStyleSheet("border-image: url(:/res/white);");
                sendMessage();
            }
        }
    }
}

void MainWindow::updateBoard()
{
    ui->blackNumber->display(blackNum);
    ui->whiteNumber->display(whiteNum);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            QString s="label";
            s+= QString("%1").arg(i);
            s+= QString("%1").arg(j);
            QLabel *label = this->findChild<QLabel*>(s);
            switch(position->getChess(i,j))
            {
                case -1: label->setStyleSheet("");break;
                case 0: label->setStyleSheet("border-image: url(:/res/black);");break;
                case 1: label->setStyleSheet("border-image: url(:/res/white);");break;
                case 2: label->setStyleSheet("border-image: url(:/res/available);");break;
            }
        }
    }
    flag=true;
}

void MainWindow::setUnAvailable()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(position->getChess(i,j)==2)
                position->setChess(i,j,-1);
        }
}
void MainWindow::calculateNum()
{
    blackNum=0;
    whiteNum=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(position->getChess(i,j)==0)
                blackNum++;
            else if(position->getChess(i,j)==1)
                whiteNum++;
        }
}
