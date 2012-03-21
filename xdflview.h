#ifndef XDFLVIEW_H
#define XDFLVIEW_H

#include <QGLWidget>
#include "renderablexdflobject.h"
#include "camera.h"

class XDFLView : public QGLWidget
{
  Q_OBJECT
public:
    XDFLView( QList< RenderableXDFLObject * > *objs, int width, int height, QGLWidget *parent = 0 );

protected:
  void initializeGL();
  void resizeGL( int width, int height);
  void paintGL();

private:
    Camera *camera;
    QList< RenderableXDFLObject * > *objects;
};

#endif // XDFLVIEW_H
