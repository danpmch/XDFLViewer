#include "camera.h"
#include <qgl.h>
#include <cstdio>
#include <iostream>

Camera::Camera( Vector3f &position, Vector3f &up, Vector3f &forward,
                int width, int height, float fov, float znear,
                float zfar )
{
  this->position = original_position = position;

  this->up = original_up = up;
  original_up.normalize();
  this->up.normalize();

  this->forward = original_forward = forward;
  original_forward.normalize();
  this->forward.normalize();

  this->width = width;
  this->height = height == 0? 1 : height;
  aspect = float( width ) / float( height );

  this->fov = fov;
  this->znear = znear;
  this->zfar = zfar;
  this->zoom = 1.0;
}

Matrix4f * Camera::get_viewMatrix()
{
  exit( 1 );
  return NULL;
}

Matrix4f * Camera::get_projectionMatrix()
{
  exit( 1 );
  return NULL;
}

void Camera::modify_view_matrix( Transform< float, 3, Affine > &t )
{
  viewMatrix = t * viewMatrix;
}

void Camera::rotate( int dx, int dy )
{
  float dx_rad = ( float( dx ) / width * fov ) * ( 3.14159265 / 180.0f );
  float dy_rad = ( float( dy ) / width * fov ) * ( 3.14159265 / 180.0f );

  Vector3f right = up.cross( forward );
  Vector3f true_up = right.cross( forward );
  up = AngleAxisf( dx_rad, true_up ) * AngleAxisf( dy_rad, right ) * up;
  forward = AngleAxisf( dx_rad, true_up ) * AngleAxisf( dy_rad, right  )* forward;
}

void Camera::update_matrices()
{
  /*
   * All following code was adapted from the Cornell CS5625 framework's Camera class
   */

  /**
   * Generate a perspective projection matrix for OpenGL
   * (See: http://www.opengl.org/documentation/specs/man_pages/hardcopy/GL/html/glu/perspective.html)
   * Avoid setting near too close to 0 or much Z-buffer precision will be lost!
   */

  const float PI = 3.1415926535897932f;

  float thetaY = (float) PI / 180.0f * (fov / 2);
  float tanThetaY = (float) tan(thetaY);
  float h = 1 / tanThetaY;
  float ww = h / aspect;
  float qq = -( zfar + znear ) / ( zfar - znear );
  float qn = -2 * ( zfar * znear ) / ( zfar - znear );

  projectionMatrix = Array44f::Zero();
  projectionMatrix( 0, 0 ) = ww;
  projectionMatrix( 1, 1 ) = h;
  projectionMatrix( 2, 2 ) = qq;
  projectionMatrix( 2, 3 ) = qn;
  projectionMatrix( 3, 2 ) = -1.0f;

//  projection.setZero();
//  projection.m00 = ww;
//  projection.m11 = h;
//  projection.m22 = qq;
//  projection.m23 = qn;
//  projection.m32 = -1.0f;
  /**
   * Generate a view transformation matrix for OpenGL
   * (See: http://www.opengl.org/documentation/specs/man_pages/hardcopy/GL/html/glu/lookat.html)
   */

// this is just the forward vector
  Vector3f u = forward;
  u.normalize();
//  std::cout << "u vector: \n" << u << std::endl;

  Vector3f v = up;
  v.normalize();
//  std::cout << "v vector: \n" << v << std::endl;

  Vector3f w = u.cross( v );
//  std::cout << "w vector: \n" << w << std::endl;

  Vector3f q = w.cross( u );
//  std::cout << "q vector: \n" << q << std::endl;
  w.normalize();
  q.normalize();

  Matrix4f orientation = Matrix4f::Identity();
  Matrix4f translate = Matrix4f::Identity();

//  printf( "Initializing orientation..." );
  orientation << w.transpose(), 0.0f,
                 q.transpose(), 0.0f,
                 -u.transpose(), 0.0f,
                 orientation.row( 3 );
//  printf( "done.\n" );
//  std::cout << "Orientation Matrix: \n" << orientation << std::endl;

//  printf( "Initializing translate..." );
  translate.col( 3 ) << -position, 1.0f;
//  printf( "done.\n" );
//  std::cout << "Translate Matrix: \n" << translate << std::endl;

  viewMatrix = orientation * translate;

//  u.sub(target, eye);
//  u.normalize();
//  v.set(up);
//  v.normalize();
//  orientation.setIdentity();
//  translate.setIdentity();
//  orientation.m00 = w.x; orientation.m01 = w.y; orientation.m02 = w.z;
//  orientation.m10 = q.x; orientation.m11 = q.y; orientation.m12 = q.z;
//  orientation.m20 = -u.x; orientation.m21 = -u.y; orientation.m22 = -u.z;
//  translate.m03 = -eye.x;
//  translate.m13 = -eye.y;
//  translate.m23 = -eye.z;
//  inverseOrientation.transpose(orientation);
//  view.mul(orientation, translate);

}

void Camera::gl_set_camera()
{
//  printf( "Setting new matrices..." );
  update_matrices();
  glMatrixMode( GL_PROJECTION );
  glLoadMatrixf( projectionMatrix.data() );
//  std::cout << "Projection Matrix: \n" << projectionMatrix << std::endl;
//  glLoadIdentity();
//  gluPerspective( fov * zoom, aspect, znear, zfar );
  glMatrixMode( GL_MODELVIEW );
//  std::cout << "View Matrix: \n" << viewMatrix << std::endl;
  glLoadMatrixf( viewMatrix.data() );
//  glLoadIdentity();
//  gluLookAt( position.x(), position.y(), position.z(),
//             forward.x(), forward.y(), forward.z(),
//             up.x(), up.y(), up.z() );
//  printf( "done.\n" );
}

void Camera::move( Vector3f &offset )
{
  position += offset;
//  std::cout << position << std::endl;
}

void Camera::move_right( float offset )
{
  Vector3f v = forward.cross( up );
  v.normalize();
  v *= offset;
  move( v );
}

void Camera::move_left( float offset )
{
  move_right( -offset );
}

void Camera::move_up( float offset )
{
  Vector3f v = up;
  v *= offset;
  move( v );
}

void Camera::move_down( float offset )
{
  move_up( -offset );
}

void Camera::move_forward( float offset )
{
  Vector3f v = forward;
  v *= offset;
  move( v );
}

void Camera::move_backward( float offset )
{
  move_forward( -offset );
}

void Camera::reset()
{
  position = original_position;
  forward = original_forward;
  up = original_up;
}
