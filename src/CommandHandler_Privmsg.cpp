#include "CommandHandler.hpp"

void CommandHandler::CreatePrivMessage(std::string &message) {
  for (std::size_t i = 1; i < this->_params.size(); i++) {
    if (i != 1) {
      message += " ";
    }

    if (i == 1 && this->_params.at(i).at(i) == ':') {
      if (this->_params.at(i).size() != 1) {
        message = this->_params.at(i).substr(1);
      }
    } else {
      message += this->_params.at(i);
    }
  }
}

void CommandHandler::sendPrivMessageChannel(const User &sender,
                                            const std::string &channelName,
                                            const std::string &message) {
  if (!this->_server.isExistChannel(channelName)) {
    // ERR_CANNOTSENDTOCHAN
    (void)sender;
    return;
  }

  Channel &sendTo = this->_server.getChannel(channelName);

  if (!sendTo.isUserInChannel(sender)) {
    // ERR_CANNOTSENDTOCHAN
    (void)sender;
    return;
  }
  sendTo.broadcastMessage(message, sender.getFd());
}

void CommandHandler::sendPrivMessageUser(const User &sender,
                                            const std::string &nick,
                                            const std::string &message) {
  if (!this->_server.isRegiNick(nick)) {
    // ERR_NOSUCHNICK
    (void)sender;
    return;
  }
  User &sendTo = this->_server.findUser(nick);

  this->_server.sendReply(sendTo.getFd(), message);
}

void CommandHandler::sendPrivMessage(const User &user,
                                     const std::vector<std::string> &sendTo,
                                     const std::string &message) {
  std::string privMessage;

  for (std::size_t i = 0 ; i < sendTo.size() ; i++) {
    privMessage = "PRIVMSG ";
    privMessage += sendTo.at(i);
    privMessage += " ";
    privMessage += message;
    privMessage += "\n\r";

    if (isValidChannelName(sendTo.at(i))) {
      sendPrivMessageChannel(user, sendTo.at(i), privMessage);
    } else {
      sendPrivMessageUser(user, sendTo.at(i), privMessage);
    }
  }
}

void CommandHandler::PRIVMSG(User &user) {
  if (this->_params.size() < 1) {
    // ERR_NORECIPIENT
    return;
  }
  if (this->_params.size() < 2) {
    // ERR_NOTEXTTOSEND
    return;
  }

  std::vector<std::string> sendTo;
  std::string message;

  CreatePrivMessage(message);
  splitStringByColon(this->_params.at(0), sendTo);

  sendPrivMessage(user, sendTo, message);
}

/*
ERR_NORECIPIENT        受け手がいない
ERR_NOTEXTTOSEND       送信内容がない
ERR_CANNOTSENDTOCHAN   チャンネルprefixがあるけど送信できない
ERR_NOTOPLEVEL
ERR_WILDTOPLEVEL
ERR_TOOMANYTARGETS
ERR_NOSUCHNICK
RPL_AWAY
*/
