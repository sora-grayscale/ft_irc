#include "CommandHandler.hpp"

// v3 JOIN message
// 1. ERR_NEEDMOREPARAMS (461)
// 1. ERR_NOSUCHCHANNEL (403)
// 1. ERR_TOOMANYCHANNELS (405)
// 1. ERR_BADCHANNELKEY (475)
// 1. ERR_BANNEDFROMCHAN (474)
// 1. ERR_CHANNELISFULL (471)
// 1. ERR_INVITEONLYCHAN (473)
// 1. ERR_BADCHANMASK (476)
// 1. RPL_TOPIC (332)
// 1. RPL_TOPICWHOTIME (333)
// 1. RPL_NAMREPLY (353)
// 1. RPL_ENDOFNAMES (366)


void CommandHandler::JOIN(User &user) {
  std::vector<std::string> channelNames;
  std::vector<std::string> keys;

  if (this->_params.at(0).empty()) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
  }

  splitChannelAndKey(channelNames, keys);

  for (std::size_t i = 0; i < channelNames.size(); i++) {

    if (channelNames.at(i).empty() || !isValidChannelName(channelNames.at(i))) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHCHANNEL(channelNames.at(i)));
      continue;
    } else if (hasReachedChannelLimit(user)) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_TOOMANYCHANNELS(channelNames.at(i)));
      continue;
    }

    if (!this->_server.isExistChannel(channelNames.at(i))) {
      if (keys.at(i).empty()) {
        this->_server.addChannel(channelNames.at(i));
      } else {
        this->_server.addChannel(channelNames.at(i), keys.at(i));
      }
    } else {
      const Channel &channel = this->_server.getChannel(channelNames.at(i));
      if (!verifyChannelKey(channel, keys.at(i))) {
        this->_server.sendReply(
            user.getFd(), Replies::ERR_BADCHANNELKEY(channel.getChannelName()));
        continue;
      } else if (!checkBanStatus(channel, user.getNickName())) {
        this->_server.sendReply(user.getFd(), Replies::ERR_BANNEDFROMCHAN(
                                                  channel.getChannelName()));
        continue;
      } else if (!checkChannelCapacity(channel)) {
        this->_server.sendReply(user.getFd(), Replies::ERR_CHANNELISFULL(
                                                  channel.getChannelName()));
      } else if (!checkInviteOnlyStatus(channel)) {
        this->_server.sendReply(user.getFd(), Replies::ERR_INVITEONLYCHAN(
                                                  channel.getChannelName()));
      } else if (!validateChannelMask(channel, user.getNickName())) {
        this->_server.sendReply(user.getFd(), Replies::ERR_BADCHANMASK(
                                                  channel.getChannelName()));
      }
    }
  }
}

void CommandHandler::splitChannelAndKey(std::vector<std::string> &channels,
                                        std::vector<std::string> &keys) {
  std::string token;

  std::istringstream issChannel(this->_params.at(0));
  while (std::getline(issChannel, token, ',')) {
    channels.push_back(token);
  }

  if (this->_params.size() > 1 && !this->_params.at(1).empty()) {
    std::istringstream issKey(this->_params.at(1));
    while (std::getline(issKey, token, ',')) {
      keys.push_back(token);
    }
  }
}

bool CommandHandler::isValidChannelName(const std::string &channelName) {
  if (channelName.find_first_of("\a\n\r ,:") == std::string::npos) {
    return (true);
  }
  return (false);
}

bool CommandHandler::hasReachedChannelLimit(const User &user) {
  if (10 < user.getJoinedChannelCount()) {
    return (true);
  }
  return (false);
}

bool CommandHandler::verifyChannelKey(const Channel &channel,
                                      const std::string &key) {
  if (channel.getKey() != key) {
    return (false);
  }
  return (true);
}

bool CommandHandler::checkBanStatus(const Channel &channel,
                                    const std::string &nickname) {
  if (channel.isBanned(nickname)) {
    return (false);
  }
  return (true);
}

bool CommandHandler::checkChannelCapacity(const Channel &channel) {
  if (channel.userNum() < channel.getUserLimit()) {
    return (true);
  } else {
    return (false);
  }
}

bool CommandHandler::checkInviteOnlyStatus(const Channel &channel) {
  if (channel.hasChannleMode(Channel::InviteOnly)) {
    return (true);
  } else {
    return (false);
  }
}

bool CommandHandler::validateChannelMask(const Channel &channel,
                                         const std::string &nickname) {
  if (channel.isBanned(nickname)) {
    return (false);
  } else {
    return (true);
  }
}
