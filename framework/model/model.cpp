#include "base.hpp"

#include "base.hpp"
#include "misc/log.hpp"

//==============================================================================
// Timer
//==============================================================================
Base::Base() {
  reset_timer();
}

//==============================================================================
// update
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
    log_realtime << m_fps << endl;
  }
}

//==============================================================================
// reset
//==============================================================================
void Base::reset_timer() {
  m_frame_time = -1;
  m_fps_counter = 0;
  m_fps = 0;
}

