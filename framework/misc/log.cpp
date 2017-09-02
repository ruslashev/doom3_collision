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

#include "log.hpp"
#include "../math/vector.hpp"
#include <cstdarg>
//#include "../gui.hpp"

#define MAX_LENGTH 256

Logger logger;

//==============================================================================
//  Logger:Logger()
//==============================================================================
Logger::Logger() {
  logfile=(FILE* ) NULL;

  //Clear the log file contents
  logfile=fopen("log.txt", "wb");
  fclose(logfile);

  //	m_console = (Overlay_console *)NULL;

  function.init( this, -1, true );
  success.init( this, 0, true );
  warning.init( this, 1, true );
  error.init( this, 2, true );
  debug.init( this, 3, true );
  init.init( this, 4, true );
  realtime.init( this, 5, false );

  m_indent = 0;

  init << "Logger initialization" << endl;
  debug << "by Reinder Nijhoff (reinder@infi.nl)" << endl;
  debug << endl;
}

//==============================================================================
//  Logger:~Logger()
//==============================================================================
Logger::~Logger() {
  if(logfile) {
    fclose(logfile);
  }
}

//==============================================================================
//  Logger:output()
//==============================================================================
void Logger::output(bool to_file, int level, char * text,...) {
#define MAX_LENGTH 256

  va_list arg_list;
  char temp[MAX_LENGTH+1];
  Color m_color;

  if(m_indent<0) m_indent=0;

  for(int i=0; i<m_indent*2; ++i) {
    temp[i] = ' ';
  }

  va_start(arg_list, text);
  vsnprintf( &(temp[m_indent*2]), MAX_LENGTH-(m_indent*2), text, arg_list);
  va_end(arg_list);

  // Write to console
  switch( level) {
    case 5:	 	m_color = white;
              break;
    case -1:    m_color = yellow;
                break;
    case 0:	    m_color = green;
                break;
    case 1:	 	m_color = orange;
              break;
    case 2:		m_color = red;
              break;
    case 3:	 	m_color = white;
              break;
    case 4:	    m_color = yellow;
                break;
  }

  // Write file
  if(to_file && ((logfile=fopen("log.txt", "a+"))!=NULL)) {
    switch( level) {
      case -1:	fprintf(logfile, "(+) "); // function
                break;
      case 0:	 	fprintf(logfile, "(-) "); // succes
                break;
      case 1:	 	fprintf(logfile, "(!) "); // warning
                break;
      case 2:		fprintf(logfile, "<!> "); // error
                break;
      case 3:	 	fprintf(logfile, "( ) "); // debug
                break;
      case 4:     fprintf(logfile, "(+) "); // function
                  break;
    }

    fprintf(logfile, temp);
    putc('\n', logfile);
    fclose(logfile);
  }

  //Write to console
  /*	if(m_console!=NULL) {
      m_console->text()->print(m_color, temp);
      if(m_console->get_direct_render()) m_console->direct_render();
      }*/
}

//==============================================================================
//  Logstreambuf::overflow()
//==============================================================================
int Logstreambuf::overflow(int c) {
  if (c == EOF || c == '\n') {
    m_logger->output(m_to_file, m_level, (char *)lnbuffer.c_str() );
    if(m_level == -1) {
      m_logger->begin_function();
    }
    if( (m_level == 0) || (m_level == 2) ) {
      m_logger->end_function();
    }
    lnbuffer = "";
  } else {
    lnbuffer += (char) c;
  }
  return 1;
}

//==============================================================================
//  set_console()
//==============================================================================
/*void Logger::set_console(Overlay_console* n_console) {
  m_console = n_console;
  }*/

//==============================================================================
//  Logstream::init()
//==============================================================================
void Logstream::init(Logger* n_logger, int n_level, bool to_file) {
  m_buffer.init(n_logger, n_level, to_file);
}

//==============================================================================
//  Logstreambuf::init()
//==============================================================================
void Logstreambuf::init(Logger* n_logger, int n_level, bool to_file) {
  m_logger = n_logger;
  m_level = n_level;
  m_to_file = to_file;
}

