#include "xdflview.h"

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <QKeyEvent>

#include <cstdio>
#include <cmath>

static const int REPAINT_DELAY = 1000/60;

XDFLView::XDFLView( QList< RenderableXDFLObject * > *objs, QWidget *parent )
  : QGLWidget( parent ), last_mouse_x( -1 ), last_mouse_y( -1 ), objects( NULL )
{
  setContext( new QGLContext( QGLFormat(), this ) );

  objects = objs;

  Vector3f default_position( 0.0f, 0.0f, 50.0f );
  Vector3f default_up( 0.0f, 1.0f, 0.0f );
  Vector3f default_forward( 0.0f, 0.0f, -1.0f );
  QSize dimensions = parent->size();
  camera = new Camera( default_position, default_up, default_forward, dimensions.width(), dimensions.height() );
}

void XDFLView::set_objects( QList< RenderableXDFLObject * > *objs )
{
  objects = objs;
  repaint();
}

void XDFLView::initializeGL()
{
  glShadeModel(GL_SMOOTH);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void XDFLView::resizeGL( int width, int height)
{
  printf( "resizeGL called: ( %d, %d )\n", width, height );
  //Prevent a divide-by-zero error
  if (height == 0) {
    height = 1;
  }

  glViewport(0, 0, (GLint)width, (GLint)height);
  camera->set_screen_size( width, height );
}

void XDFLView::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  camera->gl_set_camera();

  const float RESOLUTION = 10;
  // mark the origin, for debug purposes
  glPushMatrix();
    glColor3f( 0.0f, 0.0f, 1.0f );
    GLUquadric *sphere = gluNewQuadric();
    gluQuadricOrientation( sphere, GLU_OUTSIDE );
    gluQuadricNormals( sphere, GLU_SMOOTH );
    gluQuadricDrawStyle( sphere, GLU_FILL );
    gluSphere( sphere, 1.0f, RESOLUTION, RESOLUTION );
    gluDeleteQuadric( sphere );
  glPopMatrix();

  if( objects == NULL )
  {
    // render is complete if there are no objects
    return;
  }

  foreach( RenderableXDFLObject *object, *objects )
  {
    object->glRender();
  }

  int glerror = glGetError();
  if( glerror != GL_NO_ERROR )
  {
    printf( "%s\n", gluErrorString( glerror ) );
    exit( 1 );
  }

  glFinish();
}

void XDFLView::keyPressEvent(QKeyEvent* event)
{
  bool shift = event->modifiers().testFlag(Qt::ShiftModifier);
  switch( event->key() )
  {
    case Qt::Key_H:
    case Qt::Key_Left:
      camera->move_left();
      break;

    case Qt::Key_L:
    case Qt::Key_Right:
      camera->move_right();
      break;

    case Qt::Key_K:
      if( shift )
      {
        camera->move_up();
        break;
      }
    case Qt::Key_Up:
      camera->move_forward();
      break;

    case Qt::Key_J:
      if( shift )
      {
        camera->move_down();
        break;
      }
    case Qt::Key_Down:
      camera->move_backward();
      break;

    case Qt::Key_PageUp:
      camera->move_up();
      break;

    case Qt::Key_PageDown:
      camera->move_down();
      break;

    case Qt::Key_unknown:
      puts( "Error: unknown key, ignoring" );
      break;

    default:
      break;
  }

  repaint();
}

void XDFLView::mouseMoveEvent(QMouseEvent* event)
{
  if( last_mouse_x == -1 ) return;

  int dx = ( event->x() - last_mouse_x );
  int dy = ( event->y() - last_mouse_y );

  camera->rotate( dx, dy );

  last_mouse_x = event->x();
  last_mouse_y = event->y();
  repaint();
}

void XDFLView::mousePressEvent(QMouseEvent* event)
{
  last_mouse_x = event->x();
  last_mouse_y = event->y();
}

void XDFLView::mouseReleaseEvent(QMouseEvent* event)
{
  last_mouse_x = last_mouse_y = -1;
}

void XDFLView::reset()
{
  camera->reset();
  repaint();
}
