#ifndef PYRA_ERROR_HPP
#define PYRA_ERROR_HPP

#include <cstdlib>
#include <iostream>
#include <stdexcept>
namespace pyra {
  
  // Error class that aborts before anything gets thrown.
  class abort_error : public std::logic_error {
  public:
    abort_error(const std::string& s) : std::logic_error(s) {
      std::cerr << s << '\n';
      std::abort();
    }
    
    abort_error(const char* s) : std::logic_error(s) {
      std::cerr << s << '\n';
      std::abort();
    }
    
    abort_error() : std::logic_error("Nope!") {
      std::cerr << "Nope!" << '\n';
      std::abort();
    }
  };
}

#endif