#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    mysql=new MySql();
    tcpServer = new QTcpServer(this);
    bool ok = tcpServer->listen(QHostAddress::Any, 8080);
    if(ok)
    {
        qDebug()<<"server port:8080"<<endl;
    }
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));

    thread1=new GameThread();
    thread2=new GameThread();
    threadA=new QThread();
    threadB=new QThread();//对新建线程构建实体,从而进行connect连接
    connect(this,SIGNAL(sendLocation(int ,int ,int ,int )),thread1,SLOT(getLocation(int ,int ,int ,int )));//将主线程发送用户落子信息的信号与子线程thread1收到落子信息后完成的相应操作的槽进行绑定
    connect(this,SIGNAL(sendLocation(int ,int ,int ,int )),thread2,SLOT(getLocation(int ,int ,int ,int )));//将主线程发送用户落子信息的信号与子线程thread2收到落子信息后完成的相应操作的槽进行绑定
    connect(thread1,SIGNAL(sendBlackPosition(int ,Position *,int)),this,SLOT(getBlackPosition(int ,Position *,int)));//将子线程thread1给黑棋用户发送棋局的信号量与主线程获取黑棋用户的棋局的槽进行绑定
    connect(thread1,SIGNAL(sendWhitePosition(int ,Position *,int)),this,SLOT(getWhitePosition(int ,Position *,int)));//将子线程thread1给白棋用户发送棋局的信号量与主线程获取黑棋用户的棋局的槽进行绑定
    connect(thread2,SIGNAL(sendBlackPosition(int ,Position *,int)),this,SLOT(getBlackPosition(int ,Position *,int)));//将子线程thread2给黑棋用户发送棋局的信号量与主线程获取黑棋用户的棋局的槽进行绑定
    connect(thread2,SIGNAL(sendWhitePosition(int ,Position *,int)),this,SLOT(getWhitePosition(int ,Position *,int)));//将子线程thread2给白棋用户发送棋局的信号量与主线程获取黑棋用户的棋局的槽进行绑定
    connect(thread1,SIGNAL(stopThread()),threadA,SLOT(terminate()));//将子线程thread1结束线程的信号量与threadA的terminate()进行绑定
    connect(thread2,SIGNAL(stopThread()),threadB,SLOT(terminate()));//将子线程thread2结束线程的信号量与threadB的terminate()进行绑定
    connect(thread1,SIGNAL(sendStopID(int)),this,SLOT(getStopID(int)));//将子线程thread1结束后发送结束线程id的信号量与主线程获取结束线程id的槽绑定
    connect(thread2,SIGNAL(sendStopID(int)),this,SLOT(getStopID(int)));//将子线程thread2结束后发送结束线程id的信号量与主线程获取结束线程id的槽绑定
    connect(this,SIGNAL(startinit1()),thread1,SLOT(init()));//将主线程开辟新线程的初始化信号量与子线程thread1完成的初始化操作槽绑定
    connect(this,SIGNAL(startinit2()),thread2,SLOT(init()));//将主线程开辟新线程的初始化信号量与子线程thread2完成的初始化操作槽绑定
    connect(thread1,SIGNAL(sendID(int)),this,SLOT(getID(int)));//将子线程thread1发送开启新线程的线程id的信号量与主线程获取新线程的线程id的槽绑定
    connect(thread2,SIGNAL(sendID(int)),this,SLOT(getID(int)));//将子线程thread2发送开启新线程的线程id的信号量与主线程获取新线程的线程id的槽绑定
    thread1->moveToThread(threadA);//将thread1中的函数执行操作放入Qthread类的实体ThreadA中
    thread2->moveToThread(threadB);//将thread2中的函数执行操作放入Qthread类的实体ThreadB中
}

MainWindow::~MainWindow()
{
    for(int i=0; i<tcpClient.length(); i++)//断开所有连接
    {
        tcpClient[i]->disconnectFromHost();
        bool ok = tcpClient[i]->waitForDisconnected(1000);
        if(!ok)
        {
            qDebug()<<"there is somthing wrong";// 处理异常
        }
        tcpClient.removeAt(i);  //从保存的客户端列表中取去除
    }
    tcpServer->close();     //不再监听端口
    qDebug()<<"server end"<<endl;
}

void MainWindow::getID(int id)
{
    Thread_id=id;
    qDebug()<<Thread_id;
    //获得新线程的id
    QString sql;
    sql="update client_thread set thread_id=";
    sql+=QString::number(Thread_id);
    sql+=" where enable=1";
    qDebug()<<sql;
    mysql->updateClient(sql);
    sql="update client_thread set enable=0 ";
    qDebug()<<sql;
    mysql->updateClient(sql);
    sql="insert into client_thread values('";
    sql+=currentClient->peerAddress().toString().split("::ffff:")[1];
    sql+="',";
    int x=currentClient->peerPort();
    sql+=QString::number(x);;
    sql+=",";
    sql+="1";//white
    sql+=",";
    sql+="0";//unenable
    sql+=",";
    sql+=QString::number(Thread_id);
    sql+=")";
    qDebug()<<sql;
    mysql->insertClient(sql);
}
int MainWindow::getThread_id()
{
    return Thread_id;
}

void MainWindow::NewConnectionSlot()
{
    qDebug()<<"connect"<<endl;
    currentClient = tcpServer->nextPendingConnection();
    tcpClient.append(currentClient);

    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));

    QSqlQuery query;
    QString sql;
    sql="select count(*) from client_thread where enable=1";
    qDebug()<<sql;
    query=mysql->selectClient(sql);
    int count;
    while(query.next()){
        count = query.value(0).toInt();
    }
    //没有棋局
    if(count==0){
        sql="insert into client_thread values('";
        sql+=currentClient->peerAddress().toString().split("::ffff:")[1];
        sql+="',";
        int x=currentClient->peerPort();
        sql+=QString::number(x);;
        sql+=",";
        sql+="0";//black
        sql+=",";
        sql+="1";//enable
        sql+=",null)";
        qDebug()<<sql;
        mysql->insertClient(sql);
    }
    else{
        sql="select count(*) from client_thread where enable=0";
        qDebug()<<sql;
        query=mysql->selectClient(sql);
        while(query.next()){
            count = query.value(0).toInt();
        }
        if(count==0){
            threadA->start();
            emit startinit1();
        }
        else{
            if(threadA->isRunning()){
                threadB->start();
                emit startinit2();
            }
            else{
                threadA->start();
                emit startinit1();
            }

        }
    }
}

void MainWindow::disconnectedSlot(){
    //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
             mysql->emptyClient();
             // 删除存储在tcpClient列表中的客户端信息
             tcpClient[i]->destroyed();
             tcpClient.removeAt(i);
        }
      }
}

void MainWindow::ReadData(){

        // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
        for(int i=0; i<tcpClient.length(); i++)
        {
            QByteArray buffer = tcpClient[i]->readAll();
            if(buffer.isEmpty())    continue;
            QDataStream in(&buffer,QIODevice::ReadOnly);
            int x,y;
            in>>x;in>>y;
            qDebug()<<"receive position(x,y):"<<x<<y<<endl;
            QSqlQuery query;
            QString sql="select thread_id,color from client_thread where ip='";
            sql+=tcpClient[i]->peerAddress().toString().split("::ffff:")[1];
            sql+="' and port=";
            int port=tcpClient[i]->peerPort();
            sql+=QString::number(port);
            qDebug()<<sql;
            query=mysql->selectClient(sql);
            int thread_id;
            int color;
            while(query.next()){
                thread_id=query.value(0).toInt();
                color=query.value(1).toInt();
            }
            emit sendLocation(thread_id,x,y,color);
        }
}
void MainWindow::getBlackPosition(int id,Position *pos,int judgeColor){
    QSqlQuery query;
    QString sql="select ip,port from client_thread where thread_id=";
    sql+=QString::number(id);
    sql+=" and color=0";
    qDebug()<<sql;
    query=mysql->selectClient(sql);
    QString ip;
    int port;
    while(query.next()){
        ip=query.value(0).toString();
        port=query.value(1).toInt();
    }
        for(int i=0; i<tcpClient.length(); i++){
            if(ip==tcpClient[i]->peerAddress().toString().split("::ffff:")[1] && port==tcpClient[i]->peerPort()){
                sendData(tcpClient[i],pos,0,judgeColor);
            }
        }

}
void MainWindow::getWhitePosition(int id,Position *pos,int judgeColor){

    QSqlQuery query;
    QString sql="select ip,port from client_thread where thread_id=";
    sql+=QString::number(id);
    sql+=" and color=1";
    qDebug()<<sql;
    query=mysql->selectClient(sql);
    QString ip;
    int port;
    while(query.next()){
        ip=query.value(0).toString();
        port=query.value(1).toInt();
    }
        for(int i=0; i<tcpClient.length(); i++){
            if(ip==tcpClient[i]->peerAddress().toString().split("::ffff:")[1] && port==tcpClient[i]->peerPort()){
                sendData(tcpClient[i],pos,1,judgeColor);
            }
        }

}
void MainWindow::sendData(QTcpSocket* client,Position *pos,int color,int judgeColor){
    QByteArray block;
    //使用数据流写入数据
    QDataStream out(&block,QIODevice::WriteOnly);
    out<<color;
    out<<judgeColor;
    out<<*pos;
    client->write(block,block.size());
    block.resize(0);
}

void MainWindow::getStopID(int id){
    QString sql="delete from client_thread where thread_id=";
    sql+=QString::number(id);
    mysql->deleteClient(sql);
    qDebug()<<sql;
}
