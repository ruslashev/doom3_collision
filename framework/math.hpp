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

#ifndef _MATH_
#define _MATH_ 1

#include <math.h>
#include <stdlib.h>

#define PI 3.1415926535897932384626433832795f
#define TWO_PI 6.28318530717958647692528676655901f
#define PI_DIV_180 0.0174532925199432957692369076848861f
#define _180_DIV_PI 57.2957795130823208767981548141052f

inline float deg_to_rad(float deg) {return (float) (deg * PI_DIV_180);}
inline float rad_to_deg(float rad) {return (float) (rad * _180_DIV_PI);}

inline float ranged_random(float v1,float v2) {
  return v1 + (v2-v1)*((float)rand())/((float)RAND_MAX);
}
inline bool is_finite(float val) {
  return ((val < 1e8) && (val > -1e8));
}

//This code is purported to be from Quake3 and provides an approximation
//to the inverse square root of a number, 1/sqrtf(x).
inline float fast_inv_sqrt(float x) {
  float xhalf = 0.5f*x;
  long i = *(long*) &x;
  //    i = 0x5f3759df - (i>>1);	// original
  //    i = 0x5f375a86 - (i>>1);  // better?
  i = 0x5F400000 - (i>>1);  // Nick (flipcode)?
  x = *(float*) &i;
  x = x*(1.5f-xhalf*x*x);		// Newton step, repeating increases accuracy
  //    x = x*(1.5f-xhalf*x*x);		// Newton step, repeating increases accuracy

  return x;
}

#define roundf(x) floorf((x) + 0.5f)

//#include "math/vector.hpp"
//#include "math/matrix.hpp"

#endif /* _MATH_ */
