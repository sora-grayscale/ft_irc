#include "CommandHandler.hpp"

const std::string CommandHandler::handleCommand(const std::string &message,
                                                User &user) {
  parseMessage(message);
  if (!checkRegisterdState(user)) {
    return (this->_reply);
  }
  executeCommand(user);
  return (this->_reply);
}

// The `parseMessage` function is implemented in a separate file.

bool CommandHandler::checkRegisterdState(const User &user) {
  if (user.getState() == User::NONE) {
    if (this->_command != "PASS") {
      this->_reply = Replies::ERR_NOTREGISTERED();
      this->_reply += " [You need PASS command first] ";
      return (false);
    }
  } else if (user.getState() != User::REGISTERD) {
    if (this->_command != "PASS" && this->_command != "NICK" &&
        this->_command != "USER") {
      this->_reply = Replies::ERR_NOTREGISTERED();
      this->_reply += " [You can only use PASS, NICK, USER command now!] ";
      return (false);
    }
  }
  return (true);
}

void CommandHandler::executeCommand(User &user) {
  if (this->_command == "PASS") {
    this->_reply = PASS(user);
  } else if (this->_command == "USER") {
    this->_reply = USER(user);
  } else {
    this->_reply = Replies::ERR_UNKNOWNCOMMAND(this->_command);
  }
}
