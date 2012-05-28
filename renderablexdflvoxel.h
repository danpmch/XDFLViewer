#ifndef RENDERABLEXDFLVOXEL_H
#define RENDERABLEXDFLVOXEL_H

#include "renderablexdflobject.h"

class RenderableXDFLVoxel : public RenderableXDFLObject
{

public:

    RenderableXDFLVoxel( QDomNode &voxel_node );
    void glRender();

private:

    Vector3f position;
    float volume;
    float radius;

};

#endif // RENDERABLEXDFLVOXEL_H
