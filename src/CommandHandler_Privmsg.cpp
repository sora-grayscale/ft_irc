#include "CommandHandler.hpp"

void CommandHandler::CreateParamToOneString(std::string &message) {
  for (std::size_t i = 1; i < this->_params.size(); i++) {
    if (i != 1) {
      message += " ";
    }

    if (i == 1 && this->_params.at(1).at(0) == ':') {
      if (this->_params.at(i).size() != 1) {
        message = this->_params.at(i).substr(1);
      }
    } else {
      message += this->_params.at(i);
    }
  }
}

const std::string
CommandHandler::createPrivMessage(const std::string &sendTo,
                                  const std::string &message) {
  std::string str;
  str += "PRIVMSG ";
  str += sendTo;
  str += " :";
  str += message;
  str += "\n\r";
  return str;
}

void CommandHandler::sendPrivMessageChannel(const User &sender,
                                            const std::string &channelName,
                                            const std::string &message) {
  if (!this->_server.isExistChannel(channelName)) {
    this->_server.sendReply(sender.getFd(),
                            Replies::ERR_CANNOTSENDTOCHAN(channelName));
    return;
  }

  Channel &sendTo = this->_server.getChannel(channelName);

  if (!sendTo.isUserInChannel(sender)) {
    this->_server.sendReply(sender.getFd(),
                            Replies::ERR_CANNOTSENDTOCHAN(channelName));
    return;
  }
  sendTo.broadcastMessage(message, sender);
}

void CommandHandler::sendPrivMessageUser(const User &sender,
                                         const std::string &nick,
                                         const std::string &message) {
  if (!this->_server.isRegiNick(nick)) {
    this->_server.sendReply(sender.getFd(), Replies::ERR_NOSUCHNICK(nick));
    return;
  }
  User &sendTo = this->_server.findUser(nick);

  this->_server.sendReply(sendTo.getFd(), message);
}

void CommandHandler::sendPrivMessage(const User &user,
                                     const std::vector<std::string> &sendTo,
                                     const std::string &message) {
  std::string privMessage;

  for (std::size_t i = 0; i < sendTo.size(); i++) {
    privMessage = createPrivMessage(sendTo.at(i), message);
    if (isValidChannelName(sendTo.at(i))) {
      sendPrivMessageChannel(user, sendTo.at(i), privMessage);
    } else {
      sendPrivMessageUser(user, sendTo.at(i), privMessage);
    }
  }
}

void CommandHandler::PRIVMSG(User &user) {
  if (this->_params.size() < 1) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NORECIPIENT(this->_command));
    return;
  }
  if (this->_params.size() < 2) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NOTEXTTOSEND());
    return;
  }

  std::vector<std::string> sendTo;
  std::string message;

  CreateParamToOneString(message);
  splitStringByColon(this->_params.at(0), sendTo);

  sendPrivMessage(user, sendTo, message);
}
