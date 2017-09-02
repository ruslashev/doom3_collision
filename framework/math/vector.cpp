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

#include "vector.hpp"

//==============================================================================
//  ostream and istream operators..
//==============================================================================
std::ostream& operator << (std::ostream& os, const Vector4f& rhs) {
  os << "(" << rhs.x << "," << rhs.y << "," << rhs.z << "," << rhs.w << ")";
  return os;
}

std::istream& operator >> (std::istream& in, Vector4f& rhs) {
  in.ignore(1);    // (
  in >> rhs.x;
  in.ignore(1);    // ,
  in >> rhs.y;
  in.ignore (1);   // ,
  in >> rhs.z;
  in.ignore (1);   // ,
  in >> rhs.w;
  in.ignore (1);   // )
  return in;
}

std::ostream& operator << (std::ostream& os, const Vector3f& rhs) {
  os << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
  return os;
}

std::istream& operator >> (std::istream& in, Vector3f& rhs) {
  in.ignore(1);    // (
  in >> rhs.x;
  in.ignore(1);    // ,
  in >> rhs.y;
  in.ignore (1);   // ,
  in >> rhs.z;
  in.ignore (1);   // )
  return in;
}

std::ostream& operator << (std::ostream& os, const Vector2f& rhs) {
  os << "(" << rhs.x << "," << rhs.y << ")";
  return os;
}

std::istream& operator >> (std::istream& in, Vector2f& rhs) {
  in.ignore(1);    // (
  in >> rhs.x;
  in.ignore(1);    // ,
  in >> rhs.y;
  in.ignore (1);   // )
  return in;
}

