#ifndef  _LOG_
#define  _LOG_ 1

#include <string>
#include <iostream>

using std::endl;

#define log_debug std::cout << "debug: "
#define log_function std::cout << "function: "
#define log_success std::cout << "success: "
#define log_error std::cout << "error: "
#define log_warning std::cout << "warning: "
#define log_init std::cout << "init: "
#define log_init_multiple std::cout << "init_multiple: "
#define log_success_multiple std::cout << "success_multiple: "
#define log_debug_multiple std::cout << "debug_multiple: "
#define log_function_multiple std::cout << "function_multiple: "
#define log_realtime std::cout << "realtime: "

#endif /* _LOG_ */

