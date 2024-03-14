#include "CommandHandler.hpp"

void CommandHandler::NAMES(User &user) {
  std::vector<std::string> channelNames;

  // error
  if (2 <= this->_params.size()) {
    if (this->_params.at(1) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(1)));
      return;
    }
  }

  // send all Channel user
  if (this->_params.size() == 0) {
    for (std::map<std::string, Channel>::const_iterator it =
             this->_server.getChannelsBegin();
         it != this->_server.getChannelsEnd(); it++) {
      for (std::set<User *>::const_iterator userIt = it->second.getUserBegin();
           userIt != it->second.getUserEnd(); userIt++) {
        this->_server.sendReply(user.getFd(),
                                Replies::RPL_NAMREPLY(it->second, **userIt));
      }
      this->_server.sendReply(user.getFd(), Replies::RPL_ENDOFNAMES(it->first));
    }
    return;
  }

  // send params Channel user
  splitChannel(channelNames);
  for (std::size_t i = 0; i < channelNames.size(); i++) {
    if (!this->_server.isExistChannel(channelNames.at(i))) {
      continue;
    }
    Channel &channel = this->_server.getChannel(channelNames.at(i));
    for (std::set<User *>::const_iterator userIt = channel.getUserBegin();
         userIt != channel.getUserEnd(); userIt++) {
      this->_server.sendReply(user.getFd(),
                              Replies::RPL_NAMREPLY(channel, **userIt));
    }
    this->_server.sendReply(user.getFd(),
                            Replies::RPL_ENDOFNAMES(channelNames.at(i)));
  }
  return;
}
