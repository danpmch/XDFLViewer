#include "renderablexdflpath.h"

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

  glBegin( GL_LINES );

    glColor3f( 1.0f, 0.0f, 0.0f );

    foreach( Vector3f *point, points )
    {
      glVertex3f( point->x(), point->y(), point->z() );
    }

  glEnd();

}
