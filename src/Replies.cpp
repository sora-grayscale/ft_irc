#include "Replies.hpp"

// 461
std::string Replies::ERR_ALREADYREGISTRED(const std::string command) {
  std::string message;

  message += "461 ";
  message += command;
  message += " :Not enough parameters";
  return (message);
}

// 462
std::string Replies::ERR_NEEDMOREPARAMS() {
  std::string message;

  message += "462 ";
  message += ":You may not reregister";
  return (massage);
}
