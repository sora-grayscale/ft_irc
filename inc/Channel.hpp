#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"
#include <map>
#include <set>
#include <string>

class Channel {
public:
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

  void addUser(User &user);
  void removeUser(User &user);

  void setTopic(const std::string &topic);

  // user status
  void setUserStatus(const std::string &nickname, UserStatusFlags status,
                     bool enable);
  void addUserStatus(const std::string &nickname,
                     UserStatusFlags status); // 上とほぼ一緒
  void removeUserStatus(const std::string &nickname, UserStatusFlags status);
  bool hasUserStatus(const std::string &nickname, UserStatusFlags status) const;

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
  // std::map <std::string nickname, User &user> users;
  std::map<std::string, User *> users;
  std::string topic;

  // std::map<std::string nickname, unsigned int userStatus> userStatus;
  std::map<std::string, unsigned int> userStatus;

  unsigned int channelModeFlags;
  std::string channelKey;                // k flag
  int userLimit;                         // l flag
  std::set<std::string> banMasks;        // b flag
  std::set<std::string> exceptionMasks;  // e flag
  std::set<std::string> invitationMasks; // I flag
};
#endif
