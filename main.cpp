#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString xdfl( "/home/black_adder/fabAhome/solder prefab.xdfl" );
    MainWindow w( &xdfl );
    w.show();

    return a.exec();
}
