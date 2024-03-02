#include "CommandHandler.hpp"

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
}

void CommandHandler::extractCommand(std::istringstream &iss) {
  iss >> this->_command;
  if (iss.bad()) {
    throw std::runtime_error(
        "A critical error occurred while extracting command.");
  }
}

void CommandHandler::extractParam(std::istringstream &iss) {
  std::string param;

  iss >> param;
  this->_params.push_back(param);
  if (iss.bad()) {
    throw std::runtime_error(
        "A critical error occurred while extracting param.");
  }
}
