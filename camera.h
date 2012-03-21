#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Core>

using namespace Eigen;

class Camera
{
public:

    Camera();
    Camera( Vector3f &position, Vector3f &up, Vector3f &forward, int width, int height, float fov = 45.0f, float znear = 1.0f,
            float zfar = 1000.0f );

    void set_position( Vector3f &new_position ){ position = new_position; }
    void set_up( Vector3f &new_up ) { up = new_up; }
    void set_forward( Vector3f &new_forward ) { forward = new_forward; }

    void set_fov( float new_fov ) { fov = new_fov; }
    void set_znear( float new_znear ) { znear = new_znear; }
    void set_zfar( float new_zfar ) { zfar = new_zfar; }
    void set_screen_size( int new_width, int new_height ) { width = new_width; height = new_height;
                                                            aspect = float( width ) / float( height ); }

    Matrix4f * get_viewMatrix();
    Matrix4f * get_projectionMatrix();

private:

    Vector3f position;
    Vector3f up;
    Vector3f forward;

    float fov;
    float aspect;
    float znear;
    float zfar;

    int width;
    int height;

    Matrix4f projectionMatrix;
    Matrix4f viewMatrix;
};

#endif // CAMERA_H
