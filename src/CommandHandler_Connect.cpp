#include "CommandHandler.hpp"

void CommandHandler::CONNECT(User &user) {
  if (this->_params.size() < 2) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }
  if (!user.hasMode(User::Operator)) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NOPRIVILEGES());
    return;
  }
  this->_server.sendReply(user.getFd(),
                          Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
}
