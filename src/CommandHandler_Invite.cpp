#include "CommandHandler.hpp"

// ERR_NEEDMOREPARAMS
// ERR_NOSUCHNICK
// ERR_NOTONCHANNEL
// ERR_USERONCHANNEL
// ERR_CHANOPRIVSNEEDED
// RPL_INVITING
// RPL_AWAY

// RPL_INVITING (341)
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_CHANOPRIVSNEEDED (482)
// ERR_USERONCHANNEL (443)

void CommandHandler::INVITE(User &user) {

  // error
  if (this->_params.size() < 2) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  } else if (!this->_server.isNickRegisterd(this->_params.at(0))) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOSUCHNICK(this->_params.at(0)));
  }
//  if (this->_server.isExistChannel(this->_params.at(1))) {
//  }
  return;
}

//
//  // send all Channel user
//  if (this->_params.size() == 0) {
//    for (std::map<std::string, Channel>::const_iterator it =
//             this->_server.getChannelsBegin();
//         it != this->_server.getChannelsEnd(); it++) {
//      this->_server.sendReply(
//          user.getFd(),
//          Replies::RPL_LIST(it->first, it->second.getVisibleUsrNum(user),
//                            it->second.getTopic()));
//      this->_server.sendReply(user.getFd(), Replies::RPL_LISTEND());
//    }
//    return;
//  }
//
//  // send params Channel user
//  splitChannel(channelNames);
//  for (std::size_t i = 0; i < channelNames.size(); i++) {
//    if (!this->_server.isExistChannel(channelNames.at(i))) {
//      continue;
//    }
//    Channel &channel = this->_server.getChannel(channelNames.at(i));
//    this->_server.sendReply(user.getFd(),
//                            Replies::RPL_LIST(channel.getChannelName(),
//                                              channel.getVisibleUsrNum(user),
//                                              channel.getTopic()));
//    this->_server.sendReply(user.getFd(), Replies::RPL_LISTEND());
//  }
// return;
//}
