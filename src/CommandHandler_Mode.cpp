#include "CommandHandler.hpp"

void CommandHandler::MODE(User &user) {
  if (this->_params.size() == 0) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NEEDMOREPARAMS(this->_command));
    return;
  }

  if (this->isValidChannelName(this->_params.at(0))) {
    handleChannnelMode(user);
  } else {
    handleUserMode(user);
  }
}

// Channel Mode
void CommandHandler::handleChannnelMode(User &user) {
  const std::string &channelName = this->_params.at(0);

  // error
  if (!this->_server.isExistChannel(channelName)) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOSUCHCHANNEL(channelName));
    return;
  }

  Channel &channel = this->_server.getChannel(channelName);

  // <modestring> is not given
  if (this->_params.size() == 1) {
    sendChannelModeAndCreationTimeResponse(user, channelName, channel);
    return;
  }

  // <modestring> is given
  const std::string mode = removeDuplicates(this->_params.at(1));
  char invalidChar;
  unsigned int modeFlag = Channel::None;

  // check valid Mode
  if (!checkChannelModeFlag(this->_params.at(1))) {
    std::size_t pos =
        this->_params.at(1).find_first_not_of("+-OovaimnqpsrtklbeI");
    if (pos == std::string::npos) {
      pos = this->_params.at(1).find_first_of("OovaimnqpsrtklbeI");
    }
    Server::sendReply(
        user.getFd(),
        Replies::ERR_UNKNOWNMODE(this->_params.at(1).at(pos), channelName));
    return;
  }

  if (!checkChannelModeSyntax(mode, invalidChar, modeFlag)) {
    replySyntaxError(user, channelName, invalidChar);
    return;
  }

  // check Operator privis
  if (isOperatorNeed(mode, modeFlag)) {
    if (!channel.isUserInChannel(user)) {
      Server::sendReply(user.getFd(), Replies::ERR_NOTONCHANNEL(channelName));
      return;
    }
    if (!channel.hasUserStatus(user, Channel::Operator)) {
      Server::sendReply(user.getFd(),
                        Replies::ERR_CHANOPRIVSNEEDED(channelName));
      return;
    }
  }

  // set and reply
  channelModeSetAndReply(user, channel, channelName, mode);
}

const std::string CommandHandler::generateModeString(const Channel &channel) {
  std::string mode = "";

  if (channel.hasChannleMode(Channel::ChannelCreator)) {
    mode += "O";
  }
  if (channel.hasChannleMode(Channel::ChannelOperator)) {
    mode += "o";
  }
  if (channel.hasChannleMode(Channel::ChannelVoice)) {
    mode += "v";
  }
  if (channel.hasChannleMode(Channel::Anonymous)) {
    mode += "a";
  }
  if (channel.hasChannleMode(Channel::InviteOnly)) {
    mode += "i";
  }
  if (channel.hasChannleMode(Channel::Moderated)) {
    mode += "m";
  }
  if (channel.hasChannleMode(Channel::NoOutside)) {
    mode += "n";
  }
  if (channel.hasChannleMode(Channel::Quiet)) {
    mode += "q";
  }
  if (channel.hasChannleMode(Channel::Private)) {
    mode += "p";
  }
  if (channel.hasChannleMode(Channel::Secret)) {
    mode += "s";
  }
  if (channel.hasChannleMode(Channel::ServerReop)) {
    mode += "r";
  }
  if (channel.hasChannleMode(Channel::TopicOpOnly)) {
    mode += "t";
  }
  if (channel.hasChannleMode(Channel::Key)) {
    mode += "k";
  }
  if (channel.hasChannleMode(Channel::Limit)) {
    mode += "l";
  }
  if (channel.hasChannleMode(Channel::BanMask)) {
    mode += "b";
  }
  if (channel.hasChannleMode(Channel::ExceptionMask)) {
    mode += "e";
  }
  if (channel.hasChannleMode(Channel::InvitationMask)) {
    mode += "I";
  }
  return (mode);
}

void CommandHandler::sendChannelModeAndCreationTimeResponse(
    const User &user, const std::string &channelName, const Channel &channel) {
  const std::string mode = generateModeString(channel);
  if (mode.find_first_of("l") == std::string::npos) {
    Server::sendReply(user.getFd(),
                      Replies::RPL_CHANNELMODEIS(channelName, mode));
  } else {
    Server::sendReply(
        user.getFd(),
        Replies::RPL_CHANNELMODEIS(channelName, mode, channel.getUserLimit()));
  }
  Server::sendReply(
      user.getFd(),
      Replies::RPL_CREATIONTIME(channelName, channel.getChannelCreatedTime()));
}

bool CommandHandler::checkChannelModeFlag(const std::string &flag) {
  if (flag.empty()) {
    return (false);
  }

  if (flag.find_last_of("+-") != 0) {
    return (false);
  }

  if (flag.find_first_not_of("+-OovaimnqpsrtklbeI") != std::string::npos) {
    return (false);
  }
  return (true);
}

const std::string CommandHandler::removeDuplicates(const std::string &str) {
  std::string result;

  for (std::size_t i = 0; i < str.size(); i++) {
    if (result.find(str.at(i)) == std::string::npos) {
      result += str.at(i);
    }
  }
  return (result);
}

bool CommandHandler::checkChannelModeSyntax(const std::string &mode, char &c,
                                            unsigned int &modeFlag) {
  std::size_t countModeparams = 0;

  for (std::size_t i = 0; i < mode.size(); i++) {

    if (mode.at(i) == 'O') {
      c = 'O';
      countModeparams++;
    } else if (mode.at(i) == 'o') {
      c = 'o';
      countModeparams++;
    } else if (mode.at(i) == 'v') {
      c = 'v';
      countModeparams++;
    } else if (mode.at(i) == 'k') {
      c = 'k';
      countModeparams++;
    } else if (mode.at(i) == 'l' && mode.at(0) == '+') {
      c = 'l';
      countModeparams++;
    } else if (mode.at(i) == 'b' &&
               countModeparams < this->_params.size() - 2) {
      countModeparams++;
      modeFlag |= Channel::BanMask;
    } else if (mode.at(i) == 'e' &&
               countModeparams < this->_params.size() - 2) {
      countModeparams++;
      modeFlag |= Channel::ExceptionMask;
    } else if (mode.at(i) == 'I' &&
               countModeparams < this->_params.size() - 2) {
      countModeparams++;
      modeFlag |= Channel::InvitationMask;
    }

    if (countModeparams >= this->_params.size() - 1) {
      return (false);
    }
  }
  return (true);
}

void CommandHandler::replySyntaxError(const User &user,
                                      const std::string &channelName,
                                      const char c) {
  if (c == 'O') {
    Server::sendReply(
        user.getFd(),
        channelName +
            " :Invalid creator mode parameter. Syntax: <creator>.\r\n");
  } else if (c == 'o') {
    Server::sendReply(
        user.getFd(),
        channelName +
            " :Invalid operator mode parameter. Syntax: <operator>.\r\n");
  } else if (c == 'v') {
    Server::sendReply(
        user.getFd(),
        channelName + " :Invalid voice mode parameter. Syntax: <voice>.\r\n");
  } else if (c == 'k') {
    Server::sendReply(user.getFd(),
                      channelName +
                          " :Invalid key mode parameter. Syntax: <key>.\r\n");
  } else if (c == 'l') {
    Server::sendReply(
        user.getFd(),
        channelName + " :Invalid limit mode parameter. Syntax: <limit>.\r\n");
  }
}

bool CommandHandler::isAlreadySetKey(const std::string &modes) {
  if (modes.empty()) {
    return (false);
  } else if (modes.find("k") != std::string::npos) {
    return (true);
  }
  return (false);
}

bool CommandHandler::isOperatorNeed(const std::string &mode,
                                    const unsigned int &modeFlag) {
  if (mode.find_first_not_of("beI") != std::string::npos) {
    return (true);
  } else if ((modeFlag & Channel::BanMask) != 0 ||
             (modeFlag & Channel::ExceptionMask) != 0 ||
             (modeFlag & Channel::InvitationMask) != 0) {
    return (true);
  }
  return (false);
}

void CommandHandler::channelModeSetAndReply(const User &user, Channel &channel,
                                            const std::string &channelName,
                                            const std::string &mode) {
  bool enable = false;
  std::size_t paramPos = 2;

  if (mode.at(0) == '+') {
    enable = true;
  }

  for (std::size_t i = 0; i < mode.size(); i++) {
    if (mode.at(i) == 'O' || mode.at(i) == 'o' || mode.at(i) == 'v') {
      if (!handleCreOpeVoiMode(user, channel, channelName, paramPos)) {
        continue;
      }
      User &tmpUser = this->_server.findUser(this->_params.at(paramPos));
      paramPos++;
      if (mode.at(i) == 'O') {
        // channel.setUserStatus(tmpUser, Channel::Creator, enable);
      } else if (mode.at(i) == 'o') {
        channel.setUserStatus(tmpUser, Channel::Operator, enable);
      } else if (mode.at(i) == 'v') {
        channel.setUserStatus(tmpUser, Channel::Voice, enable);
      }
    } else if (mode.at(i) == 'a') {
      channel.setChannelMode(Channel::Anonymous, enable);
    } else if (mode.at(i) == 'i') {
      channel.setChannelMode(Channel::InviteOnly, enable);
    } else if (mode.at(i) == 'm') {
      channel.setChannelMode(Channel::Moderated, enable);
    } else if (mode.at(i) == 'n') {
      channel.setChannelMode(Channel::NoOutside, enable);
    } else if (mode.at(i) == 'q') {
      channel.setChannelMode(Channel::Quiet, enable);
    } else if (mode.at(i) == 'p') {
      channel.setChannelMode(Channel::Private, enable);
    } else if (mode.at(i) == 's') {
      channel.setChannelMode(Channel::Secret, enable);
    } else if (mode.at(i) == 'r') {
      channel.setChannelMode(Channel::ServerReop, enable);
    } else if (mode.at(i) == 't') {
      channel.setChannelMode(Channel::TopicOpOnly, enable);
    } else if (mode.at(i) == 'k') {
      if (!handleKeyMode(user, channel, channelName, enable, paramPos)) {
        continue;
      }
      channel.setChannelMode(Channel::Key, enable);
    } else if (mode.at(i) == 'l') {
      if (!handleLimitMode(user, channel, channelName, enable, paramPos)) {
        continue;
      }
      channel.setChannelMode(Channel::Limit, enable);
    } else if (mode.at(i) == 'b') {
      handleBanMode(user, channel, channelName, enable, paramPos);
      channel.setChannelMode(Channel::BanMask, enable);
    } else if (mode.at(i) == 'e') {
      handleExceptionMode(user, channel, channelName, enable, paramPos);
      channel.setChannelMode(Channel::ExceptionMask, enable);
    } else if (mode.at(i) == 'I') {
      handleInvitationMode(user, channel, channelName, enable, paramPos);
      channel.setChannelMode(Channel::InvitationMask, enable);
    }
  }
  sendChannelModeAndCreationTimeResponse(user, channelName, channel);
}

bool CommandHandler::handleCreOpeVoiMode(const User &user, Channel &channel,
                                         const std::string &channelName,
                                         std::size_t &paramPos) {
  if (!channel.isUserInChannel(this->_params.at(paramPos))) {
    Server::sendReply(
        user.getFd(),
        Replies::ERR_USERNOTINCHANNEL(this->_params.at(paramPos), channelName));
    paramPos++;
    return (false);
  }
  return (true);
}

bool CommandHandler::handleKeyMode(const User &user, Channel &channel,
                                   const std::string &channelName,
                                   const bool &enable, std::size_t &paramPos) {
  if (enable == true) {
    if (isAlreadySetKey(generateModeString(channel))) {
      Server::sendReply(user.getFd(), Replies::ERR_KEYSET(channelName));
      paramPos++;
      return (false);
    }
    channel.setKey(this->_params.at(paramPos));
  } else {
    if (channel.getKey() != this->_params.at(paramPos)) {
      Server::sendReply(user.getFd(), Replies::ERR_KEYSET(channelName));
      paramPos++;
      return (false);
    }
  }
  paramPos++;
  return (true);
}

bool CommandHandler::handleLimitMode(const User &user, Channel &channel,
                                     const std::string &channelName,
                                     const bool &enable,
                                     std::size_t &paramPos) {
  if (enable == true) {
    std::size_t num;
    std::istringstream iss(this->_params.at(paramPos));
    paramPos++;
    iss >> num;
    if (iss.fail() || iss.bad()) {
      // notice not a num
      Server::sendReply(user.getFd(),
                        Replies::ERR_UNKNOWNMODE('l', channelName));
      return (false);
    }
    channel.setUserLimit(num);
  }
  return (true);
}

void CommandHandler::handleBanMode(const User &user, Channel &channel,
                                   const std::string &channelName,
                                   const bool &enable, std::size_t &paramPos) {
  if (paramPos < this->_params.size()) {
    if (enable == true) {
      channel.addBanMask(this->_params.at(paramPos));
    } else {
      channel.removeBanMask(this->_params.at(paramPos));
    }
    paramPos++;
  }
  for (std::set<std::string>::const_iterator it = channel.getBanMaskBegin();
       it != channel.getBanMaskEnd(); it++) {
    Server::sendReply(user.getFd(), Replies::RPL_BANLIST(channelName, *it));
  }
  Server::sendReply(user.getFd(), Replies::RPL_ENDOFBANLIST(channelName));
}

void CommandHandler::handleExceptionMode(const User &user, Channel &channel,
                                         const std::string &channelName,
                                         const bool &enable,
                                         std::size_t &paramPos) {
  if (paramPos < this->_params.size()) {
    if (enable == true) {
      channel.addExceptionMask(this->_params.at(paramPos));
    } else {
      channel.removeExceptionMask(this->_params.at(paramPos));
    }
    paramPos++;
  }
  for (std::set<std::string>::const_iterator it =
           channel.getExceptionMaskBegin();
       it != channel.getExceptionMaskEnd(); it++) {
    Server::sendReply(user.getFd(), Replies::RPL_EXCEPTLIST(channelName, *it));
  }
  Server::sendReply(user.getFd(), Replies::RPL_ENDOFEXCEPTLIST(channelName));
}

void CommandHandler::handleInvitationMode(const User &user, Channel &channel,
                                          const std::string &channelName,
                                          const bool &enable,
                                          std::size_t &paramPos) {
  if (paramPos < this->_params.size()) {
    if (enable == true) {
      channel.addInvitationMask(this->_params.at(paramPos));
    } else {
      channel.removeInvitationMask(this->_params.at(paramPos));
    }
    paramPos++;
  }
  for (std::set<std::string>::const_iterator it =
           channel.getInvitationMaskBegin();
       it != channel.getInvitationMaskEnd(); it++) {
    Server::sendReply(user.getFd(), Replies::RPL_INVITELIST(channelName, *it));
  }
  Server::sendReply(user.getFd(), Replies::RPL_ENDOFINVITELIST(channelName));
}

// User Mode
void CommandHandler::handleUserMode(User &user) {
  // error
  if (!this->_server.isRegiNick(this->_params.at(0))) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NOSUCHNICK(this->_command));
    return;
  } else if (this->_params.at(0) != user.getNickName()) {
    this->_server.sendReply(user.getFd(), Replies::ERR_USERSDONTMATCH());
    return;
  }

  // <modestring> is not given
  if (this->_params.size() == 1) {
    this->_server.sendReply(user.getFd(),
                            Replies::RPL_UMODEIS(generateModeString(user)));
    return;
  }

  // <modestring> is given
  if (2 <= this->_params.size()) {
    if (!checkUserModeFlag(this->_params.at(1))) {
      this->_server.sendReply(user.getFd(), Replies::ERR_UMODEUNKNOWNFLAG());
      return;
    }
    setUserModeFlag(user, this->_params.at(1));
    Server::sendReply(user.getFd(),
                      Replies::RPL_UMODEIS(generateModeString(user)));
  }
}

const std::string CommandHandler::generateModeString(const User &user) {
  std::string mode;

  if (user.hasMode(User::Away)) {
    mode += "a";
  }
  if (user.hasMode(User::Invisible)) {
    mode += "i";
  }
  if (user.hasMode(User::Wallops)) {
    mode += "w";
  }
  if (user.hasMode(User::Restricted)) {
    mode += "r";
  }
  if (user.hasMode(User::Operator)) {
    mode += "o";
  }
  if (user.hasMode(User::LocalOperator)) {
    mode += "O";
  }
  if (user.hasMode(User::ServerNotices)) {
    mode += "s";
  }
  return (mode);
}

bool CommandHandler::checkUserModeFlag(const std::string &flag) {
  if (flag.empty()) {
    return (false);
  }

  if (flag.find_last_of("+-") != 0) {
    return (false);
  }

  if (flag.find_first_not_of("+-iwoOr") != std::string::npos) {
    return (false);
  }
  return (true);
}

void CommandHandler::setUserModeFlag(User &user, const std::string &flag) {
  bool enable = false;

  if (flag.at(0) == '+') {
    enable = true;
  }

  if (flag.find_first_of("i") != std::string::npos) {
    user.setMode(User::Invisible, enable);
  }
  if (flag.find_first_of("w") != std::string::npos) {
    user.setMode(User::Wallops, enable);
  }

  //  bypass the operator
  if (enable == false) {
    if (flag.find_first_of("o") != std::string::npos) {
      user.setMode(User::Operator, enable);
    }
    if (flag.find_first_of("O") != std::string::npos) {
      user.setMode(User::LocalOperator, enable);
    }
  }

  //  bypass the restricted
  if (enable == true) {
    if (flag.find_first_of("r") != std::string::npos) {
      user.setMode(User::Restricted, enable);
    }
  }
}
