#include "CommandHandler.hpp"

void CommandHandler::sendNoticeMessageChannel(const User &sender,
                                            const std::string &channelName,
                                            const std::string &message) {
  if (!this->_server.isExistChannel(channelName)) {
    return;
  }

  Channel &sendTo = this->_server.getChannel(channelName);

  if (!sendTo.isUserInChannel(sender)) {
    return;
  }
  sendTo.broadcastMessage(message, sender.getFd());
}

void CommandHandler::sendNoticeMessageUser(const std::string &nick,
                                           const std::string &message) {
  if (!this->_server.isRegiNick(nick)) {
    return;
  }
  User &sendTo = this->_server.findUser(nick);

  this->_server.sendReply(sendTo.getFd(), message);
}

const std::string CommandHandler::createNoticeMessage(const std::string &sendTo,
                                    const std::string &message) {
  std::string str;
  str = "NOTICE ";
  str += sendTo;
  str += " :";
  str += message;
  str += "\n\r";
  return str;
}

void CommandHandler::sendNoticeMessage(const User &user,
                                     const std::vector<std::string> &sendTo,
                                     const std::string &message) {
  std::string noticeMessage;

  for (std::size_t i = 0; i < sendTo.size(); i++) {
    noticeMessage = createNoticeMessage(sendTo.at(i), message);
    if (isValidChannelName(sendTo.at(i))) {
      sendNoticeMessageChannel(user, sendTo.at(i), noticeMessage);
    } else {
      sendNoticeMessageUser(sendTo.at(i), noticeMessage);
    }
  }
}

void CommandHandler::NOTICE(User &user) {
  if (this->_params.size() < 1) {
    return;
  }
  if (this->_params.size() < 2) {
    return;
  }

  std::vector<std::string> sendTo;
  std::string message;

  CreateParamToOneString(message);
  splitStringByColon(this->_params.at(0), sendTo);

  sendNoticeMessage(user, sendTo, message);
}
