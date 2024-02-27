#include "CommandHandler.hpp"

std::string CommandHandler::PASS(const std::string &commandName,
                                 const std::vector<string> &params,
                                 User &user, ) {
  if (user.getState() != User::NONE)
    return ERR_ALREADYREGISTRED("PASS");
  if (params.size() < 1)
    return ERR_NEEDMOREPARAMS();
  if (params[0] != this->server.getPassword())
    return "";
  setState(User::PASS);
  return "";
}

