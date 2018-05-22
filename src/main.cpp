#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QDebug>
#include "../include/io.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;
    IO w;
    w.show();

    return a.exec();
}
