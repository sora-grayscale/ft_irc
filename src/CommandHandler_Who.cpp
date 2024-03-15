#include "CommandHandler.hpp"

void CommandHandler::displayAllUser(const int fd, bool flag) {
  for (std::map<int, User>::const_iterator it = this->_server.getUserBegin();
       it != this->_server.getUserEnd(); it++) {
    if (it->second.hasMode(User::Invisible))
      continue;
    else {
      if (flag && !it->second.hasMode(User::Operator))
        ;
      else {
        this->_server.sendReply(
            fd, Replies::RPL_WHOREPLY(
                    it->second.getCurrentChannel(), it->second.getUserName(),
                    "127.0.0.1", this->_server.getServerName(),
                    it->second.getNickName(), it->second.getRealName()));
      }
    }
  }
}

void CommandHandler::displayChannelUser(const int fd, const Channel &channel,
                                        bool flag) {
  for (std::set<User *>::iterator it = channel.getUserBegin();
       it != channel.getUserEnd(); it++) {
    if (!(*it)->hasMode(User::Invisible)) {
      if (flag && !(*it)->hasMode(User::Operator))
        ;
      else {
        this->_server.sendReply(
            fd, Replies::RPL_WHOREPLY(
                    channel.getChannelName(), (*it)->getUserName(), "127.0.0.1",
                    this->_server.getServerName(), (*it)->getNickName(),
                    (*it)->getRealName()));
      }
    }
  }
}

void CommandHandler::displayUser(const int fd, const User &user, bool flag) {
  if (flag && !user.hasMode(User::Operator))
    return;
  this->_server.sendReply(
      fd, Replies::RPL_WHOREPLY(user.getCurrentChannel(), user.getUserName(),
                                "127.0.0.1", this->_server.getServerName(),
                                user.getNickName(), user.getRealName()));
}

void CommandHandler::displayWhoQuery(const int fd, const std::string &str,
                                     bool flag) {
  if (str == "0")
    displayAllUser(fd, flag);
  else if (this->_server.isExistChannel(str))
    displayChannelUser(fd, this->_server.getChannel(str), flag);
  else if (str == "127.0.0.1")
    displayAllUser(fd, flag);
  else if (str == this->_server.getServerName())
    displayAllUser(fd, flag);
  else if (this->_server.isNick(str))
    displayUser(fd, this->_server.findUser(str), flag);
  else
    this->_server.sendReply(fd, Replies::ERR_NOSUCHSERVER(str));
}

void CommandHandler::WHO(User &user) {
  if (this->_params.size() == 0) {
    displayAllUser(user.getFd(), false);
    this->_server.sendReply(user.getFd(), Replies::RPL_ENDOFWHO(""));
  } else if (this->_params.size() == 1) {
    displayWhoQuery(user.getFd(), this->_params.at(0), false);
    this->_server.sendReply(user.getFd(),
                            Replies::RPL_ENDOFWHO(this->_params.at(0)));
    return;
  } else if (this->_params.size() >= 2) {
    if (this->_params.at(1) == "o")
      displayWhoQuery(user.getFd(), this->_params.at(0), true);
    this->_server.sendReply(user.getFd(),
                            Replies::RPL_ENDOFWHO(this->_params.at(1)));
  }
}
