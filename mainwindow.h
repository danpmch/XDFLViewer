#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
#include <string>

#include "xdflview.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QString *xdfl_path = 0, QWidget *parent = 0 );
    ~MainWindow();

private:

    QDomDocument * load_document( QString *xdfl_path );
    QList< RenderableXDFLObject * > * convert_to_renderable_objects( QDomDocument xdfl_file );

private:
    Ui::MainWindow *ui;
    QList< RenderableXDFLObject * > *objects;
    XDFLView *view;
};

#endif // MAINWINDOW_H
