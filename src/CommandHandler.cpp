#include "CommandHandler.hpp"

void CommandHandler::PASS(const std::string &commandName,
                          const std::vector<string> &params, User &user,) {
  if (user.getState() != User::NONE)
    // throw std::runtime_error(":You may not reregister");
  if (params.size() < 1)
    // throw std::runtime_error("PASS :Not enough parameters");
  if (params[0] != this->server.getPassword())
    return ;
  setState(User::PASS);
}

