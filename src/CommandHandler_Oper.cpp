#include "CommandHandler.hpp"

void CommandHandler::OPER(User &user) {
  if (this->_params.size() < 2) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }

  if (this->_params.at(1) != OPER_PASSWORD) {
    this->_server.sendReply(user.getFd(), Replies::ERR_PASSWDMISMATCH());
    return;
  }

  if (this->_params.at(0) != OPER_USER) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NOOPERHOST());
    return;
  }

  user.setMode(User::Operator, true);
  this->_server.sendReply(user.getFd(), Replies::RPL_YOUREOPER());
}

void CommandHandler::MOTD(User &user) {
  if (!(this->_params.size() == 0)) {
    if (this->_params.at(0) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
      return;
    }
  }
  this->_server.sendReply(user.getFd(), Replies::RPL_MOTDSTART());
  this->_server.sendReply(user.getFd(), Replies::RPL_MOTD());
  this->_server.sendReply(user.getFd(), Replies::RPL_ENDOFMOTD());
}


