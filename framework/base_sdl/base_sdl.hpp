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

#ifndef _BASE_SDL_
#define _BASE_SDL_ 1

#include "../base.hpp"

//==============================================================================
//  Base_SDL
//==============================================================================
class Base_SDL : public Base {
public:
	Base_SDL() {}
	~Base_SDL() {}

	// init	
	void init();
	void close();
	bool update();
	
	// Timer	
	float get_sys_time() const;
	
	// Window 
	void set_caption(const char *title);
	void swap_buffers(void);
	void init_window( const int width, const int height, const bool fullscreen );
	void resize_window( const int width, const int height, const bool fullscreen ) {
	    init_window( width, height, fullscreen );
    }
    
    // input
    void set_mouse_position(int x, int y);
    void set_mouse_cursor_visibility(bool visibile);
};

#endif /* _BASE_SDL_ */

