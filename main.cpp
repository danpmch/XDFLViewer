#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString *xdfl = NULL;
    if( argc == 2 )
      xdfl = new QString( argv[ 1 ] );

    MainWindow w( xdfl );
    w.show();

    return a.exec();
}
