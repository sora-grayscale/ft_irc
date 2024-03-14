#include "CommandHandler.hpp"

void CommandHandler::LIST(User &user) {
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
      this->_server.sendReply(
          user.getFd(),
          Replies::RPL_LIST(it->first, it->second.getVisibleUsrNum(user),
                            it->second.getTopic()));
      this->_server.sendReply(user.getFd(), Replies::RPL_LISTEND());
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
    this->_server.sendReply(user.getFd(),
                            Replies::RPL_LIST(channel.getChannelName(),
                                              channel.getVisibleUsrNum(user),
                                              channel.getTopic()));
    this->_server.sendReply(user.getFd(), Replies::RPL_LISTEND());
  }
  return;
}
