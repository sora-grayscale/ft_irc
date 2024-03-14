#include "CommandHandler.hpp"

void CommandHandler::INFO(User &user) {
  if (!(this->_params.size() == 0)) {
    if (this->_params.at(0) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
      return;
    }
  }
  this->_server.sendReply(user.getFd(),
                          Replies::RPL_INFO("server version", SERVER_VERSION));
  this->_server.sendReply(user.getFd(),
                          Replies::RPL_INFO("patch level", PATCH_LEVEL));
  this->_server.sendReply(
      user.getFd(),
      Replies::RPL_INFO("start day", this->_server.getStartDay()));
  this->_server.sendReply(user.getFd(), Replies::RPL_ENDOFINFO());
}
