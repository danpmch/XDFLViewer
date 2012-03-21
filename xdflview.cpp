#include "xdflview.h"
#include <Eigen/Core>

XDFLView::XDFLView( QList< RenderableXDFLObject * > *objs, int width, int height, QGLWidget *parent )
  : QGLWidget( parent )
{
  assert( objs != NULL );
  objects = objs;

  Vector3f default_position( 0.0f, 0.0f, 5.0f );
  Vector3f default_up( 0.0f, 1.0f, 0.0f );
  Vector3f default_forward( 0.0f, 0.0f, -1.0f );
  camera = new Camera( default_position, default_up, default_forward, width, height );
}

void XDFLView::initializeGL()
{
  glShadeModel(GL_SMOOTH);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void XDFLView::resizeGL( int width, int height)
{
  if (height == 0) { //Prevent a divide-by-zero error
    height = 1;
  }

  glViewport(0, 0, (GLint)width, (GLint)height);
  camera->set_screen_size( width, height );
}

void XDFLView::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  foreach( RenderableXDFLObject *object, *objects )
  {
    object->glRender();
  }
}

