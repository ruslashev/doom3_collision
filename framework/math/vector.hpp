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

#ifndef _VECTOR_
#define _VECTOR_ 1

#include <iostream>
#include "../math.hpp"

// forward declaration

class Vector2f;
class Vector3f;
class Vector3f;

//==============================================================================
//  Vector4f
//==============================================================================
class Vector4f {
public:
  // constructors
  Vector4f(void) {}
  Vector4f(float new_x, float new_y, float new_z, float new_w)
  { set(new_x, new_y, new_z, new_w); }
  Vector4f(const float* rhs)	    { x=*rhs; y=*(rhs+1); z=*(rhs+2); w=*(rhs+3); }
  Vector4f(const Vector4f& rhs)   { set(rhs.x, rhs.y, rhs.z, rhs.w); }
  Vector4f(float val)             { set_to(val); }

  ~Vector4f() {}

  inline void set_to(float val) { x = y = z = w = val; }
  inline void set(float new_x, float new_y, float new_z, float new_w) { x=new_x; y=new_y; z=new_z; w=new_w; }

  // vector algebra
  inline float get_length() const { return (float)sqrt(get_squared_length()); }
  inline float get_squared_length() const { return (x*x)+(y*y)+(z*z); }

  inline void normalize() {
    float inv_length = 1.0f / get_length();
    (*this) *= inv_length;
  }
  Vector4f get_normalized() const {
    Vector4f result(*this);
    result.normalize();
    return result;
  }
  inline void fast_normalize() {
    float inv_length = fast_inv_sqrt( get_squared_length() );
    (*this) *= inv_length;
  }
  Vector4f get_fast_normalized() const {
    Vector4f result(*this);
    result.fast_normalize();
    return result;
  }

  // overloaded operators
  Vector4f operator+(const Vector4f & rhs) const { return Vector4f(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
  Vector4f operator-(const Vector4f & rhs) const { return Vector4f(x - rhs.x, y - rhs.y, z - rhs.z, z - rhs.w); }
  Vector4f operator/(const float rhs)      const { return (rhs==0.0f) ? Vector4f(0.0f, 0.0f, 0.0f, 0.0f) : Vector4f(x / rhs, y / rhs, z / rhs, w / rhs); }
  Vector4f operator*(const float rhs)      const { return Vector4f(x*rhs, y*rhs, z*rhs, w*rhs); }
  float operator*(const Vector4f & rhs)    const { return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;}
  friend Vector4f operator*(float scale_factor, const Vector4f & rhs) { return rhs * scale_factor; }

  bool operator==(const Vector4f & rhs) const { return (x==rhs.x && y==rhs.y && z==rhs.z && w == rhs.w); }
  bool operator!=(const Vector4f & rhs) const { return !((*this)==rhs); }

  void operator+=(const Vector4f & rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; w+=rhs.w; }
  void operator-=(const Vector4f & rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; w-=rhs.w; }
  void operator*=(const float rhs)      { x*=rhs; y*=rhs; z*=rhs; w*=rhs; }
  void operator/=(const float rhs)      { if(rhs!=0.0f) { x/=rhs; y/=rhs; z/=rhs; w/=rhs; } }

  Vector4f operator-(void) const {return Vector4f(-x, -y, -z, -w);}
  Vector4f operator+(void) const {return *this;}

  operator float* () const {return (float*) this;}

  // member variables
  float x;
  float y;
  float z;
  float w;
};

static inline Vector4f lerp(const Vector4f & v1, const Vector4f & v2, float factor) {
  return v1*(1.0f-factor) + v2*factor;
}

static inline float dot(const Vector4f & lhs, const Vector4f & rhs) {
  return (lhs.x * rhs.x +
      lhs.y * rhs.y +
      lhs.z * rhs.z +
      lhs.w * rhs.w);
}

inline bool is_finite(const Vector4f & v1) {
  return (is_finite(v1.x) && is_finite(v1.y) && is_finite(v1.z) && is_finite(v1.w));
}

//==============================================================================
//  Vector3f
//==============================================================================
class Vector3f {
public:
  // constructors
  Vector3f(void) {}
  Vector3f(float new_x, float new_y, float new_z) { set(new_x, new_y, new_z); }
  Vector3f(const float* rhs)	                    { x=*rhs; y=*(rhs+1); z=*(rhs+2); }
  Vector3f(const Vector3f& rhs)                   { set(rhs.x, rhs.y, rhs.z); }
  Vector3f(float val)                             { set_to(val); }

  ~Vector3f() {}

  inline void set_to(float val) { x = y = z = val; }
  inline void set(float new_x, float new_y, float new_z) { x=new_x; y=new_y; z=new_z; }

  // vector algebra
  inline float get_length() const { return (float)sqrt(get_squared_length()); }
  inline float get_squared_length() const { return (x*x)+(y*y)+(z*z); }

  inline void normalize() {
    float inv_length = 1.0f / get_length();
    (*this) *= inv_length;
  }
  Vector3f get_normalized() const {
    Vector3f result(*this);
    result.normalize();
    return result;
  }
  inline void fast_normalize() {
    float inv_length = fast_inv_sqrt( get_squared_length() );
    (*this) *= inv_length;
  }
  Vector3f get_fast_normalized() const {
    Vector3f result(*this);
    result.fast_normalize();
    return result;
  }

  // overloaded operators
  Vector3f operator+(const Vector3f & rhs) const { return Vector3f(x + rhs.x, y + rhs.y, z + rhs.z); }
  Vector3f operator-(const Vector3f & rhs) const { return Vector3f(x - rhs.x, y - rhs.y, z - rhs.z); }
  Vector3f operator/(const float rhs)      const { return (rhs==0.0f) ? Vector3f(0.0f, 0.0f, 0.0f) : Vector3f(x / rhs, y / rhs, z / rhs); }
  Vector3f operator*(const float rhs)      const { return Vector3f(x*rhs, y*rhs, z*rhs); }
  float operator*(const Vector3f & rhs)    const { return x*rhs.x + y*rhs.y + z*rhs.z; }
  friend Vector3f operator*(float scale_factor, const Vector3f & rhs) { return rhs * scale_factor; }

  bool operator==(const Vector3f & rhs) const { return (x==rhs.x && y==rhs.y && z==rhs.z); }
  bool operator!=(const Vector3f & rhs) const { return !((*this)==rhs); }

  void operator+=(const Vector3f & rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; }
  void operator-=(const Vector3f & rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; }
  void operator*=(const float rhs)      { x*=rhs; y*=rhs; z*=rhs; }
  void operator/=(const float rhs)      { if(rhs!=0.0f) { x/=rhs; y/=rhs; z/=rhs; } }

  Vector3f operator-(void) const {return Vector3f(-x, -y, -z);}
  Vector3f operator+(void) const {return *this;}

  operator float* () const {return (float*) this;}

  // member variables
  float x;
  float y;
  float z;
};

static inline Vector3f lerp(const Vector3f & v1, const Vector3f & v2, float factor) {
  return v1*(1.0f-factor) + v2*factor;
}

static inline float dot(const Vector3f & lhs, const Vector3f & rhs) {
  return (lhs.x * rhs.x +
      lhs.y * rhs.y +
      lhs.z * rhs.z);
}

static inline Vector3f cross(const Vector3f & lhs, const Vector3f & rhs) {
  return Vector3f(lhs.y*rhs.z - lhs.z*rhs.y,
      lhs.z*rhs.x - lhs.x*rhs.z,
      lhs.x*rhs.y - lhs.y*rhs.x);
}

static inline Vector3f proj(const Vector3f & v1, const Vector3f & v2) {
  return (dot(v1, v2) * v1) / v1.get_squared_length();
}

inline bool is_finite(const Vector3f & v1) {
  return (is_finite(v1.x) && is_finite(v1.y) && is_finite(v1.z));
}

//==============================================================================
//  Vector2f
//==============================================================================
class Vector2f {
public:
  // constructors
  Vector2f(void) {}
  Vector2f(float new_x, float new_y) { set(new_x, new_y); }
  Vector2f(const float* rhs)         { x=*rhs; y=*(rhs+1); }
  Vector2f(const Vector2f& rhs)      { set(rhs.x, rhs.y); }
  Vector2f(float val)                { set_to(val); }

  ~Vector2f() {}

  inline void set_to(float val) { x = y = val; }
  inline void set(float new_x, float new_y) { x=new_x; y=new_y; }

  // vector algebra
  inline float get_length() const { return (float)sqrt(get_squared_length()); }
  inline float get_squared_length() const { return (x*x)+(y*y); }

  inline void normalize() {
    float inv_length = 1.0f / get_length();
    (*this) *= inv_length;
  }
  Vector2f get_normalized() const {
    Vector2f result(*this);
    result.normalize();
    return result;
  }
  inline void fast_normalize() {
    float inv_length = fast_inv_sqrt( get_squared_length() );
    (*this) *= inv_length;
  }
  Vector2f get_fast_normalized() const {
    Vector2f result(*this);
    result.fast_normalize();
    return result;
  }

  // overloaded operators
  Vector2f operator+(const Vector2f & rhs) const { return Vector2f(x + rhs.x, y + rhs.y); }
  Vector2f operator-(const Vector2f & rhs) const { return Vector2f(x - rhs.x, y - rhs.y); }
  Vector2f operator/(const float rhs)      const { return (rhs==0.0f) ? Vector2f(0.0f, 0.0f) : Vector2f(x / rhs, y / rhs); }
  Vector2f operator*(const float rhs)      const { return Vector2f(x*rhs, y*rhs); }
  float operator*(const Vector2f & rhs)    const { return x*rhs.x + y*rhs.y; }
  friend Vector2f operator*(float scale_factor, const Vector2f & rhs) { return rhs * scale_factor; }

  bool operator==(const Vector2f & rhs) const { return (x==rhs.x && y==rhs.y); }
  bool operator!=(const Vector2f & rhs) const { return !((*this)==rhs); }

  void operator+=(const Vector2f & rhs) { x+=rhs.x; y+=rhs.y; }
  void operator-=(const Vector2f & rhs) { x-=rhs.x; y-=rhs.y; }
  void operator*=(const float rhs)      { x*=rhs; y*=rhs; }
  void operator/=(const float rhs)      { if(rhs!=0.0f) { x/=rhs; y/=rhs; } }

  Vector2f operator-(void) const {return Vector2f(-x, -y);}
  Vector2f operator+(void) const {return *this;}

  operator float* () const {return (float*) this;}

  // member variables
  float x;
  float y;
};

static inline Vector2f lerp(const Vector2f & v1, const Vector2f & v2, float factor) {
  return v1*(1.0f-factor) + v2*factor;
}

static inline float dot(const Vector2f & lhs, const Vector2f & rhs) {
  return (lhs.x * rhs.x +
      lhs.y * rhs.y );
}

inline bool is_finite(const Vector2f & v1) {
  return (is_finite(v1.x) && is_finite(v1.y));
}

std::ostream& operator << (std::ostream& os, const Vector4f& rhs);
std::istream& operator >> (std::istream& in, Vector4f& rhs);
std::ostream& operator << (std::ostream& os, const Vector3f& rhs);
std::istream& operator >> (std::istream& in, Vector3f& rhs);
std::ostream& operator << (std::ostream& os, const Vector2f& rhs);
std::istream& operator >> (std::istream& in, Vector2f& rhs);

typedef Vector3f Position;
typedef Vector3f Velocity;
typedef Vector3f Rotation;
typedef Vector3f Color;
typedef Vector3f ColorRGB;
typedef Vector4f ColorRGBA;

const Color black     (0.0f, 0.0f, 0.0f);
const Color white     (1.0f, 1.0f, 1.0f);
const Color green     (0.0f, 1.0f, 0.0f);
const Color red       (1.0f, 0.0f, 0.0f);
const Color blue      (0.0f, 0.0f, 1.0f);
const Color yellow    (1.0f, 1.0f, 0.0f);
const Color purple    (1.0f, 0.0f, 1.0f);
const Color orange    (1.0f, 0.5f, 0.0f);
const Color lightblue (0.2f, 0.6f, 1.0f);


#endif	/* _VECTOR_ */
