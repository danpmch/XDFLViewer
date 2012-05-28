#ifndef RENDERABLEXDFLPATH_H
#define RENDERABLEXDFLPATH_H

#include "renderablexdflobject.h"

using namespace Eigen;

class RenderableXDFLPath : public RenderableXDFLObject
{

public:

    RenderableXDFLPath( QDomNode &path_node );
    ~RenderableXDFLPath();

    void glRender();

    void print_path();

private:

    void print_point( int index );
    Vector3f * convert_to_vector( QDomNode &point_node );

private:

    QList< Vector3f * > points;

};

#endif // RENDERABLEXDFLPATH_H
