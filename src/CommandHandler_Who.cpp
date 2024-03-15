#include "CommandHandler.hpp"

void CommandHandler::displayAllUser(bool flag) {
  for (std::map<int, User>::iterator it = this->_server.getUserBegin();
       it != this->_server.getUserEnd(); it++) {
    if (!it->second.hasMode(User::Invisible))
      if (flag && !it->second.hasMode(User::Operator))
        ;
      else
        this->_server.sendReply(fd, Replies::RPL_WHOREPLY());
  }
}

void CommandHandler::displayChannelUser(const channel &channel, bool flag) {
  for (std::set<User *>::iterator it = channel.getUserBegin();
       it != channel.getUserEnd; it++) {
    if (!it->hasMode(User::Invisible))
    {
      if (flag && !it->hasMode(User::Operator))
        ;
      else
        this->_server.sendReply(fd, Replies::RPL_WHOREPLY());
    }
  }
}

void CommandHandler::displayUser(const User &user, bool flag) {
  if (flag && !user.hasMode(User::Operator))
    return;
  this->_server.sendReply(fd, Replies::RPL_WHOREPLY());
}

void CommandHandler::displayWhoQuery(const int fd, const std::string &str,
                                     bool flag) {
  if (str == '0')
    displayAllUser(flag);
  else if (this->_server.isExistChannel(str))
    displayChannelUser(this->_server.getChannel(str), flag);
  else if (str == "127.0.0.1")
    displayAllUser(flag);
  else if (str == this->_server.getServerName())
    displayAllUser(flag);
  else if (this->_server.isNick(str))
    displayUser(this->_server.findUser(str), flag);
  else
    this->_server.sendReply(fd, Replies::ERR_NOSUCHSERVER(str));
}

void CommandHandler::WHO(User &user) {
  if (this->_params.size() == 0) {
    displayAllUser(false);
  }
  else if (this->_params.size() == 1) {
    displayWhoQuery(user.getFd(), this->_params.at(0), false);
    return ;
  }
  else if (this->_params.size() >= 2) {
    if (this->_params.at(1) == 'o')
      displayWhoQuery(user.getFd(), this->_params.at(0), true);
  }
  this->_server.sendReply(user.getFd(), Replies::RPL_ENDOFWHO());
}
