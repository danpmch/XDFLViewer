#include "renderablexdflvoxel.h"
#include <iostream>
#include <cstdio>

RenderableXDFLVoxel::RenderableXDFLVoxel( QDomNode &voxel_node )
{
  assert( voxel_node.isElement() );
  assert( voxel_node.isElement() );
  QDomElement voxel_element = voxel_node.toElement();

  QDomNode x_node = voxel_element.elementsByTagName( "x" ).at( 0 );
  assert( x_node.isElement() );
  float x = x_node.toElement().text().toFloat();

  QDomNode y_node = voxel_element.elementsByTagName( "y" ).at( 0 );
  assert( y_node.isElement() );
  float y = y_node.toElement().text().toFloat();

  QDomNode z_node = voxel_element.elementsByTagName( "z" ).at( 0 );
  assert( z_node.isElement() );
  float z = z_node.toElement().text().toFloat();

  position = Vector3f( x, y, z );

  QDomNode volume_node = voxel_element.elementsByTagName( "volume" ).at( 0 );
  assert( volume_node.isElement() );
  volume = volume_node.toElement().text().toFloat();
}

void RenderableXDFLVoxel::glRender()
{
//  printf( "Drawing a voxel\n" );
  static const float RESOLUTION = 10;

  // TODO: figure out how to take a cube root
  float radius = volume / ( 4 / 3 );
  radius = sqrt( radius ) / 2;

  glPushMatrix();
    glColor3f( 1.0f, 0.0f, 0.0f );
    glTranslatef( position.x(), position.y(), position.z() );
    GLUquadric *sphere = gluNewQuadric();
    gluQuadricOrientation( sphere, GLU_OUTSIDE );
    gluQuadricNormals( sphere, GLU_SMOOTH );
    gluQuadricDrawStyle( sphere, GLU_FILL );
    gluSphere( sphere, radius, RESOLUTION, RESOLUTION );
    gluDeleteQuadric( sphere );
  glPopMatrix();

}
