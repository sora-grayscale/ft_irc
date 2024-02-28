#include "User.hpp"
#include <iostream>

User::User()  {}

User::User(const int fd) : _fd(fd) {}

User::User(const std::string &nick, const std::string &realName) {
  std::cout << nick << std::endl;
  std::cout << realName << std::endl;
}

User &User::operator=(const User &user) {
  if (this != &user) {
    this->_nickname = user._nickname;
    this->_username = user._username;
    this->_realname = user._realname;
    this->_fd = user._fd;
    this->_state = user._state;
    this->_modeFlags = user._modeFlags;
  }
  return (*this);
}

User::~User() {}
