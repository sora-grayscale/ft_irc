#include "CommandHandler.hpp"

void CommandHandler::TOPIC(User &user) {
  if (this->_params.size() == 0) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }

  std::string &channelName = this->_params.at(0);

  if (!this->_server.isExistChannel(channelName)) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOSUCHCHANNEL(channelName));
    return;
  }

  const Channel &channel = this->_server.getChannel(channelName);
  if (!channel.isUserInChannel(user)) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOTONCHANNEL(channelName));
    return;
  }

  if (1 < this->_params.size()) {
    setTopic(user, const_cast<Channel &>(channel));
  }

  if (channel.getTopic().empty()) {
    this->_server.sendReply(user.getFd(), Replies::RPL_NOTOPIC(channelName));
  } else {
    this->_server.sendReply(
        user.getFd(), Replies::RPL_TOPIC(channelName, channel.getTopic()));
    this->_server.sendReply(user.getFd(),
                            Replies::RPL_TOPICWHOTIME(channelName,
                                                      channel.getTopicSetUser(),
                                                      channel.getTopicSetAt()));
  }
}

void CommandHandler::setTopic(const User &user, Channel &channel) const {
  if (this->_params.at(1).at(0) != ':') {
    channel.setTopic(this->_params.at(1), user.getNickName());
    return;
  }

  std::string topic;
  std::vector<std::string>::const_iterator it = this->_params.begin();
  it++;
  size_t i = 0;
  for (; it < this->_params.end(); it++) {
    if (i == 0) {
      topic += (*it).substr(1);
    } else {
      topic += *it;
    }
    topic += ' ';
    i++;
  }
  channel.setTopic(topic, user.getNickName());
  return;
}
