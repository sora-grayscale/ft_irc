#include "CommandHandler.hpp"

void CommandHandler::displayAllChannel(const int fd,
                                       const std::string nick) const {
  for (std::map<std::string, Channel>::const_iterator it =
           this->_server.getChannelsBegin();
       it != this->_server.getChannelsEnd(); it++) {
    for (std::set<User *>::const_iterator userIt = it->second.getUserBegin();
         userIt != it->second.getUserEnd(); userIt++) {
      if ((*userIt)->getNickName() != nick ||
          (*userIt)->hasMode(User::Invisible)) {
        continue;
      } else {
        this->_server.sendReply(fd,
                                Replies::RPL_WHOISCHANNELS(nick, it->first));
      }
    }
  }
}

void CommandHandler::displayOpeUser(const int fd,
                                    const std::string nick) const {
  User user = this->_server.findUser(nick);
  if (!user.hasMode(User::Operator))
    return;
  this->_server.sendReply(fd, Replies::RPL_WHOISOPERATOR(nick));
}

void CommandHandler::displayWhoisQuery(const User &user,
                                       const std::string nick) const {
  this->_server.sendReply(
      user.getFd(),
      Replies::RPL_WHOISUSER(user.getNickName(), user.getUserName(),
                             "127.0.0.1", user.getRealName()));
  displayAllChannel(user.getFd(), nick);
  this->_server.sendReply(
      user.getFd(), Replies::RPL_WHOISSERVER(
                        nick, this->_server.getServerName(), "server info"));
  displayOpeUser(user.getFd(), nick);
  this->_server.sendReply(user.getFd(), Replies::RPL_ENDOFWHOIS(nick));
}

void CommandHandler::WHOIS(User &user) {
  if (this->_params.size() == 0) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NONICKNAMEGIVEN());
    return;
  }

  if (this->_params.size() == 1) {
    if (!this->_server.isRegiNick(this->_params.at(0))) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHNICK(this->_params.at(0)));
      return;
    }
    displayWhoisQuery(user, this->_params.at(0));
    return;
  }

  if (this->_params.size() == 2) {
    if (this->_params.at(0) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
      return;
    }
    if (!this->_server.isRegiNick(this->_params.at(1))) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHNICK(this->_params.at(1)));
      return;
    }
    displayWhoisQuery(user, this->_params.at(1));
    return;
  }
}
