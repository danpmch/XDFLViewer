#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderablexdflobject.h"
#include <QFile>
#include <cstdio>

MainWindow::MainWindow( QString *xdfl_path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDomDocument *xdfl_file;
    if( xdfl_path != NULL )
    {
      xdfl_file = load_document( xdfl_path );
      if( xdfl_file != NULL )
        objects = RenderableXDFLObject::convert_to_renderable_objects( *xdfl_file );
      else
        objects = NULL;
    }
    else
      objects = NULL;

    if( objects != NULL )
    {
      view = new XDFLView( objects, 680, 400 );
    }
}

QDomDocument * MainWindow::load_document( QString *xdfl_path )
{
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
