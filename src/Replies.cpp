#include "Replies.hpp"

// 421
const std::string Replies::ERR_UNKNOWNCOMMAND(const std::string &command) {
  std::string message;

  message += "421 ";
  message += command;
  message += " :Unknown command";
  return (message);
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

