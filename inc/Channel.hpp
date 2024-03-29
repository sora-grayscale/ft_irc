#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"
#include <climits>
#include <ctime>
#include <map>
#include <set>
#include <string>

class Channel {
public:
  Channel();
  Channel(const std::string &channelName);
  Channel(const std::string &channelName, const std::string &key);
  ~Channel();

  enum UserStatusFlags {
    Normal = 0,
    Creator = 1 << 0,
    Operator = 1 << 1,
    Voice = 1 << 2
  };

  enum ChannelModeFlags {
    None = 0,
    ChannelCreator = 1 << 0,  // O
    ChannelOperator = 1 << 1, // o
    ChannelVoice = 1 << 2,    // v
    Anonymous = 1 << 3,       // a
    InviteOnly = 1 << 4,      // i
    Moderated = 1 << 5,       // m
    NoOutside = 1 << 6,       // n
    Quiet = 1 << 7,           // q
    Private = 1 << 8,         // p
    Secret = 1 << 9,          // s
    ServerReop = 1 << 10,     // r
    TopicOpOnly = 1 << 11,    // t
    Key = 1 << 12,            // k 特別扱いが必要
    Limit = 1 << 13,          // l 特別扱いが必要
    BanMask = 1 << 14,        // b 特別扱いが必要
    ExceptionMask = 1 << 15,  // e 特別扱いが必要
    InvitationMask = 1 << 16  // I 特別扱いが必要
  };

  // chat
  void broadcastMessage(const std::string &message, const User &sender) const;

  // getter
  const std::string &getChannelName() const;
  const std::time_t &getChannelCreatedTime() const;

  // user
  void addUser(User &user);
  void removeUser(User &user);
  std::size_t userNum() const;
  std::size_t getVisibleUsrNum(const User &user) const;
  std::set<User *>::const_iterator getUserBegin() const;
  std::set<User *>::const_iterator getUserEnd() const;
  bool isUserInChannel(const User &user) const;
  bool isUserInChannel(const std::string &nick) const;

  // user status
  void setUserStatus(User &user, UserStatusFlags status, bool enable);
  bool hasUserStatus(User &user, const UserStatusFlags status) const;
  Channel::UserStatusFlags getUserStatus(User &user) const;

  // topic
  void setTopic(const std::string &topic, const std::string &nick);
  const std::string &getTopic() const;
  const std::string &getTopicSetUser() const;
  const std::time_t &getTopicSetAt() const;

  // channel mode
  void setChannelMode(const ChannelModeFlags flag, bool enable);
  bool hasChannleMode(const ChannelModeFlags flag) const;

  // k flag
  void setKey(const std::string &key);
  const std::string &getKey() const;

  // l flag
  void setUserLimit(int limit);
  std::size_t getUserLimit() const;

  // b flag
  void addBanMask(const std::string &mask);
  void removeBanMask(const std::string &mask);
  bool isBanned(const std::string &mask) const;
  std::size_t sizeOfBanMask() const;
  std::set<std::string>::const_iterator getBanMaskBegin() const;
  std::set<std::string>::const_iterator getBanMaskEnd() const;

  // e flag
  void addExceptionMask(const std::string &mask);
  void removeExceptionMask(const std::string &mask);
  bool hasException(const std::string &mask) const;
  std::size_t sizeOfExceptionMask() const;
  std::set<std::string>::const_iterator getExceptionMaskBegin() const;
  std::set<std::string>::const_iterator getExceptionMaskEnd() const;

  // I flag
  void addInvitationMask(const std::string &mask);
  void removeInvitationMask(const std::string &mask);
  bool isInvited(const std::string &mask) const;
  std::size_t sizeOfInvitationMask() const;
  std::set<std::string>::const_iterator getInvitationMaskBegin() const;
  std::set<std::string>::const_iterator getInvitationMaskEnd() const;

  // delete flag
  bool isDelete() const;

private:
  std::string _channelName;
  std::time_t _channelCreatedTime;

  std::set<User *> _users;
  std::map<User *, unsigned int> _userStatus; // nickname, userStatus

  std::string _topic;
  std::string _topicSetUser;
  std::time_t _topicSetAt;

  unsigned int _channelModeFlag;
  std::string _channelKey;                // k flag
  std::size_t _userLimit;                 // l flag
  std::set<std::string> _banMasks;        // b flag
  std::set<std::string> _exceptionMasks;  // e flag
  std::set<std::string> _invitationMasks; // I flag

  bool _delete;

  // setTopic func
  std::time_t getCurrentUnixTimestamp();
};

#endif
