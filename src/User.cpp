#include "User.hpp"
#include <iostream>

User::User(const std::string &nick, const std::string &realName) : _fd(0) {
  std::cout << nick << std::endl;
  std::cout << realName << std::endl;
}

User::~User() {}

void User::setMode(unsigned int mode, bool enable) {
  if (enable) {
    this->_modeFlags |= mode;
  } else {
    this->_modeFlags &= ~mode;
  }
}
bool User::hasMode(ModeFlags flag) const {
  return (this->_modeFlags & flag) != 0;
}

void User::setState(RegisterState state) {
  this->_state = static_cast<RegisterState>(this->_state | state);
}

User::RegisterState User::getState() const { return this->_state; }
