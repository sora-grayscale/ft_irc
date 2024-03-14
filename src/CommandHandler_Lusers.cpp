#include "CommandHandler.hpp"

void CommandHandler::LUSERS(User &user) {
  if (1 <= this->_params.size()) {
    if (this->_params.at(0) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
      return;
    }
  }
  if (2 <= this->_params.size()) {
    if (this->_params.at(1) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(1)));
      return;
    }
  }
  int users = this->_server.numOfUser();
  int services = 0;
  int operators = this->_server.numOfOpeUser();
  int unknown = 0;
  int channnels = this->_server.numOfChannel();
  int clients = users;
  int servers = 1;

  this->_server.sendReply(user.getFd(),
                          Replies::RPL_LUSERCLIENT(users, services, servers));
  this->_server.sendReply(user.getFd(), Replies::RPL_LUSEROP(operators));
  this->_server.sendReply(user.getFd(), Replies::RPL_LUSERUNKNOWN(unknown));
  this->_server.sendReply(user.getFd(), Replies::RPL_LUSERCHANNELS(channnels));
  this->_server.sendReply(user.getFd(), Replies::RPL_LUSERME(clients, servers));
}

