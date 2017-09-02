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

#include "base_sdl.hpp"
#include "../misc/log.hpp"

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

//==============================================================================
//  Base_SDL::init()
//==============================================================================
void Base_SDL::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    log_error << "Error initialising SDL - " << SDL_GetError() << endl;
    exit(0);
  }
}

//==============================================================================
//  Base_SDL::close()
//==============================================================================
void Base_SDL::close() {
  SDL_Quit();
}

//==============================================================================
//  Base_SDL::init_window()
//==============================================================================
void Base_SDL::init_window( const int width, const int height, const bool fullscreen ) {
  m_width = width;
  m_height = height;
  m_fullscreen = fullscreen;

  // inform the user
  log_function << "Window initialization" << endl;

  const SDL_VideoInfo* m_VideoInfo;
  int rgb_size[3];
  bool fsaa = false;
  int value;

  // Retrieve current video info
  if ((m_VideoInfo = SDL_GetVideoInfo()) == 0) {
    log_error << "Video query failed - " << SDL_GetError() << endl;
    exit(0);
  }

  /*	if ( fsaa ) {
      SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
      SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, fsaa );
      }*/

  // Set the video mode
  if (!SDL_SetVideoMode(m_width, m_height, m_VideoInfo->vfmt->BitsPerPixel, SDL_OPENGL | m_fullscreen)) {
    log_error << "Video mode set failed - " << SDL_GetError() << endl;
    exit(0);
  }

  SDL_Surface *screen = SDL_GetVideoSurface();
  m_width = screen->w;
  m_height = screen->h;

  SDL_GL_GetAttribute( SDL_GL_BUFFER_SIZE, &value );
  log_debug << "Screen BPP : " <<  value << endl;
  log_debug << "Vendor     : " <<  glGetString( GL_VENDOR ) << endl;
  log_debug << "Renderer   : " <<  glGetString( GL_RENDERER ) << endl;
  log_debug << "Version    : " <<  glGetString( GL_VERSION ) << endl;
  //	log_debug << "Extensions : " << glGetString( GL_EXTENSIONS ) << endl;

  log_debug << "Size       : " <<  get_window_width() << " x " << get_window_height() << endl;
  log_debug << "Fullscreen : " <<  get_fullscreen() << endl;

  SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &value );
  log_debug << "SDL_GL_RED_SIZE    : requested " <<  rgb_size[0] << ", got " << value << endl;
  SDL_GL_GetAttribute( SDL_GL_GREEN_SIZE, &value );
  log_debug << "SDL_GL_GREEN_SIZE  : requested " <<  rgb_size[1] << ", got " << value << endl;
  SDL_GL_GetAttribute( SDL_GL_BLUE_SIZE, &value );
  log_debug << "SDL_GL_BLUE_SIZE   : requested " <<  rgb_size[2] << ", got " << value << endl;
  SDL_GL_GetAttribute( SDL_GL_DEPTH_SIZE, &value );
  log_debug << "SDL_GL_DEPTH_SIZE  : requested " << m_VideoInfo->vfmt->BitsPerPixel << ", got " << value << endl;
  SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &value );
  log_debug << "SDL_GL_DOUBLEBUFFER: requested 1, got " << value << endl;
  /*	if ( fsaa ) {
      SDL_GL_GetAttribute( SDL_GL_MULTISAMPLEBUFFERS, &value );
      log_debug << "SDL_GL_MULTISAMPLEBUFFERS: requested 1, got " << value << endl;
      SDL_GL_GetAttribute( SDL_GL_MULTISAMPLESAMPLES, &value );
      log_debug << "SDL_GL_MULTISAMPLESAMPLES: requested " << fsaa << ", got " << value << endl;
      }*/
  log_success << "Window initialization successful" << endl;
}

//==============================================================================
//  Base_SDL::swap_buffers()
//==============================================================================
void Base_SDL::swap_buffers(void) {
  glFlush();
  SDL_GL_SwapBuffers();
}

//==============================================================================
//  Base_SDL::set_caption()
//==============================================================================
void Base_SDL::set_caption(const char *title) {
  SDL_WM_SetCaption(title, "");
}

//==============================================================================
//  Base_SDL::get_sys_time()
//==============================================================================
float Base_SDL::get_sys_time() const {
  return SDL_GetTicks() * 0.001f;
}

//==============================================================
// Base_SDL::update()
//==============================================================
bool Base_SDL::update() {
  // Timer
  update_timer();
  // Backup current frame keys
  memcpy(m_keys_last_frame, m_keys, sizeof(m_keys));

  SDL_Event event;

  // Retrieve all events from the queue
  while( SDL_PollEvent(&event) ) {
    switch (event.type) {
      // Handle key presses
      case (SDL_KEYDOWN):	m_keys[event.key.keysym.sym] = true;
                          break;
      case (SDL_KEYUP):	m_keys[event.key.keysym.sym] = false;
                        break;
                        // Todo: handle program exit
      case (SDL_QUIT):	return false;
                        break;
    }
  }

  // Set the key released states
  for (int i = 0; i < SDLK_LAST; i++) {
    m_keys_released[i] = (m_keys_last_frame[i] ^ m_keys[i]) & m_keys_last_frame[i];
  }
  // Get the current mouse state
  m_mouse_buttons = SDL_GetMouseState(&m_mouse_x, &m_mouse_y);

  /* default key-functions */
  if (m_keys[SDLK_ESCAPE] || m_keys[SDLK_q]) {
    return false;
  }

  return true;
}

//==============================================================
//  Base_SDL::set_mouse_position()
//==============================================================
void Base_SDL::set_mouse_position(int x, int y) {
  SDL_WarpMouse(x, y);
}

//==============================================================
// Base_SDL::set_mouse_cursor_visibility()
//==============================================================
void Base_SDL::set_mouse_cursor_visibility(bool visibile) {

}
