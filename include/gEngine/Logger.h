#ifndef LOGGER
#define LOGGER
#include <iostream>
#include <string>
namespace Logger{
  inline void log(const std::string& name, const std::string& msg) {
    std::cout << "\033[32m[LOG BY " << name << "]: " << msg << "\033[0m \n";
  }

  inline void log_err(const std::string& name, const std::string& msg){
    std::cout << "\033[32m[ERROR BY " << name << "]: " << msg << "\033[0m \n";
  }
}
#endif
