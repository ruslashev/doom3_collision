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

#ifndef  _LOG_
#define  _LOG_ 1

//class Overlay_console;

#include <string>
#include <iostream>

#define endl std::endl

class Logger;

//==============================================================================
//  Logstreambuf
//==============================================================================
class Logstreambuf : public std::streambuf {
    public:
        Logstreambuf() { m_to_file=true; };
        void init(Logger* n_logger, int n_level, bool to_file);    
    protected:
        virtual int overflow(int c);
    private:
        std::string lnbuffer;
        Logger* m_logger;
        int m_level;
        bool m_to_file;
};

//==============================================================================
//  Logstream
//==============================================================================
class Logstream : public std::ostream {
    public:
        Logstream() : std::ostream(&m_buffer) {};
        void init(Logger* n_logger, int n_level, bool to_file);       
    private:
     	Logstreambuf m_buffer;
};

//==============================================================================
//  Logger
//==============================================================================
class Logger {
public:
	Logger();
	~Logger();

	//Output functions 
	Logstream function; // -1
	Logstream success; // 0
 	Logstream warning; // 1
	Logstream error; // 2
  	Logstream debug; // 3
   	Logstream init; // 4
   	Logstream realtime; // 5
   	
   	// intend functions
   	void begin_function() { ++m_indent; }
   	void end_function() { --m_indent; }
   	
	void output(bool to_file, int level, char * text, ...); 	
	/* use console */
//	void set_console(Overlay_console* n_console);
private:
	FILE* logfile;
//	Overlay_console* m_console;
	int m_indent;
};

/* log functions called once */
#ifndef log_debug
#define log_debug logger.debug 
#endif

#ifndef log_function
#define log_function logger.function
#endif

#ifndef log_success
#define log_success logger.success
#endif

#ifndef log_error
#define log_error logger.error
#endif

#ifndef log_warning
#define log_warning logger.warning
#endif

#ifndef log_init
#define log_init logger.init 
#endif

/* log functions called often */
#ifndef log_init_multiple
#define log_init_multiple logger.init 
#endif

#ifndef log_success_multiple
#define log_success_multiple logger.success
#endif

#ifndef log_debug_multiple
#define log_debug_multiple logger.debug 
#endif

#ifndef log_function_multiple
#define log_function_multiple logger.function 
#endif

#ifndef log_realtime
#define log_realtime logger.realtime
#endif

extern Logger logger;

#endif /* _LOG_ */

