#ifndef LIBUTILS_HPP 
#define LIBUTILS_HPP

#include <iostream>
#include <string>

class LibUtils {
public:
  bool isnum(const std::string &input);
  int stoi(std::string str);
};

#endif // LIBUTILS
