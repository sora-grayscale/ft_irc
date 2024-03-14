#include "CommandHandler.hpp"

void CommandHandler::TRACE(User &user) {
  if (!(this->_params.size() == 0)) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
  } else {
    this->_server.sendReply(
        user.getFd(), Replies::ERR_NOSUCHSERVER(this->_server.getServerName()));
  }
}
