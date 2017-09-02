#include "camera.hpp"
#include "../misc/log.hpp"

#include "../renderer.hpp"
#include "../base.hpp"

//==============================================================================
//  Camera::Camera
//==============================================================================
Camera::Camera() : Controllable_object() {
    set_perspective(45.0f, 0.15f ,50000.0f); 
    m_type = CAM_3D; 
 
	log_init << "Camera initialization" << endl;
}

//==============================================================================
//  Camera::set_perspective()
//==============================================================================
void Camera::set_perspective(float fov_y, float near_plane, float far_plane) {
    m_fov_y = fov_y;
    m_near_plane = near_plane;
    m_far_plane = far_plane;
}

//==============================================================================
//  Camera::get_perspective()
//==============================================================================
void Camera::get_perspective(float &fov_y, float &near_plane, float &far_plane) {
    fov_y = m_fov_y;
    near_plane = m_near_plane;
    far_plane = m_far_plane;
}


//==============================================================================
//  Camera::update_frustum()
//==============================================================================
void Camera::update_frustum() {
    Matrix4x4f clip = renderer->get_projection_matrix() * renderer->get_modelview_matrix();
    
    // This will extract the RIGHT side of the frustum
    m_frustum_planes[FRUSTUM_RIGHT ] = Plane(
    Vector3f( clip[ 3] - clip[ 0], clip[ 7] - clip[ 4], clip[11] - clip[ 8]), clip[15] - clip[12]);

    // This will extract the LEFT side of the frustum
    m_frustum_planes[FRUSTUM_LEFT  ] = Plane(
    Vector3f( clip[ 3] + clip[ 0], clip[ 7] + clip[ 4], clip[11] + clip[ 8]), clip[15] + clip[12]);

    // This will extract the BOTTOM side of the frustum
    m_frustum_planes[FRUSTUM_BOTTOM] = Plane(
    Vector3f( clip[ 3] + clip[ 1], clip[ 7] + clip[ 5], clip[11] + clip[ 9]), clip[15] + clip[13]);

    // This will extract the TOP side of the frustum
    m_frustum_planes[FRUSTUM_TOP   ] = Plane(
    Vector3f( clip[ 3] - clip[ 1], clip[ 7] - clip[ 5], clip[11] - clip[ 9]), clip[15] - clip[13]);

    // This will extract the BACK side of the frustum
    m_frustum_planes[FRUSTUM_BACK  ] = Plane(    
    Vector3f( clip[ 3] - clip[ 2], clip[ 7] - clip[ 6], clip[11] - clip[10]), clip[15] - clip[14]);
        
    // This will extract the FRONT side of the frustum
    m_frustum_planes[FRUSTUM_FRONT ] = Plane(    
    Vector3f( clip[ 3] + clip[ 2], clip[ 7] + clip[ 6], clip[11] + clip[10]), clip[15] + clip[14]);
    
    // And normalize..
    for(int i=0; i<FRUSTUM_PLANES; ++i) {
        m_frustum_planes[i].normalize();
    }        
}    

//==============================================================================
//  Camera_controller_fps::Camera_controller_fps()
// remember, z is up
//==============================================================================
Camera_controller_fps::Camera_controller_fps() {
    look_at( Vector3f(0.0, 0.0, 0.0),
    		 Vector3f(0.0, 1.0, 0.5),
       		 Vector3f(0.0, 0.0, 1.0) );

	m_speed = 150.0f;
}

//==============================================================================
//  Camera_controller_fps::set_rotation()
//==============================================================================
void Camera_controller_fps::set_rotation(float angle_z, float angle_y) {
    // Todo: if the current rotation (in radians) is greater than 1.0, 
    // we want to cap it.
        
	Vector3f axis = cross(m_view - m_position, m_up);
	axis.normalize();;
	
    set_rotation(angle_y, axis);
    // Rotate around the y axis no matter what the current_rot_x is
    set_rotation(angle_z, Vector3f(0, 0, 1) );
}

//==============================================================================
//  Camera_controller_fps::set_rotation()
//==============================================================================
void Camera_controller_fps::set_rotation(float angle, Vector3f axis) {
    Vector3f new_view;
    // Get the view vector (The direction we are facing)
    Vector3f view = m_view - m_position;     
 
    // build rotation matrix
    Matrix3x3f rotation;
    rotation.set_rotation_axis( angle, axis );

    new_view = rotation * view;
    m_up = rotation * m_up;
    
    // Now we just add the newly rotated vector to our position to set
    // our new rotated view of our Camera.
    m_view = m_position + new_view;
    
    // update strafe
    m_strafe = cross(new_view.get_normalized(), m_up).get_normalized();
    
    look_at( m_position, m_view, m_up);
}

//==============================================================================
//  Camera_controller_fps::strafe()
//==============================================================================
void Camera_controller_fps::strafe(float speed) {   
    // Add the strafe vector to our position
    m_position.x += m_strafe.x * speed;
    m_position.y += m_strafe.y * speed;

    // Add the strafe vector to our view
    m_view.x += m_strafe.x * speed;
    m_view.y += m_strafe.y * speed;
}

//==============================================================================
//  Camera_controller_fps::move()
//==============================================================================
void Camera_controller_fps::move(float speed) {
    // Get the current view vector (the direction we are looking)
    Vector3f movement = m_view - m_position;
    movement.normalize();
    
    movement *= speed;
    
    m_position += movement;
    m_view += movement;
}

//==============================================================================
//  Camera_controller_fps::update()
//==============================================================================
void Camera_controller_fps::update(void) {
    int middle_x = base->get_window_width() / 2;
    int middle_y = base->get_window_height() / 2;
    int mouse_x = base->get_mouse_x();
    int mouse_y = base->get_mouse_y();
    float angle_y = 0.0f;					
    float angle_z = 0.0f;					
    
    // If our cursor is not in the middle
	if((mouse_x != middle_x) || (mouse_y != middle_y) ) {
	    // Set the mouse position to the middle of our window
	    base->set_mouse_position(middle_x,middle_y);

	    // Get the direction the mouse moved in, but bring the number down to a reasonable amount
	    angle_y = (float)( (middle_x - mouse_x) ) / 500.0f;        
	    angle_z = (float)( (middle_y - mouse_y) ) / 500.0f;

		set_rotation(angle_y, angle_z);
	}

    float speed = m_speed * base->get_frame_interval();

    if( base->is_key_pressed(KEY_UP) || base->is_key_pressed(KEY_W) ) {              
        move(speed);              
    }
    if( base->is_key_pressed(KEY_DOWN) || base->is_key_pressed(KEY_S) ) {            
        move(-speed);             
    }
    if( base->is_key_pressed(KEY_LEFT) || base->is_key_pressed(KEY_A) ) {            
        strafe(-speed);
    }
    if( base->is_key_pressed(KEY_RIGHT) || base->is_key_pressed(KEY_D) ) {           
        strafe(speed);
    }   
}

//==============================================================================
//  Camera_fps::Camera_fps()
//==============================================================================
Camera_fps::Camera_fps() { 
    m_control_fps = new Camera_controller_fps();
    set_controller( m_control_fps );
    set_controlled(true); 
};

//==============================================================================
//  Camera_fps::~Camera_fps()
//==============================================================================
Camera_fps::~Camera_fps() { 
    delete m_control_fps; 
}

