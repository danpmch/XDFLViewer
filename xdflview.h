#ifndef XDFLVIEW_H
#define XDFLVIEW_H

#include <QGLWidget>
#include <QTimer>
#include "renderablexdflobject.h"
#include "camera.h"

class XDFLView : public QGLWidget
{

  Q_OBJECT

public:

  XDFLView( QList< RenderableXDFLObject * > *objs, QWidget *parent = 0 );

  void set_objects( QList< RenderableXDFLObject * > *objs );

  void keyPressEvent(QKeyEvent* event);

  void mouseMoveEvent(QMouseEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);

protected:

  void initializeGL();
  void resizeGL( int width, int height);
  void paintGL();

private:

  int last_mouse_x, last_mouse_y;

  Camera *camera;
  QList< RenderableXDFLObject * > *objects;
  QTimer repaint_timer;
};

#endif // XDFLVIEW_H
