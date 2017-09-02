#ifndef _BASE_
#define _BASE_ 1

class Base {
public:
	Base();
	~Base() {};
 	
	// init
	virtual void init()=0;
	virtual void close()=0;
	
	// Timer	
	void update_timer();
	void reset_timer();

	inline float get_fps() const { return m_fps; }
	inline float get_frame_interval() const { return m_frame_interval; }
	virtual float get_sys_time() const { return 0.0f; }	
	
	// Window 
	virtual void set_caption(const char *title)=0;
	virtual void swap_buffers(void)=0;
	virtual void resize_window( int width, int height, bool fullscreen )=0;
	virtual void init_window( int width, int height, bool fullscreen )=0;
	
	int get_window_width(void) const { return m_width; }
	int get_window_height(void) const { return m_height; }	
	bool get_fullscreen(void) const { return m_fullscreen; }
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
private:
};

extern Base* base;

#endif /* _BASE_ */
