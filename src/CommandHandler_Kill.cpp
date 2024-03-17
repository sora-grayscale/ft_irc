#include "CommandHandler.hpp"

void CommandHandler::delUserChannel(User user, const std::string &comment) {
  std::map<std::string, Channel> channels = this->_server.getChannels();

  for (std::map<std::string, Channel>::iterator it = channels.begin();
       it != channels.end(); it++) {
    if (it->second.isUserInChannel(user.getNickName())) {
      it->second.broadcastMessage(comment, user);
      it->second.removeUser(user);
    }
  }
}

void CommandHandler::eraseUserList(User user) {
  this->_server.eraseRegiMap(user.getFd());
}

void CommandHandler::delUser(User &user, const std::string &comment) {
  // userをチャンネルから消去, messageの送信
  delUserChannel(user, comment);
  // userを持っているリスト系から取り除く
  eraseUserList(user);
  // userのfdをクローズ
  close(user.getFd());
}

void CommandHandler::KILL(User &user) {
  if (!user.hasMode(User::Operator)) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NOPRIVILEGES());
  }
  if (this->_params.size() < 2) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NEEDMOREPARAMS(this->_command));
  }
  // param 0 ncik
  if (!this->_server.isRegiNick(this->_params.at(0))) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NOSUCHNICK(this->_params.at(0)));
  }
  // kill_user
  std::string comment = this->_params.at(1);
  comment += "\n\r";
  delUser(this->_server.findUser(this->_params.at(0)), comment);
}
