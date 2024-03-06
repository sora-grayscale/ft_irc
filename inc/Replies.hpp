#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>
#include <sstream>

class Replies {
public:
  // 251
  static const std::string
  RPL_LUSERCLIENT(const int &users, const int &services, const int &servers);
  // 252
  static const std::string RPL_LUSEROP(const int &operators);
  // 253
  static const std::string RPL_LUSERUNKNOWN(const int &unknown);
  // 254
  static const std::string RPL_LUSERCHANNELS(const int &channels);
  // 255
  static const std::string RPL_LUSERME(const int &clients, const int &servers);
  // 372
  static const std::string RPL_MOTD();
  // 375
  static const std::string RPL_MOTDSTART();
  // 376
  static const std::string RPL_ENDOFMOTD();
  // 381
  static const std::string RPL_YOUREOPER();
  // 402
  static const std::string ERR_NOSUCHSERVER(const std::string serverName);
  // 421
  static const std::string ERR_UNKNOWNCOMMAND(const std::string &command);
  // 422
  static const std::string ERR_NOMOTD();
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
  // 484
  static const std::string ERR_RESTRICTED();
  // 491
  static const std::string ERR_NOOPERHOST();
};

#endif // REPLIES
