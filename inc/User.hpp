#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
public:
  enum RegisterState {
    NONE = 0,
    PASS = 1,
    NICK = 2,
    USER = 4,
    REGISTERD = PASS | NICK | USER
  };

  enum ModeFlags {
    None = 0,
    Away = 1 << 0,          // a
    Invisible = 1 << 1,     // i
    Wallops = 1 << 2,       // w
    Restricted = 1 << 3,    // r
    Operator = 1 << 4,      // o
    LocalOperator = 1 << 5, // O
    ServerNotices = 1 << 6  // s
  };

  User();
  User(const int fd);
  User &operator=(const User &user);
  ~User();

  // setter
  void setNickName(const std::string &nickname);
  void setRealName(const std::string &realname);
  void setUserName(const std::string &username);

  //getter
  const std::string &getNickName() const;
  const std::string &getRealName() const;
  const std::string &getUserName() const;
  const int &getFd() const;
  int getJoinedChannelCount() const;

  // mode
  void setMode(unsigned int mode, bool enable);
  bool hasMode(ModeFlags flag) const;

  // state
  void setState(RegisterState state, bool eneble);
  RegisterState getState() const;

private:
  std::string _nickname;
  std::string _username;
  std::string _realname; // 63 自分で決めた
  int _fd;
  int _joinedChannelCount;

  RegisterState _state;
  unsigned int _modeFlags;
};

#endif
