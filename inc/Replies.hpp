#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>

// 1. RPL_NAMREPLY (353)
class Replies {
public:
  // 332
  static const std::string RPL_TOPIC(const std::string &channelName,
                                     const std::string &topic);
  // 333
  static const std::string RPL_TOPICWHOTIME(const std::string &channelName,
                                     const std::string &nick,
                                     const long &setat);
  // 366
  static const std::string RPL_ENDOFNAMES(const std::string &channelName);
  // 403
  static const std::string ERR_NOSUCHCHANNEL(const std::string &channelName);
  // 405
  static const std::string ERR_TOOMANYCHANNELS(const std::string &channelName);
  // 421
  static const std::string ERR_UNKNOWNCOMMAND(const std::string &command);
  // 431
  static const std::string ERR_NONICKNAMEGIVEN();
  // 432
  static const std::string ERR_ERRONEUSNICKNAME(const std::string &nick);
  // 433
  static const std::string ERR_NICKNAMEINUSE(const std::string &nick);
  // 436
  static const std::string ERR_NICKCOLLISION(const std::string &nick,
                                             const std::string &user,
                                             const std::string &host);
  // 437
  static const std::string ERR_UNAVAILRESOURCE(const std::string &str);
  // 451
  static const std::string ERR_NOTREGISTERED();
  // 461
  static const std::string ERR_NEEDMOREPARAMS(const std::string &command);
  // 462
  static const std::string ERR_ALREADYREGISTRED();
  // 464
  static const std::string ERR_PASSWDMISMATCH();
  // 471
  static const std::string ERR_CHANNELISFULL(const std::string &channelName);
  // 473
  static const std::string ERR_INVITEONLYCHAN(const std::string &channelName);
  // 474
  static const std::string ERR_BANNEDFROMCHAN(const std::string &channelName);
  // 475
  static const std::string ERR_BADCHANNELKEY(const std::string &channelName);
  // 476
  static const std::string ERR_BADCHANMASK(const std::string &channelName);
  // 484
  static const std::string ERR_RESTRICTED();
};

#endif // REPLIES
