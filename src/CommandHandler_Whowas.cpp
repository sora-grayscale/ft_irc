#include "CommandHandler.hpp"

void CommandHandler::WHOWAS(User &user) {
  if (this->_params.size() == 0) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NONICKNAMEGIVEN());
    return;
  }
  if (!this->_server.isHisNick(this->_params.at(0))) {
   this->_server.sendReply(user.getFd(),
                               Replies::ERR_WASNOSUCHNICK(this->_params.at(0)));
    return;
  }
  if (this->_server.isRegiNick(this->_params.at(0))) {
    this->_server.sendReply(
        user.getFd(),
        Replies::RPL_WHOISSERVER(this->_params.at(0),
                                 this->_server.getServerName(), "server info"));
  } else {
    this->_server.sendReply(
        user.getFd(), Replies::RPL_WHOWASUSER(this->_params.at(0), "deleted",
                                              "127.0.0.1", "deleted"));
  }
  this->_server.sendReply(user.getFd(),
                          Replies::RPL_ENDOFWHOWAS(this->_params.at(0)));
}
