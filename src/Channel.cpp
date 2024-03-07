#include "Channel.hpp"

// constructor
Channel::Channel()
    : _channelName(""), _topic(""), _topicSetAt(0), _channelModeFlag(0),
      _channelKey(""), _userLimit(INT_MAX) {}

// destructor
Channel::~Channel() {}

// getter
const std::string &Channel::getChannelName() const {
  return (this->_channelName);
}

const std::map<User *, unsigned int> &Channel::getUserStatus() const {
  return (this->_userStatus);
}

// user
void Channel::addUser(User &user) { this->_users.insert(&user); }
void Channel::removeUser(User &user) { this->_users.erase(&user); }

// user status
void Channel::setUserStatus(User &user, UserStatusFlags status, bool enable) {
  unsigned int &userStatus = this->_userStatus.at(&user);
  if (enable) {
    userStatus |= status;
  } else {
    userStatus &= ~status;
  }
}

bool Channel::hasUserStatus(User &user, const UserStatusFlags status) const {
  if ((this->_userStatus.at(&user) & status) == 1) {
    return (true);
  }
  return (false);
}

// topic
void Channel::setTopic(const std::string &topic) { this->_topic = topic; }

// // channel mode
void Channel::setChannelMode(const ChannelModeFlags flag, bool enable) {
  if (enable) {
    this->_channelModeFlag |= flag;
  } else {
    this->_channelModeFlag &= ~flag;
  }
}

bool Channel::hasChannleMode(const ChannelModeFlags flag) const {
  if ((this->_channelModeFlag & flag) == 1) {
    return (true);
  } else {
    return (false);
  }
}

// k flag
void Channel::setKey(const std::string &key) { this->_channelKey = key; }

const std::string &Channel::getKey() const { return (this->_channelKey); }

// l flag
void Channel::setUserLimit(int limit) { this->_userLimit = limit; }

int Channel::getUserLimit() const { return (this->_userLimit); }

// b flag
void Channel::addBanMask(const std::string &mask) {
  this->_banMasks.insert(mask);
}

void Channel::removeBanMask(const std::string &mask) {
  this->_banMasks.erase(mask);
}

bool Channel::isBanned(const std::string &mask) const {
  if (this->_banMasks.find(mask) != this->_banMasks.end()) {
    return (true);
  } else {
    return (false);
  }
}

// e flag
void Channel::addExceptionMask(const std::string &mask) {
  this->_exceptionMasks.insert(mask);
}

void Channel::removeExceptionMask(const std::string &mask) {
  this->_exceptionMasks.erase(mask);
}

bool Channel::hasException(const std::string &mask) const {
  if (this->_exceptionMasks.find(mask) != this->_exceptionMasks.end()) {
    return (true);
  } else {
    return (false);
  }
}

// // I flag
void Channel::addInvitationMask(const std::string &mask) {
  this->_invitationMasks.insert(mask);
}

void Channel::removeInvitationMask(const std::string &mask) {
  this->_invitationMasks.erase(mask);
}

bool Channel::isInvited(const std::string &mask) const {
  if (this->_invitationMasks.find(mask) != this->_invitationMasks.end()) {
    return (true);
  } else {
    return (false);
  }
}

// func
long Channel::getCurrentUnixTimestamp() {
  std::time_t now = std::time(NULL);
  return (static_cast<long>(now));
}
