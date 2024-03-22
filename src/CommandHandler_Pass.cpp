#include "CommandHandler.hpp"

void CommandHandler::PASS(User &user) {
  if (this->_params.size() == 0) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }
  if (user.getState() != User::NONE && user.getState() != User::PASS) {
    this->_server.sendReply(user.getFd(),
                            Replies::Replies::ERR_ALREADYREGISTRED());
    return;
  }
  if (this->_params.at(0) != this->_server.getPassword()) {
    user.setState(User::PASS, false);
    this->_server.sendReply(user.getFd(), Replies::ERR_PASSWDMISMATCH());
    user.incrementPassTryCount();
    if ((COMMAND_ATTEMPT_NUM) <= user.getPassTryCount()) {
      this->_server.delUser(user.getFd());
    }
    return;
  }
  user.setState(User::PASS, true);
  return;
}
