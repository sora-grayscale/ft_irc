#include "CommandHandler.hpp"

void CommandHandler::LINKS(User &user) {
  if (this->_params.size() == 0) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOSUCHSERVER(this->_server.getServerName()));
  } else {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
  }
}

