#include "CommandHandler.hpp"
void CommandHandler::KILL(User &user) {
  if (!user.hasMode(User::Operator)) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NOPRIVILEGES());
    return;
  }
  if (this->_params.size() < 2) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }
  // param 0 ncik
  if (!this->_server.isRegiNick(this->_params.at(0))) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOSUCHNICK(this->_params.at(0)));
    return;
  }
  // kill_user
  std::string comment = this->_params.at(1);
  comment += "\n\r";
  this->_server.delUser(this->_server.findUser(this->_params.at(0)), comment);
}
