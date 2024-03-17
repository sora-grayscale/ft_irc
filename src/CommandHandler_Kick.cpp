#include "CommandHandler.hpp"

void CommandHandler::KICK(User &user) {
  std::vector<std::string> channelNames;
  std::vector<std::string> users;

  // error
  if (this->_params.size() < 2) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }

  splitStringByColon(this->_params.at(0), channelNames);
  splitStringByColon(this->_params.at(1), users);

  if (channelNames.size() != 1) {
    if (channelNames.size() != users.size()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NEEDMOREPARAMS(this->_command));
      return;
    }
  }

  if (channelNames.size() == 1) {
    for (std::size_t i = 1; i < users.size(); i++) {
      channelNames.push_back(channelNames.at(0));
    }
  }

  for (std::size_t i = 0; i < channelNames.size(); i++) {
    if (!this->_server.isExistChannel(channelNames.at(i))) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHCHANNEL(channelNames.at(i)));
      continue;
    }

    Channel &channel = this->_server.getChannel(channelNames.at(i));

    if (!channel.isUserInChannel(users.at(i))) {
      this->_server.sendReply(
          user.getFd(),
          Replies::ERR_USERNOTINCHANNEL(channelNames.at(i), users.at(i)));
      continue;
    }

    if (!channel.isUserInChannel(user)) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOTONCHANNEL(channelNames.at(i)));
      continue;
    }

    if (!channel.hasUserStatus(user, Channel::Operator)) {
      this->_server.sendReply(
          user.getFd(), Replies::ERR_CHANOPRIVSNEEDED(channelNames.at(i)));
      continue;
    }
    std::string message = ":" + user.getNickName() + "!" + user.getUserName() +
                          "@" + SERVER_NAME + " " + this->_command + " " +
                          channelNames.at(i) + ":" + users.at(i) + "\r\n";
    User &kickedUser = this->_server.findUser(users.at(i));
    channel.broadcastMessage(message, user);
    channel.removeUser(kickedUser);
  }
}

void CommandHandler::splitStringByColon(const std::string &str,
                                        std::vector<std::string> &vec) {
  std::string token;

  std::istringstream issChannel(str);
  while (std::getline(issChannel, token, ',')) {
    vec.push_back(token);
  }
}
