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
  User(const std::string &nick, const std::string &realName);
  User &operator=(const User &user);
  ~User();

  void setNickName(const std::string &nickname);
  void setRealName(const std::string &realname);
  void setUserName(const std::string &username);
  const std::string &getNickName() const;
  const std::string &getRealName() const;
  const std::string &getUserName() const;
  const int &getFd() const;

  void setMode(unsigned int mode, bool enable);
  bool hasMode(ModeFlags flag) const;
  void setState(RegisterState state, bool eneble);
  RegisterState getState() const;

private:
  std::string
      _nickname; // 1.2.1 ユーザー
                 // 各ユーザーは、最大長さ9文字の一意のニックネームで他のユーザーと区別されます。ニックネームで使用される可能性のあるものとできないものについては、プロトコル文法規則（セクション2.3.1）を参照してください。
  std::string _username;
  std::string _realname; // 63 自分で決めた
  int _fd;

  RegisterState _state;
  unsigned int _modeFlags;
};

#endif
