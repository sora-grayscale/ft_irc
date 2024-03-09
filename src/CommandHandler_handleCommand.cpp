#include "CommandHandler.hpp"

void CommandHandler::handleCommand(const std::string &message, const int fd) {
  User &user = this->_server.findUser(fd);
  parseMessage(message);
  if (!checkRegisterdState(user)) {
    this->_server.sendReply(fd, this->_reply);
    return;
  }
  executeCommand(user, fd);
  return;
}

// The `parseMessage` function is implemented in a separate file.

bool CommandHandler::checkRegisterdState(const User &user) {
  if (user.getState() == User::NONE) {
    if (this->_command != "PASS") {
      this->_reply = Replies::ERR_NOTREGISTERED();
      this->_reply += " [You need PASS command first] \r\n";
      return (false);
    }
  } else if (user.getState() != User::REGISTERD) {
    if (this->_command != "PASS" && this->_command != "NICK" &&
        this->_command != "USER") {
      this->_reply = Replies::ERR_NOTREGISTERED();
      this->_reply += " [You can only use PASS, NICK, USER command now!] \r\n";
      return (false);
    }
  }
  return (true);
}

void CommandHandler::executeCommand(User &user, const int fd) {
  if (this->_command == "PASS") {
    this->_reply = PASS(user);
    this->_server.sendReply(fd, this->_reply);
  } else if (this->_command == "USER") {
    this->_reply = USER(user);
    this->_server.sendReply(fd, this->_reply);
  } else if (this->_command == "NICK") {
    this->_reply = NICK(user);
    this->_server.sendReply(fd, this->_reply);
  } else if (this->_command == "OPER") {
    OPER(user);
  } else if (this->_command == "MOTD") {
    MOTD(user);
  } else if (this->_command == "LUSERS") {
    LUSERS(user);
  } else if (this->_command == "VERSION") {
    VERSION(user);
  } else if (this->_command == "TIME") {
    TIME(user);
  } else if (this->_command == "CONNECT") {
    CONNECT(user);
  } else {
    this->_reply = Replies::ERR_UNKNOWNCOMMAND(this->_command);
    this->_server.sendReply(fd, this->_reply);
  }
}
