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
        None    = 0,
        Away    = 1 << 0, // a
        Invisible = 1 << 1, // i
        Wallops = 1 << 2, // w
        Restricted = 1 << 3, // r
        Operator = 1 << 4, // o
        LocalOperator = 1 << 5, // O
        ServerNotices = 1 << 6 // s
    };

  User(const std::string &nick,const std::string &realName);
  ~User();

  void setNickName(const std::string &nickname);
  void setRealName(const std::string &realname);
  void setUserName(const std::string &username);
  const std::string &getNickName(const std::string &nickname) const;
  const std::string &getRealName(const std::string &realname) const;
  const std::string &getUserName(const std::string &username) const;

  void setMode(unsigned int mode, bool enable);
  bool hasMode(ModeFlags flag) const;

private:
    std::string nickname; // 1.2.1 ユーザー 各ユーザーは、最大長さ9文字の一意のニックネームで他のユーザーと区別されます。ニックネームで使用される可能性のあるものとできないものについては、プロトコル文法規則（セクション2.3.1）を参照してください。 
    std::string username;
    std::string realname; // 63 自分で決めた
    const int userFd;
    RegisterState state;
    unsigned int modeFlags;
};

#endif
