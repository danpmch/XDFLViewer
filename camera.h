#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

const float DEFAULT_OFFSET = 1.0f;

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
    void set_zoom( float new_zoom ) { zoom = new_zoom; }
    void incr_zoom_by_percent( float percent = 5.0 ) { zoom += percent; }
    void decr_zoom_by_percent( float percent = 5.0 ) { zoom -= percent; }
    void set_screen_size( int new_width, int new_height ) { width = new_width; height = new_height;
                                                            aspect = float( width ) / float( height ); }

    int get_width() { return width; }
    int get_height() { return height; }

    float get_znear() { return znear; }
    float get_zfar() { return zfar; }
    float get_fov() { return fov; }

    Matrix4f * get_viewMatrix();
    Matrix4f * get_projectionMatrix();

    void modify_view_matrix( Transform< float, 3, Affine > &t );
    void rotate( int dx, int dy );

    void update_matrices();
    void gl_set_camera();

    void move( Vector3f &offset );
    void move_right( float offset = DEFAULT_OFFSET );
    void move_left( float offset = DEFAULT_OFFSET );
    void move_up( float offset = DEFAULT_OFFSET );
    void move_down( float offset = DEFAULT_OFFSET );
    void move_forward( float offset = DEFAULT_OFFSET );
    void move_backward( float offset = DEFAULT_OFFSET );

    void reset();

private:

    Vector3f original_position;
    Vector3f original_up;
    Vector3f original_forward;

    Vector3f position;
    Vector3f up;
    Vector3f forward;

    float fov;
    float aspect;
    float znear;
    float zfar;
    float zoom;

    int width;
    int height;

    Matrix4f projectionMatrix;
    Matrix4f viewMatrix;
};

#endif // CAMERA_H
