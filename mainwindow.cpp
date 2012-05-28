#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderablexdflobject.h"

#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <cstdio>

MainWindow::MainWindow( QString *xdfl_path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    view( NULL )
{
  ui->setupUi(this);
  view = new XDFLView( NULL, ui->graphicsView );
  init_view( xdfl_path );
}

void MainWindow::init_view( QString *xdfl_path )
{
  QDomDocument *xdfl_file = load_document( xdfl_path );
  QList< RenderableXDFLObject * > *objects = RenderableXDFLObject::convert_to_renderable_objects( xdfl_file );

  view->set_objects( objects );

  delete xdfl_file;
}

QDomDocument * MainWindow::load_document( QString *xdfl_path )
{
  if( xdfl_path == NULL ) return NULL;

  QFile file( *xdfl_path );
  if( !file.open( QIODevice::ReadOnly ) )
  {
    printf( "Could not open file\n" );
    return NULL;
  }

  QDomDocument *doc = new QDomDocument( "xdfl" );

  if( !doc->setContent( &file ) )
  {
    printf( "Could not set document contents\n" );
    delete doc;
    doc = NULL;
  }

  file.close();
  return doc;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  view->resize(ui->graphicsView->size());
  view->repaint();
}

void MainWindow::keyPressEvent( QKeyEvent *event )
{
  view->keyPressEvent( event );
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
  view->mouseMoveEvent( event );
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
  view->mousePressEvent( event );
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
  view->mouseReleaseEvent( event );
}

void MainWindow::on_actionOpen_triggered()
{
  QString file_name = QFileDialog::getOpenFileName( this, tr( "Open XDFL" ), QDir::currentPath(), tr( "XDFL (*.xdfl)" ) );
  if( !file_name.isNull() )
  {
    init_view( &file_name );
  }
}

void MainWindow::on_actionExit_triggered()
{
  exit( 0 );
}
