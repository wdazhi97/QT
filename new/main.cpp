#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);//无边框
    w.show();
    w.showFullScreen();
    return a.exec();
}
