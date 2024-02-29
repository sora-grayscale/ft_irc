#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>

class Replies {
public:
  // 461
  static const std::string ERR_NEEDMOREPARAMS(const std::string &command);
  // 462
  static const std::string ERR_ALREADYREGISTRED();
  // 464
  static const std::string ERR_PASSWDMISMATCH();
};

#endif // REPLIES
