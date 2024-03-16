#include "CommandHandler.hpp"

void CommandHandler::WHOIS(User &user) {
  // param 0
  if (this->_params.size() == 0) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NONICKNAMEGIVEN());
    return;
  }

  // param 1
  if (this->_params.size() == 1) {
    if (!this->_server.isRegiNick(this->_params.at(0))) {
      // ERR_NOSUCHNICK
      return ;
    }
    // RPL_
    return;
  }

  // param 2
  if (this->_params.size() == 2) {
    if (this->_params.at(0) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
      return ;
    }
    if (!this->_server.isRegiNick(this->_params.at(1))) {
      // ERR_NOSUCHNICK
      return ;
    }
    // RPL
  }
}

