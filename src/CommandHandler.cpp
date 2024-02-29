#include "CommandHandler.hpp"
#include <iostream>

CommandHandler::CommandHandler(const Server &server) : _server(server) {}

CommandHandler::~CommandHandler() {}

void CommandHandler::handleCommand(const std::string &message) {
  parseMessage(message);
}

const std::string CommandHandler::PASS(const std::string &commandName,
                                       const std::vector<std::string> &params,
                                       User &user) {
  if (user.getState() != User::NONE)
    return Replies::ERR_ALREADYREGISTRED();
  if (params.size() < 1)
    return Replies::ERR_NEEDMOREPARAMS(commandName);
  if (params.at(0) != this->_server.getPassword())
    return "";
  user.setState(User::PASS);
  return "";
}
