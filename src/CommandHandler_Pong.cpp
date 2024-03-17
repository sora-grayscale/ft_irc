#include "CommandHandler.hpp"

void CommandHandler::checkPong(User &user) {
  if (user.getPingTime() == 0) {
    return;
  }

  std::time_t now = std::time(NULL);
  std::time_t diff = now - user.getPingTime();

  if (diff < 10) {
    return;
  }
  delUser(user, "user Killed because of no respons\n\r");
}

void CommandHandler::sendPong(User &user) {
  std::string message;
  message += "PONG ";
  message += this->_params.at(0);
  message += "\n\r";

  this->_server.sendReply(user.getFd(), message);
}

void CommandHandler::PONG(User &user) { user.setPingTime(0); }
