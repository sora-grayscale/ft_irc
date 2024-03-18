#include "CommandHandler.hpp"

void CommandHandler::sendError(const int fd, const std::string &message) {
  this->_server.sendReply(fd, message);
}

void CommandHandler::ERROR(User &user) {
  std::string message;
  message += "ERROR :";
  if (this->_params.size() > 1) {
    for (std::size_t i = 0; i < this->_params.size(); i++) {
      message += " ";
      message += this->_params.at(i);
    }
  }
  message += "\n\r";
  sendError(user.getFd(), message);
}
