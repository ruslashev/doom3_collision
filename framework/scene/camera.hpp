//============================================================================//
// This source file is part of work done by Reinder Nijhoff (reinder@infi.nl) //
// For the latest info, see http://developer.infi.nl                          //
//                                                                            //
// You're free to use the code in any way you like, modified, unmodified or   //
// cut'n'pasted into your own work.                                           //
//                                                                            //
// Part of this source is based on work by:                                   //
//    - Humus (http://esprit.campus.luth.se/~humus/)                          //
//    - Paul Baker (http://www.paulsprojects.net)                             //
//============================================================================//

#ifndef _CAMERA_
#define _CAMERA_ 1

#include "../math/vector.hpp"
#include "../math/geometry.hpp"
#include "../model/controller.hpp"

enum Camera_type {
  CAM_3D		        = 0,
  CAM_2D	            = 1
};

enum Frustum_plane {
  FRUSTUM_FRONT		= 0,
  FRUSTUM_LEFT		= 1,
  FRUSTUM_TOP			= 2,
  FRUSTUM_RIGHT		= 3,
  FRUSTUM_BOTTOM		= 4,
  FRUSTUM_BACK		= 5,
  FRUSTUM_PLANES		= 6
};

//==============================================================================
//  Camera
//==============================================================================
class Camera : public Controllable_object {
public:
  Camera();

  void set_type(const Camera_type type) { m_type = type; }
  Camera_type get_type() const { return m_type; }

  void set_perspective(float fov_y, float near_plane, float far_plane);
  void get_perspective(float &fov_y, float &near_plane, float &far_plane);

  void update_frustum();
  Plane & get_frustum_plane(int index) const { return (Plane &)m_frustum_planes[index]; }
private:
  float m_near_plane;
  float m_far_plane;
  float m_fov_y;

  Camera_type m_type;
  Plane m_frustum_planes[FRUSTUM_PLANES];
};

//==============================================================================
//  Camera_controller_fps
//==============================================================================
class Camera_controller_fps : public Controller {
public:
  Camera_controller_fps();

  inline void set_position (const Vector3f & position) {
    look_at( position, m_view + (position - m_position), m_up);
  }
  inline void look_at( const Vector3f & eye, const Vector3f & center, const Vector3f & up) {
    m_orientation.look_at( eye, center, up );
    m_position = eye;
    m_up = up;
    m_view = center;
  }
  void set_rotation(float angle, Vector3f axis);
  void set_rotation(float angle_x, float angle_z);
  void strafe(float speed);
  void move(float speed);

  // update function, check keyboard and mouse input...
  void update(void);
private:
  float m_speed;

  Vector3f m_view;
  Vector3f m_strafe;
  Vector3f m_up;
};

//==============================================================================
//  Camera_fps
//==============================================================================
class Camera_fps : public Camera {
public:
  Camera_fps();
  ~Camera_fps();
private:
  Camera_controller_fps* m_control_fps;
};

#endif /* _CAMERA_ */

