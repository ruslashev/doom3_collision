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

#ifndef _CONTROLLER_
#define _CONTROLLER_ 1

#include "../math/matrix.hpp"

//==============================================================================
//  Controller
//==============================================================================
class Controller {
public:
  Controller() {}
  ~Controller() {}

  virtual void update() {}

  virtual void set_position   (const Vector3f & position)       { m_position = position; };
  virtual void set_orientation(const Orientation & orientation) { m_orientation = orientation; };

  const Position    & get_position()    const { return m_position;    };
  const Orientation & get_orientation() const { return m_orientation; };
protected:
  Position    m_position;
  Orientation m_orientation;
};

//==============================================================================
//  Controllable_object
//==============================================================================
class Controllable_object {
public:
  Controllable_object() { m_controlled = false; }
  ~Controllable_object() {}

  virtual void update() { if(m_controlled) m_controller->update(); }

  const Vector3f & get_position() const {
    return (m_controlled ? m_controller->get_position() : m_position);
  }
  const Orientation & get_orientation() const {
    return (m_controlled ? m_controller->get_orientation() : m_orientation);
  }

  const bool is_controlled() { return m_controlled; }

  void set_controlled(bool controlled) { m_controlled = controlled; }
  void set_controller(Controller* controller) { m_controller = controller; }
  Controller* get_controller() { return m_controller; }
protected:
  bool m_controlled;

  Controller* m_controller;
  Position    m_position;
  Orientation m_orientation;
};

#endif /* _CONTROLLER_ */

