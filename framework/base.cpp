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

#include "base.hpp"
#include "misc/log.hpp"
#include <cstring>

//==============================================================================
//  Base::Base()
//==============================================================================
Base::Base() {
  reset_timer();
  memset(m_keys, 0, sizeof(m_keys));
}

//==============================================================================
//  Base::update_timer()
//==============================================================================
void Base::update_timer() {
  float current_time = get_sys_time();

  if(m_frame_time<0) {
    m_last_time = get_sys_time();
    m_frame_time = get_sys_time();
  }

  m_frame_interval = current_time - m_frame_time;
  m_frame_time = current_time;

  ++m_fps_counter;

  if( current_time - m_last_time > 1.0f ) {
    m_last_time = current_time;
    m_fps = m_fps_counter;
    m_fps_counter=0;
    // log_realtime << m_fps << endl;
  }
}

//==============================================================================
//  Base::reset_timer()
//==============================================================================
void Base::reset_timer() {
  m_frame_time = -1;
  m_fps_counter = 0;
  m_fps = 0;
}

