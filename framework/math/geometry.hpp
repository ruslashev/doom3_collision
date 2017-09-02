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

#ifndef _GEOMETRY_
#define _GEOMETRY_ 1

#include <iostream>
#include "vector.hpp"


//==============================================================================
//  Plane
//==============================================================================
class Plane {
public:
  // constructors
  Plane(void) {}
  Plane(const Vector3f& n_normal, float n_d ) : normal(n_normal), d(n_d) {}

  ~Plane() {}

  // vector algebra
  inline void normalize() {
    float inv_length = 1.0f / normal.get_length();
    normal *= inv_length;
    d *= inv_length;
  }

  inline bool is_in_front(const Vector3f & point) {
    return (point*normal+d > 0);
  }

  inline float distance(const Vector3f & point) {
    return point*normal-d;
  }

  // member variables
  Vector3f normal;
  float d;
};

#endif	/* _GEOMETRY_ */

