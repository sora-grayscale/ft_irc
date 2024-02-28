#include "Replies.hpp"

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
