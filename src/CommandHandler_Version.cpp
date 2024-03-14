#include "CommandHandler.hpp"

void CommandHandler::VERSION(User &user) {
  if (!(this->_params.size() == 0)) {
    if (this->_params.at(0) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
      return;
    }
  }
  this->_server.sendReply(user.getFd(),
                          Replies::RPL_VERSION(SERVER_VERSION, DEBUG_LEVEL,
                                               this->_server.getServerName(),
                                               SERVER_VERSION_COMMENT));
}

