#include "renderablexdflobject.h"
#include "renderablexdflpath.h"
#include "renderablexdflvoxel.h"
#include <cstdio>

QList< RenderableXDFLObject * > * RenderableXDFLObject::convert_to_renderable_objects( QDomDocument &xdfl_file )
{
  QList< RenderableXDFLObject * > *objects = new QList< RenderableXDFLObject * >();

  // get all paths
  printf( "Making renderable paths\n" );
  QDomNodeList path_nodes = xdfl_file.elementsByTagName( "path" );
  for( uint i = 0; i < path_nodes.length(); i++ )
  {
    QDomNode path_node = path_nodes.at( i );
    objects->append( new RenderableXDFLPath( path_node ) );
  }

  // get all voxels
  printf( "Making renderable voxels\n" );
  QDomNodeList voxel_nodes = xdfl_file.elementsByTagName( "voxel" );
  for( uint i = 0; i < voxel_nodes.length(); i++ )
  {
    printf( "voxel %d", i );
    QDomNode voxel_node = voxel_nodes.at( i );
    objects->append( new RenderableXDFLVoxel( voxel_node ) );
    printf( "\n" );
  }

  return objects;
}
