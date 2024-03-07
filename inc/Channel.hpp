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

  // getter
  const std::string &getChannelName() const;
  const std::map<User *, unsigned int> &getUserStatus() const;

  // user
  void addUser(User &user);
  void removeUser(User &user);
  int userNum() const;

  // user status
  void setUserStatus(User &user, UserStatusFlags status, bool enable);
  bool hasUserStatus(User &user, const UserStatusFlags status) const;

  // topic
  void setTopic(const std::string &topic);
  const std::string &getTopic() const;
  const long &getTopicSetAt() const;

  // channel mode
  void setChannelMode(const ChannelModeFlags flag, bool enable);
  bool hasChannleMode(const ChannelModeFlags flag) const;

  // k flag
  void setKey(const std::string &key);
  const std::string &getKey() const;

  // l flag
  void setUserLimit(int limit);
  int getUserLimit() const;

  // b flag
  void addBanMask(const std::string &mask);
  void removeBanMask(const std::string &mask);
  bool isBanned(const std::string &mask) const;

  // e flag
  void addExceptionMask(const std::string &mask);
  void removeExceptionMask(const std::string &mask);
  bool hasException(const std::string &mask) const;

  // I flag
  void addInvitationMask(const std::string &mask);
  void removeInvitationMask(const std::string &mask);
  bool isInvited(const std::string &mask) const;

private:
  std::string _channelName;

  std::set<User *> _users;
  std::map<User *, unsigned int> _userStatus; // nickname, userStatus

  std::string _topic;
  long _topicSetAt;

  unsigned int _channelModeFlag;
  std::string _channelKey;           // k flag
  int _userLimit;                    // l flag
  std::set<std::string> _banMasks;        // b flag
  std::set<std::string> _exceptionMasks;  // e flag
  std::set<std::string> _invitationMasks; // I flag

  // setTopic func
  long getCurrentUnixTimestamp();
};

#endif
