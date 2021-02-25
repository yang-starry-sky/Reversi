#include "mainwindow.h"
#include <QApplication>
#include "gamethread.h"

#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMutex>
#include <QString>
#include <qapplication.h>

// 自定义消息处理程序
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();

    QString strMessage = QString("%1")
            .arg(localMsg.constData());
    // 输出信息至文件中
    QFile file("log.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    MainWindow w;

    qInstallMessageHandler(myMessageOutput);
    return a.exec();
}
