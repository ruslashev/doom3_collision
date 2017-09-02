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

#ifndef _BASE_
#define _BASE_ 1

#define NUM_KEYS 315

//==============================================================================
//  Base
//==============================================================================
class Base {
public:
  Base();
  ~Base() {};

  // init
  virtual void init()=0;
  virtual void close()=0;
  virtual bool update()=0;

  // Timer
  void update_timer();
  void reset_timer();

  inline float get_fps() const { return m_fps; }
  inline float get_frame_interval() const { return m_frame_interval; }
  virtual float get_sys_time() const { return 0.0f; }

  // Window
  virtual void set_caption(const char *title)=0;
  virtual void swap_buffers(void)=0;
  virtual void resize_window( const int width, const int height, const bool fullscreen )=0;
  virtual void init_window( const int width, const int height, const bool fullscreen )=0;

  int get_window_width(void) const { return m_width; }
  int get_window_height(void) const { return m_height; }
  bool get_fullscreen(void) const { return m_fullscreen; }

  // Keyboard and Mouse
  inline bool is_key_pressed( int key ) { return m_keys[ key ]; }
  inline bool is_key_released( int key ) { return m_keys_released[ key ]; }

  inline int get_mouse_x() { return m_mouse_x; }
  inline int get_mouse_y() { return m_mouse_y; }
  inline unsigned short int get_mouse_buttons() { return m_mouse_buttons; }

  virtual void set_mouse_position(int x, int y) {}
  virtual void set_mouse_cursor_visibility(bool visibile) {};
protected:
  // Window dimensions
  int m_width, m_height;
  bool m_fullscreen;

  // Timer
  float m_fps;
  float m_frame_interval;
  float m_frame_time;
  float m_last_time;
  int m_fps_counter;

  // Keyboard and Mouse
  bool m_keys_last_frame[NUM_KEYS];
  bool m_keys[NUM_KEYS];
  bool m_keys_released[NUM_KEYS];

  int m_mouse_x;
  int	m_mouse_y;

  unsigned short int m_mouse_buttons;
private:
};

//==============================================================================
//  Keyboard Layout
// 	todo: make this base specific, Base_SDL values declared now...
//==============================================================================
const int KEY_UNKNOWN      = 0;
const int KEY_BACKSPACE    = 8;
const int KEY_TAB		   = 9;
const int KEY_CLEAR		   = 12;
const int KEY_RETURN	   = 13;
const int KEY_PAUSE		   = 19;
const int KEY_ESCAPE	   = 27;
const int KEY_SPACE		   = 32;
const int KEY_PLUS		   = 43;
const int KEY_COMMA		   = 44;
const int KEY_MINUS		   = 45;
const int KEY_PERIOD	   = 46;
const int KEY_SLASH		   = 47;
const int KEY_0	  		   = 48;
const int KEY_1			   = 49;
const int KEY_2			   = 50;
const int KEY_3			   = 51;
const int KEY_4			   = 52;
const int KEY_5			   = 53;
const int KEY_6			   = 54;
const int KEY_7			   = 55;
const int KEY_8			   = 56;
const int KEY_9			   = 57;
const int KEY_COLON		   = 58;
const int KEY_SEMICOLON	   = 59;
const int KEY_LESS		   = 60;
const int KEY_EQUALS 	   = 61;
const int KEY_GREATER	   = 62;
const int KEY_QUESTION	   = 63;
const int KEY_LEFTBRACKET  = 91;
const int KEY_BACKSLASH	   = 92;
const int KEY_RIGHTBRACKET = 93;
const int KEY_CARET		   = 94;
const int KEY_UNDERSCORE   = 95;
const int KEY_BACKQUOTE	   = 96;
const int KEY_A			   = 97;
const int KEY_B			   = 98;
const int KEY_C			   = 99;
const int KEY_D			   = 100;
const int KEY_E			   = 101;
const int KEY_F			   = 102;
const int KEY_G			   = 103;
const int KEY_H			   = 104;
const int KEY_I			   = 105;
const int KEY_J			   = 106;
const int KEY_K			   = 107;
const int KEY_L			   = 108;
const int KEY_M			   = 109;
const int KEY_n			   = 110;
const int KEY_O			   = 111;
const int KEY_P			   = 112;
const int KEY_Q			   = 113;
const int KEY_R			   = 114;
const int KEY_S			   = 115;
const int KEY_T			   = 116;
const int KEY_U			   = 117;
const int KEY_V			   = 118;
const int KEY_W			   = 119;
const int KEY_X			   = 120;
const int KEY_Y			   = 121;
const int KEY_Z			   = 122;
const int KEY_DEL		   = 127;
/* Numeric keypad */
const int KEY_KP0		   = 256;
const int KEY_KP1		   = 257;
const int KEY_KP2	       = 258;
const int KEY_KP3		   = 259;
const int KEY_KP4		   = 260;
const int KEY_KP5		   = 261;
const int KEY_KP6		   = 262;
const int KEY_KP7		   = 263;
const int KEY_KP8		   = 264;
const int KEY_KP9		   = 265;
const int KEY_KP_PERIOD	   = 266;
const int KEY_KP_DIVIDE	   = 267;
const int KEY_KP_MULTIPLY  = 268;
const int KEY_KP_MINUS	   = 269;
const int KEY_KP_PLUS	   = 270;
const int KEY_KP_ENTER	   = 271;
const int KEY_KP_EQUALS	   = 272;
/* Arrows + Home/End pad */
const int KEY_UP		   = 273;
const int KEY_DOWN		   = 274;
const int KEY_RIGHT		   = 275;
const int KEY_LEFT		   = 276;
const int KEY_INSERT	   = 277;
const int KEY_HOME		   = 278;
const int KEY_END		   = 279;
const int KEY_PAGEUP	   = 280;
const int KEY_PAGEDOWN	   = 281;
/* Function keys */
const int KEY_F1		   = 282;
const int KEY_F2		   = 283;
const int KEY_F3		   = 284;
const int KEY_F4		   = 285;
const int KEY_F5		   = 286;
const int KEY_F6		   = 287;
const int KEY_F7		   = 288;
const int KEY_F8		   = 289;
const int KEY_F9		   = 290;
const int KEY_F10		   = 291;
const int KEY_F11		   = 292;
const int KEY_F12		   = 293;
const int KEY_F13		   = 294;
const int KEY_F14		   = 295;
const int KEY_F15		   = 296;
/* Key state modifier keys */
const int KEY_NUMLOCK	   = 300;
const int KEY_CAPSLOCK	   = 301;
const int KEY_SCROLLOCK	   = 302;
const int KEY_RSHIFT	   = 303;
const int KEY_LSHIFT	   = 304;
const int KEY_RCTRL		   = 305;
const int KEY_LCTRL		   = 306;
const int KEY_RALT		   = 307;
const int KEY_LALT		   = 308;
const int KEY_RMETA		   = 309;
const int KEY_LMETA		   = 310;
const int KEY_LSUPER	   = 311;
const int KEY_RSUPER	   = 312;
const int KEY_MODE		   = 313;
const int KEY_COMPOSE	   = 314;

extern Base* base;

#endif /* _BASE_ */
