#include "renderablexdflpath.h"

#include <cstdio>

RenderableXDFLPath::RenderableXDFLPath( QDomNode &path_node )
{
  assert( path_node.isElement() );
  QDomElement path_element = path_node.toElement();
  QDomNodeList point_doms = path_element.elementsByTagName( "point" );

  for( uint i = 0; i < point_doms.length(); i++ )
  {
    QDomNode point_dom = point_doms.at( i );
    points.append( convert_to_vector( point_dom ) );
  }

  //print_path();
}

RenderableXDFLPath::~RenderableXDFLPath()
{
  foreach( Vector3f *v, points )
  {
    delete v;
  }
}

void RenderableXDFLPath::print_path()
{
  printf( "Path: [ " );

  for( int i = 0; i < points.length(); i++ )
  {
    print_point( i );
  }

  printf( "]\n" );
}

void RenderableXDFLPath::print_point( int index )
{
  Vector3f *point = points[ index ];
  printf( "( %f, %f, %f );\n", point->x(), point->y(), point->z() );
}

Vector3f * RenderableXDFLPath::convert_to_vector( QDomNode &point_node )
{
  assert( point_node.isElement() );
  QDomElement point_element = point_node.toElement();

  QDomNode x_node = point_element.elementsByTagName( "x" ).at( 0 );
  float x = x_node.toElement().text().toFloat();

  QDomNode y_node = point_element.elementsByTagName( "y" ).at( 0 );
  float y = y_node.toElement().text().toFloat();

  QDomNode z_node = point_element.elementsByTagName( "z" ).at( 0 );
  float z = z_node.toElement().text().toFloat();

  return new Vector3f( x, y, z );
}

void RenderableXDFLPath::glRender()
{

  glBegin( GL_LINE_STRIP );

    glColor3f( 1.0f, 0.0f, 0.0f );

    foreach( Vector3f *point, points )
    {
      glVertex3f( point->x(), point->y(), point->z() );
    }

  glEnd();

}
