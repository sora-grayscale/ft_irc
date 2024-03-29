#include "CommandHandler.hpp"
#include "Server.hpp"

void Server::sendPing(User &user) const {
  if (user.getPingTime() != 0) {
    return;
  }

  user.setPingTime(std::time(NULL));

  std::stringstream ss;
  ss << "PING ";
  ss << user.getPingTime();
  ss << "\r\n";

  Server::sendReply(user.getFd(), ss.str());
}

void CommandHandler::PING(User &user) {
  if (this->_params.size() < 1) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }
  sendPong(user);
}
