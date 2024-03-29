#include "CommandHandler.hpp"
#include "Server.hpp"

void Server::checkPong(User &user) {
  if (user.getPingTime() == 0) {
    return;
  }

  std::time_t now = std::time(NULL);
  std::time_t diff = now - user.getPingTime();

  if (static_cast<long>(diff) < PING_TIME) {
    return;
  }
  delUser(user, "user Killed because of no respons\r\n");
}

void CommandHandler::sendPong(const User &user) const {
  std::string message;
  message += "PONG ";
  message += this->_params.at(0);
  message += "\r\n";

  this->_server.sendReply(user.getFd(), message);
}

void CommandHandler::PONG(User &user) { user.setPingTime(0); }
