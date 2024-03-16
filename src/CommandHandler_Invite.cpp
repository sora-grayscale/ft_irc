#include "CommandHandler.hpp"

void CommandHandler::INVITE(User &user) {
  // error
  if (this->_params.size() < 2) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }

  const std::string &nickName = this->_params.at(0);
  const std::string &channelName = this->_params.at(1);

  if (!this->_server.isNickRegisterd(nickName)) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOSUCHNICK(nickName));
    return;
  }
  if (this->_server.isExistChannel(channelName)) {
    const Channel &channel = this->_server.getChannel(channelName);
    if (!channel.isUserInChannel(user)) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOTONCHANNEL(channelName));
      return;
    }
    if (channel.hasChannleMode(Channel::InviteOnly) ||
        channel.hasChannleMode(Channel::InvitationMask)) {
      if (!channel.hasUserStatus(user, Channel::Operator)) {
        this->_server.sendReply(user.getFd(),
                                Replies::ERR_CHANOPRIVSNEEDED(channelName));
        return;
      }
    }
  }

  // check ok
  this->_server.sendReply(user.getFd(),
                          Replies::RPL_INVITING(channelName, nickName));
  this->_server.sendReply(this->_server.getUserFd(nickName),
                          Replies::RPL_INVITING(channelName, nickName));
  return;
}
