#ifndef RENDERABLEXDFLOBJECT_H
#define RENDERABLEXDFLOBJECT_H

#include <QDomElement>
#include <qgl.h>
#include <Eigen/Core>

using namespace Eigen;

class RenderableXDFLObject
{
public:
    static QList< RenderableXDFLObject * > * convert_to_renderable_objects( QDomDocument &xdfl_file );
    virtual void glRender() = 0;
};

#endif // RENDERABLEXDFLOBJECT_H
