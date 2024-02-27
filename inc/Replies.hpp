#ifndef REPLIES_HPP
#define REPLIES_HPP

class Replies {
public:
  //461
  static std::string ERR_ALREADYREGISTRED(const std::string command);
  //462
  static std::string ERR_NEEDMOREPARAMS();
};

#endif // REPLIES
