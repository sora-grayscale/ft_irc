#include "CommandHandler.hpp"

void CommandHandler::sendNoticeMessageChannel(
    const User &sender, const std::string &channelName,
    const std::string &message) const {
  if (!this->_server.isExistChannel(channelName)) {
    return;
  }

  const Channel &sendTo = this->_server.getChannel(channelName);

  if (!sendTo.isUserInChannel(sender)) {
    return;
  }
  sendTo.broadcastMessage(message, sender);
}

void CommandHandler::sendNoticeMessageUser(const User &sender,
                                           const std::string &nick,
                                           const std::string &message) const {
  if (!this->_server.isRegiNick(nick)) {
    return;
  }
  const User &sendTo = this->_server.findUser(nick);

  this->_server.sendReply(sender, sendTo.getFd(), message);
}

const std::string
CommandHandler::createNoticeMessage(const std::string &sendTo,
                                    const std::string &message) const {
  std::string str;
  str = "NOTICE ";
  str += sendTo;
  str += " :";
  str += message;
  str += "\r\n";
  return str;
}

void CommandHandler::sendNoticeMessage(const User &user,
                                       const std::vector<std::string> &sendTo,
                                       const std::string &message) const {
  std::string noticeMessage;

  for (std::size_t i = 0; i < sendTo.size(); i++) {
    noticeMessage = createNoticeMessage(sendTo.at(i), message);
    if (isValidChannelName(sendTo.at(i))) {
      sendNoticeMessageChannel(user, sendTo.at(i), noticeMessage);
    } else {
      sendNoticeMessageUser(user, sendTo.at(i), noticeMessage);
    }
  }
}

void CommandHandler::NOTICE(User &user) {
  if (this->_params.size() < 2) {
    return;
  }

  std::vector<std::string> sendTo;
  std::string message;

  splitStringByColon(this->_params.at(0), sendTo);
  createParamToOneString(message);

  sendNoticeMessage(user, sendTo, message);
}
