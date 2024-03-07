#include "Replies.hpp"

// 332
const std::string Replies::RPL_TOPIC(const std::string &channelName, const std::string &topic) {
  std::string message;
  message += "332 ";
  message += channelName;
  message += " :";
  message += topic;
  message += "\r\n";
  return (message);
}

// 333
const std::string Replies::RPL_TOPICWHOTIME(const std::string &channelName, const std::string &nick, const long &setat) {
  std::string message;
  message += "333 ";
  message += channelName;
  message += " ";
  message += nick;
  message += " ";
  message += setat;
  message += "\r\n";
  return (message);
}


// 366
const std::string Replies::RPL_ENDOFNAMES(const std::string &channelName) {
  std::string message;
  message += "366 ";
  message += channelName;
  message += " :End of NAMES list";
  message += "\r\n";
  return (message);
}

// 403
const std::string Replies::ERR_NOSUCHCHANNEL(const std::string &channelName) {
  std::string message;
  message += "403 ";
  message += channelName;
  message += " :No such channel";
  message += "\r\n";
  return (message);
}

// 405
const std::string Replies::ERR_TOOMANYCHANNELS(const std::string &channelName) {
  std::string message;
  message += "405 ";
  message += channelName;
  message += " :You have joined too many channels";
  message += "\r\n";
  return (message);
}

// 421
const std::string Replies::ERR_UNKNOWNCOMMAND(const std::string &command) {
  std::string message;
  message += "421 ";
  message += command;
  message += " :Unknown command";
  return (message);
}

// 431
const std::string Replies::ERR_NONICKNAMEGIVEN() {
  std::string message;
  message += "431 ";
  message += ":No nickname given";
  return (message);
}

// 432
const std::string Replies::ERR_ERRONEUSNICKNAME(const std::string &nick) {
  std::string message;
  message += "432 ";
  message += nick;
  message += " :Erroneous nickname";
  return message;
}

// 433
const std::string Replies::ERR_NICKNAMEINUSE(const std::string &nick) {
  std::string message;
  message += "433 ";
  message += nick;
  message += " :Nickname is already in use";
  return message;
}

// 436
const std::string Replies::ERR_NICKCOLLISION(const std::string &nick,
                                             const std::string &user,
                                             const std::string &host) {
  std::string message;
  message += "436 ";
  message += nick;
  message += " :Nickname collision KILL from ";
  if (user.empty())
    message += "<user>";
  else
    message += user;
  message += host;
  return message;
}

// 437
const std::string Replies::ERR_UNAVAILRESOURCE(const std::string &str) {
  std::string message;
  message += "437 ";
  message += str;
  message += " :Nick/channel is temporarily unavailable";
  return message;
}

// 451
const std::string Replies::ERR_NOTREGISTERED() {
  std::string message;
  message += "451 ";
  message += ":You have not registered";
  return (message);
}

// 461
const std::string Replies::ERR_NEEDMOREPARAMS(const std::string &command) {
  std::string message;
  message += "461 ";
  message += command;
  message += " :Not enough parameters";
  message += "\r\n";
  return (message);
}

// 462
const std::string Replies::ERR_ALREADYREGISTRED() {
  std::string message;
  message += "462 ";
  message += ":Unauthorized command (already registered)";
  return (message);
}

// 464
const std::string Replies::ERR_PASSWDMISMATCH() {
  std::string message;
  message += "464 ";
  message += ":Password incorrect";
  return (message);
}

// 471
const std::string Replies::ERR_CHANNELISFULL(const std::string &channelName) {
  std::string message;
  message += "471 ";
  message += channelName;
  message += " :Cannot join channel (+l)";
  message += "\r\n";
  return (message);
}

// 473
const std::string Replies::ERR_INVITEONLYCHAN(const std::string &channelName) {
  std::string message;
  message += "473 ";
  message += channelName;
  message += " :Cannot join channel (+i)";
  message += "\r\n";
  return (message);
}

// 474
const std::string Replies::ERR_BANNEDFROMCHAN(const std::string &channelName) {
  std::string message;
  message += "474 ";
  message += channelName;
  message += " :Cannot join channel (+b)";
  message += "\r\n";
  return (message);
}

// 475
const std::string Replies::ERR_BADCHANNELKEY(const std::string &channelName) {
  std::string message;
  message += "475 ";
  message += channelName;
  message += " :Cannot join channel (+k)";
  message += "\r\n";
  return (message);
}

// 476
const std::string Replies::ERR_BADCHANMASK(const std::string &channelName) {
  std::string message;
  message += "476 ";
  message += channelName;
  message += " :Bad Channel Mask";
  message += "\r\n";
  return (message);
}

// 484
const std::string Replies::ERR_RESTRICTED() {
  std::string message;
  message += "484 ";
  message += ":Your connection is restricted!";
  return message;
}
