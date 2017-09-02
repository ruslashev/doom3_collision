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

#ifndef _MATRIX_
#define _MATRIX_ 1

#include <memory.h>
#include <iostream>

#include "vector.hpp"
#include "../math.hpp"

// forward declaration
class Vector3f;
class Vector4f;

//==============================================================================
//  Matrix3x3f
//==============================================================================
class Matrix3x3f {
public:
  // constructors
  Matrix3x3f(void) {}
  Matrix3x3f(float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7, float e8)
  { set(e0, e1, e2, e3, e4, e5, e6, e7, e8); }
  Matrix3x3f(const float* rhs)      { memcpy(m_data, rhs, 9*sizeof(float)); }
  Matrix3x3f(const Matrix3x3f& rhs) { memcpy(m_data, rhs.m_data, 9*sizeof(float)); }
  Matrix3x3f(float val)             { set_to(val); }

  ~Matrix3x3f() {}

  inline void set_to(float val) { memset(m_data, (int)val, 9*sizeof(float)); }
  inline void set( float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7, float e8) {
    m_data[0]=e0;
    m_data[1]=e1;
    m_data[2]=e2;
    m_data[3]=e3;
    m_data[4]=e4;
    m_data[5]=e5;
    m_data[6]=e6;
    m_data[7]=e7;
    m_data[8]=e8;
  }

  Vector3f get_row(int position) const;
  Vector3f get_column(int position) const;

  void load_identity(void)  {
    set_to(0);
    m_data[0]=1.0f;
    m_data[4]=1.0f;
    m_data[8]=1.0f;
  }

  // overloaded operators
  Matrix3x3f operator+(const Matrix3x3f & rhs) const;
  Matrix3x3f operator-(const Matrix3x3f & rhs) const;
  inline Matrix3x3f operator*(const Matrix3x3f & rhs) const {
    return Matrix3x3f( m_data[0]*rhs.m_data[0]+m_data[3]*rhs.m_data[1]+m_data[6]*rhs.m_data[2],
        m_data[1]*rhs.m_data[0]+m_data[4]*rhs.m_data[1]+m_data[7]*rhs.m_data[2],
        m_data[2]*rhs.m_data[0]+m_data[5]*rhs.m_data[1]+m_data[8]*rhs.m_data[2],

        m_data[0]*rhs.m_data[3]+m_data[3]*rhs.m_data[4]+m_data[6]*rhs.m_data[5],
        m_data[1]*rhs.m_data[3]+m_data[4]*rhs.m_data[4]+m_data[7]*rhs.m_data[5],
        m_data[2]*rhs.m_data[3]+m_data[5]*rhs.m_data[4]+m_data[8]*rhs.m_data[5],

        m_data[0]*rhs.m_data[6]+m_data[3]*rhs.m_data[7]+m_data[6]*rhs.m_data[8],
        m_data[1]*rhs.m_data[6]+m_data[4]*rhs.m_data[7]+m_data[7]*rhs.m_data[8],
        m_data[2]*rhs.m_data[6]+m_data[5]*rhs.m_data[7]+m_data[8]*rhs.m_data[8]);
  }
  Matrix3x3f operator*(const float rhs) const;
  Matrix3x3f operator/(const float rhs) const;
  friend Matrix3x3f operator*(float scale_factor, const Matrix3x3f & rhs);

  bool operator==(const Matrix3x3f & rhs) const;
  bool operator!=(const Matrix3x3f & rhs) const;

  //self-add etc
  void operator+=(const Matrix3x3f & rhs);
  void operator-=(const Matrix3x3f & rhs);
  void operator*=(const Matrix3x3f & rhs);
  void operator*=(const float rhs);
  void operator/=(const float rhs);

  //unary operators
  Matrix3x3f operator-(void) const;
  Matrix3x3f operator+(void) const {return (*this);}

  //multiply a vector by this matrix
  inline Vector3f operator*(const Vector3f rhs) const {
    return Vector3f(m_data[0]*rhs.x + m_data[3]*rhs.y + m_data[6]*rhs.z,
        m_data[1]*rhs.x + m_data[4]*rhs.y + m_data[7]*rhs.z,
        m_data[2]*rhs.x + m_data[5]*rhs.y + m_data[8]*rhs.z);
  }
  inline Vector3f multiply(const Vector3f rhs) const {
    return Vector3f(m_data[0]*rhs.x + m_data[1]*rhs.y + m_data[2]*rhs.z,
        m_data[3]*rhs.x + m_data[4]*rhs.y + m_data[5]*rhs.z,
        m_data[6]*rhs.x + m_data[7]*rhs.y + m_data[8]*rhs.z);
  }

  // set to perform an operation on space - removes other m_data
  void set_rotation_axis(const double angle, const Vector3f & axis);
  void set_rotation_x(const double angle);
  void set_rotation_y(const double angle);
  void set_rotation_z(const double angle);
  void set_rotation(const float yaw, const float pitch, const float roll);

  // cast to pointer to a (float *) for glGetFloatv etc
  operator float* () const {return (float*) this;}
  float operator[] (int index) { return m_data[index]; }

  float & operator()(const int i, const int j) {return m_data[i + 3*j];}
  const float & operator()(const int i, const int j) const {return m_data[i + 3*j];}

  // inline void orthonormalise();
  inline void orthonormalize() {
    Vector3f u1(operator()(0, 0), operator()(1, 0), operator()(2, 0));
    Vector3f u2(operator()(0, 1), operator()(1, 1), operator()(2, 1));
    Vector3f u3(operator()(0, 2), operator()(1, 2), operator()(2, 2));

    Vector3f w1 = u1.get_normalized();

    Vector3f w2 = (u2 - proj(w1, u2)).get_normalized();
    Vector3f w3 = (u3 - proj(w1, u3) - proj(w2, u3)).get_normalized();

    operator()(0, 0) = w1[0];
    operator()(1, 0) = w1[1];
    operator()(2, 0) = w1[2];

    operator()(0, 1) = w2[0];
    operator()(1, 1) = w2[1];
    operator()(2, 1) = w2[2];

    operator()(0, 2) = w3[0];
    operator()(1, 2) = w3[1];
    operator()(2, 2) = w3[2];
  }

  void look_at( const Vector3f & eye, const Vector3f & center, const Vector3f & up);

  // member variables
  float m_data[9];
};

inline Matrix3x3f transpose(const Matrix3x3f & rhs) {
  return Matrix3x3f(rhs.m_data[0+3*0], rhs.m_data[0+3*1], rhs.m_data[0+3*2],
      rhs.m_data[1+3*0], rhs.m_data[1+3*1], rhs.m_data[1+3*2],
      rhs.m_data[2+3*0], rhs.m_data[2+3*1], rhs.m_data[2+3*2] );
}

inline const Matrix3x3f & Matrix3x3f_identity() {
  static const Matrix3x3f result(1, 0, 0,
      0, 1, 0,
      0, 0, 1);
  return result;
}

inline Matrix3x3f rotation_matrix(float ang, const Vector3f & dir) {
  // from page 32(45) of glspec.dvi
  Matrix3x3f uut(dir[0]*dir[0], dir[1]*dir[0], dir[2]*dir[0],
      dir[0]*dir[1], dir[1]*dir[1], dir[2]*dir[1],
      dir[0]*dir[2], dir[1]*dir[2], dir[2]*dir[2]);

  Matrix3x3f s(0, dir[2], -dir[1],
      -dir[2], 0, dir[0],
      dir[1], -dir[0], 0);

  return (uut + (float) cosf(deg_to_rad(ang)) *
      (Matrix3x3f_identity() - uut) + (float) sinf(deg_to_rad(ang)) * s);
}
/*
   inline bool is_finite(const Matrix3x3f &rhs) const {
   for (unsigned i = 0 ; i < 9 ; ++i) {
   if (!is_finite(rhs[i])) {
   return false;
   }
   }
   return true;
   }
   */


//==============================================================================
//  Matrix4x4f
//==============================================================================
class Matrix4x4f {
public:
  // constructors
  Matrix4x4f(void) {}
  Matrix4x4f(float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7, float e8,
      float e9, float e10, float e11, float e12, float e13, float e14, float e15)
  { set(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15); }
  Matrix4x4f(const float* rhs)      { memcpy(m_data, rhs, 16*sizeof(float)); }
  Matrix4x4f(const Matrix4x4f& rhs) { memcpy(m_data, rhs.m_data, 16*sizeof(float)); }
  Matrix4x4f(float val)             { set_to(val); }
  Matrix4x4f(const Matrix3x3f& rhs) { set( rhs.m_data[ 0], rhs.m_data[ 1], rhs.m_data[ 2], 0,
      rhs.m_data[ 3], rhs.m_data[ 4], rhs.m_data[ 5], 0,
      rhs.m_data[ 6], rhs.m_data[ 7], rhs.m_data[ 8], 0,
      0,              0,              0, 1); }
  ~Matrix4x4f() {}

  inline void set_to(float val) { memset(m_data, (int)val, 16*sizeof(float)); }
  inline void set( float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7, float e8,
      float e9, float e10, float e11, float e12, float e13, float e14, float e15) {
    m_data[ 0]=e0;
    m_data[ 1]=e1;
    m_data[ 2]=e2;
    m_data[ 3]=e3;
    m_data[ 4]=e4;
    m_data[ 5]=e5;
    m_data[ 6]=e6;
    m_data[ 7]=e7;
    m_data[ 8]=e8;
    m_data[ 9]=e9;
    m_data[10]=e10;
    m_data[11]=e11;
    m_data[12]=e12;
    m_data[13]=e13;
    m_data[14]=e14;
    m_data[15]=e15;
  }

  void load_identity(void)  {
    set_to(0);
    m_data[ 0]=1.0f;
    m_data[ 5]=1.0f;
    m_data[10]=1.0f;
    m_data[15]=1.0f;
  }

  // overloaded operators
  Matrix4x4f operator+(const Matrix4x4f & rhs) const;
  Matrix4x4f operator-(const Matrix4x4f & rhs) const;
  inline Matrix4x4f operator*(const Matrix4x4f & rhs) const {
    return Matrix4x4f( m_data[0]*rhs.m_data[0]+m_data[4]*rhs.m_data[1]+m_data[8]*rhs.m_data[2]+m_data[12]*rhs.m_data[3],
        m_data[1]*rhs.m_data[0]+m_data[5]*rhs.m_data[1]+m_data[9]*rhs.m_data[2]+m_data[13]*rhs.m_data[3],
        m_data[2]*rhs.m_data[0]+m_data[6]*rhs.m_data[1]+m_data[10]*rhs.m_data[2]+m_data[14]*rhs.m_data[3],
        m_data[3]*rhs.m_data[0]+m_data[7]*rhs.m_data[1]+m_data[11]*rhs.m_data[2]+m_data[15]*rhs.m_data[3],

        m_data[0]*rhs.m_data[4]+m_data[4]*rhs.m_data[5]+m_data[8]*rhs.m_data[6]+m_data[12]*rhs.m_data[7],
        m_data[1]*rhs.m_data[4]+m_data[5]*rhs.m_data[5]+m_data[9]*rhs.m_data[6]+m_data[13]*rhs.m_data[7],
        m_data[2]*rhs.m_data[4]+m_data[6]*rhs.m_data[5]+m_data[10]*rhs.m_data[6]+m_data[14]*rhs.m_data[7],
        m_data[3]*rhs.m_data[4]+m_data[7]*rhs.m_data[5]+m_data[11]*rhs.m_data[6]+m_data[15]*rhs.m_data[7],

        m_data[0]*rhs.m_data[8]+m_data[4]*rhs.m_data[9]+m_data[8]*rhs.m_data[10]+m_data[12]*rhs.m_data[11],
        m_data[1]*rhs.m_data[8]+m_data[5]*rhs.m_data[9]+m_data[9]*rhs.m_data[10]+m_data[13]*rhs.m_data[11],
        m_data[2]*rhs.m_data[8]+m_data[6]*rhs.m_data[9]+m_data[10]*rhs.m_data[10]+m_data[14]*rhs.m_data[11],
        m_data[3]*rhs.m_data[8]+m_data[7]*rhs.m_data[9]+m_data[11]*rhs.m_data[10]+m_data[15]*rhs.m_data[11],

        m_data[0]*rhs.m_data[12]+m_data[4]*rhs.m_data[13]+m_data[8]*rhs.m_data[14]+m_data[12]*rhs.m_data[15],
        m_data[1]*rhs.m_data[12]+m_data[5]*rhs.m_data[13]+m_data[9]*rhs.m_data[14]+m_data[13]*rhs.m_data[15],
        m_data[2]*rhs.m_data[12]+m_data[6]*rhs.m_data[13]+m_data[10]*rhs.m_data[14]+m_data[14]*rhs.m_data[15],
        m_data[3]*rhs.m_data[12]+m_data[7]*rhs.m_data[13]+m_data[11]*rhs.m_data[14]+m_data[15]*rhs.m_data[15]);
  }
  Matrix4x4f operator*(const float rhs) const;
  Matrix4x4f operator/(const float rhs) const;
  friend Matrix4x4f operator*(float scale_factor, const Matrix4x4f & rhs);

  bool operator==(const Matrix4x4f & rhs) const;
  bool operator!=(const Matrix4x4f & rhs) const;

  //self-add etc
  void operator+=(const Matrix4x4f & rhs);
  void operator-=(const Matrix4x4f & rhs);
  void operator*=(const Matrix4x4f & rhs);
  void operator*=(const float rhs);
  void operator/=(const float rhs);

  //unary operators
  Matrix4x4f operator-(void) const;
  Matrix4x4f operator+(void) const {return (*this);}

  //multiply a vector by this matrix
  inline Vector4f operator*(const Vector4f rhs) const {
    return Vector4f(m_data[ 0]*rhs.x + m_data[ 4]*rhs.y + m_data[ 8]*rhs.z + m_data[12]*rhs.w,
        m_data[ 1]*rhs.x + m_data[ 5]*rhs.y + m_data[ 9]*rhs.z + m_data[13]*rhs.w,
        m_data[ 2]*rhs.x + m_data[ 6]*rhs.y + m_data[10]*rhs.z + m_data[14]*rhs.w,
        m_data[ 3]*rhs.x + m_data[ 7]*rhs.y + m_data[11]*rhs.z + m_data[15]*rhs.w);
  }
  inline Vector4f multiply(const Vector4f rhs) const {
    return Vector4f(m_data[ 0]*rhs.x + m_data[ 1]*rhs.y + m_data[ 2]*rhs.z + m_data[ 3]*rhs.w,
        m_data[ 4]*rhs.x + m_data[ 5]*rhs.y + m_data[ 6]*rhs.z + m_data[ 7]*rhs.w,
        m_data[ 8]*rhs.x + m_data[ 9]*rhs.y + m_data[10]*rhs.z + m_data[11]*rhs.w,
        m_data[12]*rhs.x + m_data[13]*rhs.y + m_data[14]*rhs.z + m_data[15]*rhs.w);
  }

  // cast to pointer to a (float *) for glGetFloatv etc
  operator float* () const {return (float*) this;}
  float operator[] (int index) { return m_data[index]; }

  float & operator()(const int i, const int j) {return m_data[i + 4*j];}
  const float & operator()(const int i, const int j) const {return m_data[i + 4*j];}

  // member variables
  float m_data[16];
};

inline Matrix4x4f transpose(const Matrix4x4f & rhs) {
  return Matrix4x4f(rhs.m_data[ 0+4*0], rhs.m_data[0+4*1], rhs.m_data[0+4*2], rhs.m_data[0+4*3],
      rhs.m_data[ 1+4*0], rhs.m_data[1+4*1], rhs.m_data[1+4*2], rhs.m_data[1+4*3],
      rhs.m_data[ 2+4*0], rhs.m_data[2+4*1], rhs.m_data[2+4*2], rhs.m_data[2+4*3],
      rhs.m_data[ 3+4*0], rhs.m_data[3+4*1], rhs.m_data[3+4*2], rhs.m_data[3+4*3] );
}

inline const Matrix4x4f & Matrix4x4f_identity() {
  static const Matrix4x4f result(1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1);
  return result;
}

std::ostream& operator <<(std::ostream& os, const Matrix3x3f& rhs);
std::ostream& operator <<(std::ostream& os, const Matrix4x4f& rhs);

typedef Matrix3x3f Orientation;

#endif	/* _MATRIX_ */
