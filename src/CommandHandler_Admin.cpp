#include "CommandHandler.hpp"

void CommandHandler::ADMIN(User &user) {
  if (!(this->_params.size() == 0)) {
    if (this->_params.at(0) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
      return;
    }
  }
  this->_server.sendReply(user.getFd(),
                          Replies::RPL_ADMINME(this->_server.getServerName()));
  this->_server.sendReply(user.getFd(), Replies::RPL_ADMINLOC1(ADMIN_LOCATION));
  this->_server.sendReply(user.getFd(),
                          Replies::RPL_ADMINLOC2(ADMIN_AFFILIATION));
  this->_server.sendReply(user.getFd(), Replies::RPL_ADMINEMAIL(ADMIN_MAIL));
}
