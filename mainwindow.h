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

    void keyPressEvent( QKeyEvent *event );

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:

    void init_view( QString *xdfl_path );
    void resizeEvent(QResizeEvent* event);

    QDomDocument * load_document( QString *xdfl_path );
    QList< RenderableXDFLObject * > * convert_to_renderable_objects( QDomDocument xdfl_file );

private slots:

  void on_actionOpen_triggered();
  void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    XDFLView *view;
};

#endif // MAINWINDOW_H
