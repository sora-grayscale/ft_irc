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

void User::setState(RegisterState state, bool enable) {
  if (enable) {  
    this->_state = static_cast<RegisterState>(this->_state | state);  
  } else {  
    this->_state = static_cast<RegisterState>(this->_state & ~state);  
  }  
 }  

User::RegisterState User::getState() const { return this->_state; }

const int &User::getFd() const { return this->_fd; }

const std::string &User::getNickName() const { return this->_nickname; }
const std::string &User::getRealName() const { return this->_realname; }
const std::string &User::getUserName() const { return this->_username; }

void User::setNickName(const std::string &nickname) {
  this->_nickname = nickname;
}
void User::setRealName(const std::string &realname) {
  this->_realname = realname;
}
void User::setUserName(const std::string &username)
{
  this->_username = username;
}
