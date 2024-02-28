#include "CommandHandler.hpp"
#include <iostream>

void CommandHandler::parseMessage(const std::string &message) {
  std::istringstream iss(message);

  if (message.at(0) == ':') {
    extractPrefix(iss);
  }
  if (iss.eof()) {
    return;
  }
  extractCommand(iss);
  while (!iss.eof()) {
    extractParam(iss);
  }
}

void CommandHandler::extractPrefix(std::istringstream &iss) {
  iss >> this->_prefix;
  if (iss.bad()) {
    throw std::runtime_error(
        "A critical error occurred while extracting prefix.");
  }
//  std::cout << this->_prefix << std::endl;
}

void CommandHandler::extractCommand(std::istringstream &iss) {
  iss >> this->_command;
  if (iss.bad()) {
    throw std::runtime_error(
        "A critical error occurred while extracting command.");
  }
//  std::cout << this->_command << std::endl;
}

void CommandHandler::extractParam(std::istringstream &iss) {
  std::string param;

  iss >> param;
  this->_params.push_back(param);
  if (iss.bad()) {
    throw std::runtime_error(
        "A critical error occurred while extracting param.");
  }
//  std::cout << param << std::endl;
}

CommandHandler::CommandHandler(const Server &server) : _server(server) {}

CommandHandler::~CommandHandler() {}

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
