#include "User.hpp"
#include <iostream>

User::User(const std::string &nick, const std::string &realName) : userFd(0) {
  std::cout << nick << std::endl;
  std::cout << realName << std::endl;
}

User::~User() {}
