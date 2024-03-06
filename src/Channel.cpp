#include "Channel.hpp"

// user
// void addUser(User &user) {
//   this->_users.insert(user);
// }

// void removeUser(User &user) {}
// 
// // user status
// void setUserStatus(const std::string &nickname, UserStatusFlags status,
//                    bool enable) {}
// void addUserStatus(const std::string &nickname, UserStatusFlags status) {}
// void removeUserStatus(const std::string &nickname, UserStatusFlags status) {}
// bool hasUserStatus(const std::string &nickname, UserStatusFlags status) const {}
// 
// // topic
// void setTopic(const std::string &topic) {}
// 
// // channel mode
// void setChannelMode(const ChannelModeFlags flag, bool enable) {}
// bool hasChannleMode(const ChannelModeFlags flag) const {}

// k flag
void Channel::setKey(const std::string &key) { this->_channelKey = key; }

const std::string &Channel::getKey() const { return (this->_channelKey); }

// l flag
void Channel::setUserLimit(int limit) { this->_userLimit = limit; }

int Channel::getUserLimit() const { return (this->_userLimit); }

// // b flag
// void addBanMask(const std::string &mask) {}
// void removeBanMask(const std::string &mask) {}
// bool isBanned(const std::string &mask) const {}
// 
// // e flag
// void addExceptionMask(const std::string &mask) {}
// void removeExceptionMask(const std::string &mask) {}
// bool hasException(const std::string &mask) const {}
// 
// // I flag
// void addInvitationMask(const std::string &mask) {}
// void removeInvitationMask(const std::string &mask) {}
// bool isInvited(const std::string &mask) const {}
