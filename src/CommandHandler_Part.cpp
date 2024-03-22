#include "CommandHandler.hpp"

void CommandHandler::PART(User &user) {
  std::vector<std::string> channelNames;

  if (this->_params.size() == 0) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }

  splitChannel(channelNames);

  for (std::size_t i = 0; i < channelNames.size(); i++) {

    if (channelNames.at(i).empty() || !isValidChannelName(channelNames.at(i))) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHCHANNEL(channelNames.at(i)));
      continue;
    }

    if (!this->_server.isExistChannel(channelNames.at(i))) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHCHANNEL(channelNames.at(i)));
      continue;
    }

    const Channel &channel = this->_server.getChannel(channelNames.at(i));
    if (!channel.isUserInChannel(user)) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOTONCHANNEL(channelNames.at(i)));
    }
    const_cast<Channel &>(channel).removeUser(user);
    if (channel.isDelete()) {
      this->_server.eraseChannel(channel.getChannelName());
    }
  }
}

void CommandHandler::splitChannel(std::vector<std::string> &channelNames) {
  std::string token;

  std::istringstream issChannel(this->_params.at(0));
  while (std::getline(issChannel, token, ',')) {
    channelNames.push_back(token);
  }
}
