#include "camera.h"

Camera::Camera( Vector3f &position, Vector3f &up, Vector3f &forward,
                int width, int height, float fov, float znear,
                float zfar )
{
  this->position = position;
  this->position.normalize();

  this->up = up;
  this->up.normalize();

  this->forward = forward;
  this->forward.normalize();

  this->width = width;
  this->height = height == 0? 1 : height;
  aspect = width / height;

  this->fov = fov;
  this->znear = znear;
  this->zfar = zfar;
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
