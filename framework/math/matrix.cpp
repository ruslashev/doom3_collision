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

#include <memory.h>

#include "../misc/log.hpp"
#include "matrix.hpp"

//==============================================================================
//  Matrix3x3f
//==============================================================================
Vector3f Matrix3x3f::get_row(int position) const {
  if(position==0)
    return Vector3f(m_data[0], m_data[3], m_data[6]);

  if(position==1)
    return Vector3f(m_data[1], m_data[4], m_data[7]);

  if(position==2)
    return Vector3f(m_data[2], m_data[5], m_data[8]);

  log_warning << "Illegal argument to Matrix3x3f::get_row(): " << position << endl;
  return Vector3f(0.0f, 0.0f, 0.0f);
}

Vector3f Matrix3x3f::get_column(int position) const {
  if(position==0)
    return Vector3f(m_data[0], m_data[1], m_data[2]);

  if(position==1)
    return Vector3f(m_data[3], m_data[4], m_data[5]);

  if(position==2)
    return Vector3f(m_data[6], m_data[7], m_data[8]);

  log_warning << "Illegal argument to Matrix3x3f::get_column(): " << position << endl;
  return Vector3f(0.0f, 0.0f, 0.0f);
}

Matrix3x3f Matrix3x3f::operator+(const Matrix3x3f & rhs) const {
  return Matrix3x3f(	m_data[0]+rhs.m_data[0],
      m_data[1]+rhs.m_data[1],
      m_data[2]+rhs.m_data[2],
      m_data[3]+rhs.m_data[3],
      m_data[4]+rhs.m_data[4],
      m_data[5]+rhs.m_data[5],
      m_data[6]+rhs.m_data[6],
      m_data[7]+rhs.m_data[7],
      m_data[8]+rhs.m_data[8]);
}

Matrix3x3f Matrix3x3f::operator-(const Matrix3x3f & rhs) const {
  return Matrix3x3f(	m_data[0]-rhs.m_data[0],
      m_data[1]-rhs.m_data[1],
      m_data[2]-rhs.m_data[2],
      m_data[3]-rhs.m_data[3],
      m_data[4]-rhs.m_data[4],
      m_data[5]-rhs.m_data[5],
      m_data[6]-rhs.m_data[6],
      m_data[7]-rhs.m_data[7],
      m_data[8]-rhs.m_data[8]);
}

Matrix3x3f Matrix3x3f::operator*(const float rhs) const {
  return Matrix3x3f(	m_data[0]*rhs,
      m_data[1]*rhs,
      m_data[2]*rhs,
      m_data[3]*rhs,
      m_data[4]*rhs,
      m_data[5]*rhs,
      m_data[6]*rhs,
      m_data[7]*rhs,
      m_data[8]*rhs);
}

Matrix3x3f Matrix3x3f::operator/(const float rhs) const {
  if (rhs==0.0f) {
    log_warning << "Attempted Divide by zero in Matrix3x3f::operator/" << endl;
    return (*this);
  }

  float temp=1/rhs;

  return (*this)*temp;
}

Matrix3x3f operator*(float scale_factor, const Matrix3x3f & rhs) {
  return rhs*scale_factor;
}

bool Matrix3x3f::operator==(const Matrix3x3f & rhs) const {
  for(int i=0; i<9; i++) {
    if(m_data[i]!=rhs.m_data[i])
      return false;
  }
  return true;
}

bool Matrix3x3f::operator!=(const Matrix3x3f & rhs) const {
  return !((*this)==rhs);
}

void Matrix3x3f::operator+=(const Matrix3x3f & rhs) {
  (*this)=(*this)+rhs;
}

void Matrix3x3f::operator-=(const Matrix3x3f & rhs) {
  (*this)=(*this)-rhs;
}

void Matrix3x3f::operator*=(const Matrix3x3f & rhs) {
  (*this)=(*this)*rhs;
}

void Matrix3x3f::operator*=(const float rhs) {
  (*this)=(*this)*rhs;
}

void Matrix3x3f::operator/=(const float rhs) {
  (*this)=(*this)/rhs;
}

Matrix3x3f Matrix3x3f::operator-(void) const {
  Matrix3x3f result(*this);

  for(int i=0; i<9; i++)
    result.m_data[i]=-result.m_data[i];

  return result;
}

void Matrix3x3f::set_rotation_axis(const double angle, const Vector3f & axis)
{
  Vector3f u=axis.get_normalized();

  float sinfAngle=(float)sinf(angle);
  float cosfAngle=(float)cosf(angle);
  float oneMinuscosfAngle=1.0f-cosfAngle;

  load_identity();

  m_data[0]=(u.x)*(u.x) + cosfAngle*(1-(u.x)*(u.x));
  m_data[3]=(u.x)*(u.y)*(oneMinuscosfAngle) - sinfAngle*u.z;
  m_data[6]=(u.x)*(u.z)*(oneMinuscosfAngle) + sinfAngle*u.y;

  m_data[1]=(u.x)*(u.y)*(oneMinuscosfAngle) + sinfAngle*u.z;
  m_data[4]=(u.y)*(u.y) + cosfAngle*(1-(u.y)*(u.y));
  m_data[7]=(u.y)*(u.z)*(oneMinuscosfAngle) - sinfAngle*u.x;

  m_data[2]=(u.x)*(u.z)*(oneMinuscosfAngle) - sinfAngle*u.y;
  m_data[5]=(u.y)*(u.z)*(oneMinuscosfAngle) + sinfAngle*u.x;
  m_data[8]=(u.z)*(u.z) + cosfAngle*(1-(u.z)*(u.z));
}

void Matrix3x3f::set_rotation_x(const double angle) {
  load_identity();

  m_data[4]=(float)cosf(angle);
  m_data[5]=(float)sinf(angle);

  m_data[7]=(float)-sinf(angle);
  m_data[8]=(float)cosf(angle);
}

void Matrix3x3f::set_rotation_y(const double angle) {
  load_identity();

  m_data[0]=(float)cosf(angle);
  m_data[2]=(float)-sinf(angle);

  m_data[6]=(float)sinf(angle);
  m_data[8]=(float)cosf(angle);
}

void Matrix3x3f::set_rotation_z(const double angle) {
  load_identity();

  m_data[0]=(float)cosf(angle);
  m_data[1]=(float)sinf(angle);

  m_data[3]=(float)-sinf(angle);
  m_data[4]=(float)cosf(angle);
}

void Matrix3x3f::set_rotation(const float yaw, const float pitch, const float roll) {
  float cos_roll = cosf(roll);
  float sin_roll = sinf(roll);

  float cos_pitch = cosf(pitch);
  float sin_pitch = sinf(pitch);

  float cos_yaw = cosf(yaw);
  float sin_yaw = sinf(yaw);

  m_data[0] = cos_yaw * cos_pitch;
  m_data[1] = cos_yaw * sin_pitch * sin_roll - sin_yaw * cos_roll;
  m_data[2] = cos_yaw * sin_pitch * cos_roll + sin_yaw * cos_pitch;

  m_data[3] = sin_yaw * cos_pitch;
  m_data[4] = sin_yaw * sin_pitch * sin_roll + cos_yaw * cos_roll;
  m_data[5] = sin_yaw * sin_pitch * cos_roll - cos_yaw * sin_roll;

  m_data[6] = -sin_pitch;
  m_data[7] = cos_pitch * sin_roll;
  m_data[8] = cos_pitch * cos_roll;
}

void Matrix3x3f::look_at( const Vector3f & eye, const Vector3f & center, const Vector3f & up) {
  // from gluLookAt (http://pyopengl.sourceforge.net/documentation/manual/gluLookAt.3G.html)

  Vector3f f = (center - eye).get_normalized();
  Vector3f u = up.get_normalized();
  Vector3f s = cross(f, u);
  u = cross(s, f);

  set( s.x, u.x,-f.x,
      s.y, u.y,-f.y,
      s.z, u.z,-f.z);
}

//==============================================================================
//  Matrix4x4f
//==============================================================================
Matrix4x4f Matrix4x4f::operator+(const Matrix4x4f & rhs) const {
  return Matrix4x4f(	m_data[ 0]+rhs.m_data[ 0],
      m_data[ 1]+rhs.m_data[ 1],
      m_data[ 2]+rhs.m_data[ 2],
      m_data[ 3]+rhs.m_data[ 3],
      m_data[ 4]+rhs.m_data[ 4],
      m_data[ 5]+rhs.m_data[ 5],
      m_data[ 6]+rhs.m_data[ 6],
      m_data[ 7]+rhs.m_data[ 7],
      m_data[ 8]+rhs.m_data[ 8],
      m_data[ 9]+rhs.m_data[ 9],
      m_data[10]+rhs.m_data[10],
      m_data[11]+rhs.m_data[11],
      m_data[12]+rhs.m_data[12],
      m_data[13]+rhs.m_data[13],
      m_data[14]+rhs.m_data[14],
      m_data[15]+rhs.m_data[15]);
}

Matrix4x4f Matrix4x4f::operator-(const Matrix4x4f & rhs) const {
  return Matrix4x4f(	m_data[ 0]-rhs.m_data[ 0],
      m_data[ 1]-rhs.m_data[ 1],
      m_data[ 2]-rhs.m_data[ 2],
      m_data[ 3]-rhs.m_data[ 3],
      m_data[ 4]-rhs.m_data[ 4],
      m_data[ 5]-rhs.m_data[ 5],
      m_data[ 6]-rhs.m_data[ 6],
      m_data[ 7]-rhs.m_data[ 7],
      m_data[ 8]-rhs.m_data[ 8],
      m_data[ 9]-rhs.m_data[ 9],
      m_data[10]-rhs.m_data[10],
      m_data[11]-rhs.m_data[11],
      m_data[12]-rhs.m_data[12],
      m_data[13]-rhs.m_data[13],
      m_data[14]-rhs.m_data[14],
      m_data[15]-rhs.m_data[15]);
}

Matrix4x4f Matrix4x4f::operator*(const float rhs) const {
  return Matrix4x4f(	m_data[ 0]*rhs,
      m_data[ 1]*rhs,
      m_data[ 2]*rhs,
      m_data[ 3]*rhs,
      m_data[ 4]*rhs,
      m_data[ 5]*rhs,
      m_data[ 6]*rhs,
      m_data[ 7]*rhs,
      m_data[ 8]*rhs,
      m_data[ 9]*rhs,
      m_data[10]*rhs,
      m_data[11]*rhs,
      m_data[12]*rhs,
      m_data[13]*rhs,
      m_data[14]*rhs,
      m_data[15]*rhs);
}

Matrix4x4f Matrix4x4f::operator/(const float rhs) const {
  if (rhs==0.0f) {
    log_warning << "Attempted Divide by zero in Matrix4x4f::operator/" << endl;
    return (*this);
  }

  float temp=1/rhs;

  return (*this)*temp;
}

Matrix4x4f operator*(float scale_factor, const Matrix4x4f & rhs) {
  return rhs*scale_factor;
}

bool Matrix4x4f::operator==(const Matrix4x4f & rhs) const {
  for(int i=0; i<16; i++) {
    if(m_data[i]!=rhs.m_data[i])
      return false;
  }
  return true;
}

bool Matrix4x4f::operator!=(const Matrix4x4f & rhs) const {
  return !((*this)==rhs);
}

void Matrix4x4f::operator+=(const Matrix4x4f & rhs) {
  (*this)=(*this)+rhs;
}

void Matrix4x4f::operator-=(const Matrix4x4f & rhs) {
  (*this)=(*this)-rhs;
}

void Matrix4x4f::operator*=(const Matrix4x4f & rhs) {
  (*this)=(*this)*rhs;
}

void Matrix4x4f::operator*=(const float rhs) {
  (*this)=(*this)*rhs;
}

void Matrix4x4f::operator/=(const float rhs) {
  (*this)=(*this)/rhs;
}

Matrix4x4f Matrix4x4f::operator-(void) const {
  Matrix4x4f result(*this);

  for(int i=0; i<16; i++)
    result.m_data[i]=-result.m_data[i];

  return result;
}

//==============================================================================
//  ostream and istream operators..
//==============================================================================
std::ostream& operator <<(std::ostream& os, const Matrix3x3f& rhs) {
  os << endl << "Matrix3x3f(" << rhs.m_data[0] << ", " << rhs.m_data[1] << ", " << rhs.m_data[2] << ")" << endl;
  os << "         (" << rhs.m_data[3] << ", " << rhs.m_data[4] << ", " << rhs.m_data[5] << ")" << endl;
  os << "         (" << rhs.m_data[6] << ", " << rhs.m_data[7] << ", " << rhs.m_data[8] << ")" << endl;
  return os;
}

std::ostream& operator <<(std::ostream& os, const Matrix4x4f& rhs) {
  os << endl << "Matrix4x4f(" << rhs.m_data[0] << ", " << rhs.m_data[1] << ", " << rhs.m_data[2] << ", " << rhs.m_data[3] << ")" << endl;
  os << "         (" << rhs.m_data[ 4] << ", " << rhs.m_data[ 5] << ", " << rhs.m_data[ 6] << ", " << rhs.m_data[ 7] << ")" << endl;
  os << "         (" << rhs.m_data[ 8] << ", " << rhs.m_data[ 9] << ", " << rhs.m_data[10] << ", " << rhs.m_data[11] << ")" << endl;
  os << "         (" << rhs.m_data[12] << ", " << rhs.m_data[13] << ", " << rhs.m_data[14] << ", " << rhs.m_data[15] << ")" << endl;
  return os;
}

