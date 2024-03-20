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

void CommandHandler::handleChannnelMode(User &user) { (void)user; }

void CommandHandler::handleUserMode(User &user) {
  // error
  if (!this->_server.isRegiNick(user.getNickName())) {
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
                            Replies::RPL_UMODEIS(generateUserModeString(user)));
    return;
  }

  // <modestring> is given
  if (2 <= this->_params.size()) {
    if (!checkUserModeFlag(this->_params.at(1))) {
      this->_server.sendReply(user.getFd(), Replies::ERR_UMODEUNKNOWNFLAG());
      return;
    }
    setUserModeFlag(user, this->_params.at(1));
  }
}

const std::string CommandHandler::generateUserModeString(const User &user) {
  std::string mode = "";
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
