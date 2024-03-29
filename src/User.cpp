#include "User.hpp"
#include <iostream>

User::User()
    : _nickname(""), _username(""), _realname(""), _currentChannel(""), _fd(0),
      _joinedChannelCount(0), _pingTime(0), _state(User::NONE),
      _modeFlags(User::None), _passTryCount(0), _nonPassCommandCount(0),
      _nonPassNickUserCommandCount(0) {}

User::User(const int fd)
    : _nickname(""), _username(""), _realname(""), _currentChannel(""), _fd(fd),
      _joinedChannelCount(0), _pingTime(0), _state(User::NONE),
      _modeFlags(User::None), _passTryCount(0), _nonPassCommandCount(0),
      _nonPassNickUserCommandCount(0) {}

User &User::operator=(const User &user) {
  if (this != &user) {
    this->_nickname = user._nickname;
    this->_username = user._username;
    this->_realname = user._realname;
    this->_fd = user._fd;
    this->_joinedChannelCount = user._joinedChannelCount;
    this->_state = user._state;
    this->_modeFlags = user._modeFlags;
  }
  return (*this);
}

User::~User() {}

// setter
void User::setNickName(const std::string &nickname) {
  this->_nickname = nickname;
}
void User::setRealName(const std::string &realname) {
  this->_realname = realname;
}
void User::setUserName(const std::string &username) {
  this->_username = username;
}

void User::setCurrentChannel(const std::string &channel) {
  this->_currentChannel = channel;
}

void User::setPingTime(const std::time_t &time) { this->_pingTime = time; }

void User::incrementJoinedChannelCount() { this->_joinedChannelCount += 1; }
void User::decrementJoinedChannelCount() { this->_joinedChannelCount -= 1; }

void User::incrementPassTryCount() { this->_passTryCount += 1; }
void User::incrementNonPassCommandCount() { this->_nonPassCommandCount += 1; }
void User::incrementNonPassNickUserCommandCount() {
  this->_nonPassNickUserCommandCount += 1;
}

// getter
const std::string &User::getNickName() const { return this->_nickname; }
const std::string &User::getRealName() const { return this->_realname; }
const std::string &User::getUserName() const { return this->_username; }
const int &User::getFd() const { return this->_fd; }
int User::getJoinedChannelCount() const { return (this->_joinedChannelCount); }
const std::string &User::getCurrentChannel() const {
  return this->_currentChannel;
}
const std::time_t &User::getPingTime() const { return (this->_pingTime); }
const std::size_t &User::getPassTryCount() const {
  return (this->_passTryCount);
}
const std::size_t &User::getNonPassCommandCount() const {
  return (this->_nonPassCommandCount);
}
const std::size_t &User::getNonPassNickUserCommandCount() const {
  return (this->_nonPassNickUserCommandCount);
}

// mode
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

// state
void User::setState(RegisterState state, bool enable) {
  if (enable) {
    this->_state = static_cast<RegisterState>(this->_state | state);
  } else {
    this->_state = static_cast<RegisterState>(this->_state & ~state);
  }
}

User::RegisterState User::getState() const { return this->_state; }
