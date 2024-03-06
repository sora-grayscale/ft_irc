#include "Replies.hpp"

// 421
const std::string Replies::ERR_UNKNOWNCOMMAND(const std::string &command) {
  std::string message;

  message += "421 ";
  message += command;
  message += " :Unknown command";
  return (message);
}


// 451
const std::string Replies::ERR_NOTREGISTERED() {
  std::string message;

  message += "451 ";
  message += ":You have not registered";
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

// 484
const std::string Replies::ERR_RESTRICTED() {
  std::string message;

  message += "484 ";
  message += ":Your connection is restricted!";
  return message;
}

// 461
const std::string Replies::ERR_NEEDMOREPARAMS(const std::string &command) {
  std::string message;

  message += "461 ";
  message += command;
  message += " :Not enough parameters";
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

// 381
const std::string Replies::RPL_YOUREOPER() {
  std::string message;

  message += "381 ";
  message += ":You are now an IRC operator";
  return (message);
}

// 491
const std::string Replies::ERR_NOOPERHOST() {
  std::string message;

  message += "491 ";
  message += ":No O-lines for your host";
  return (message);
}

// 375
const std::string Replies::RPL_MOTDSTART() {
  std::string message;

  message += "375";
  message += " :- Message of the day - ";
  return (message);
}

// 372
const std::string Replies::RPL_MOTD() {
  std::string message;

  message += "372";
  message += " :Today's message!!";
  return (message);
}

// 376
const std::string Replies::RPL_ENDOFMOTD() {
  std::string message;

  message += "376";
  message += ":End of MOTD command";
  return (message);
}

// 422
const std::string Replies::ERR_NOMOTD() {
  std::string message;

  message += "422";
  message += ":MOTD File is missing";
  return (message);
}
// 421
const std::string Replies::ERR_NOSUCHSERVER(const std::string &serverName) {
  std::string message;

  message += "402 ";
  message += serverName;
  message += " :No such server";
  return (message);
}
