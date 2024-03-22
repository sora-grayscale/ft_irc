#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::replyRegistered(const User &user) const {
  const std::string &nick = user.getNickName();
  const std::string &username = user.getUserName();
  const std::string &date = this->_server.getStartDay();
  const std::string host = SERVER_NAME;
  const std::string ver = SERVER_VERSION;
  const std::string availUserMode = "aiwroOs";
  const std::string availChannnelMode = "aimnqpsrtklbeI";
  const int &fd = user.getFd();

  // RPL_WELCOME
  this->_server.sendReply(fd, Replies::RPL_WELCOME(nick, username, host));
  // RPL_YOURHOST
  this->_server.sendReply(fd, Replies::RPL_YOURHOST(host, ver));
  // RPL_CREATED
  this->_server.sendReply(fd, Replies::RPL_CREATED(date));
  // RPL_MYINFO
  this->_server.sendReply(
      fd, Replies::RPL_MYINFO(host, ver, availUserMode, availChannnelMode));
}

bool CommandHandler::isSpecialChar(const char c) {
  const std::string special = "[]\\`_^{|}";
  return special.find(c) != std::string::npos;
}

bool CommandHandler::validateNick(const std::string &str) {
  for (std::size_t i = 0; i < str.size(); ++i) {
    char c = str.at(i);
    if (i == 0) {
      if (!std::isalpha(static_cast<unsigned char>(c)) && !isSpecialChar(c))
        return (false);
    } else if (!std::isalnum(static_cast<unsigned char>(c)) &&
               !isSpecialChar(c) && c != '-') {
      return (false);
    }
  }
  return (true);
}

void CommandHandler::convertChar(std::string &str) {
  for (std::size_t i = 0; i < str.size(); ++i) {
    switch (str.at(i)) {
    case '{':
      str.at(i) = '[';
      break;
    case '}':
      str.at(i) = ']';
      break;
    case '|':
      str.at(i) = '\\';
      break;
    case '^':
      str.at(i) = '~';
      break;
    default:
      break;
    }
  }
}

bool CommandHandler::isReservedNick(const std::string &nick) {
  if (nick == OPER_USER || nick == ADMIN_NAME || nick == ANON_NAME) {
    return (true);
  }
  return (false);
}

void CommandHandler::NICK(User &user) {
  if (this->_params.size() == 0) {
    this->_server.sendReply(user.getFd(), Replies::ERR_NONICKNAMEGIVEN());
    return;
  }

  // state の確認
  if ((user.getState() & User::PASS) == 0) {
    return;
  }

  // nick paramのバリデーション
  if (this->_params.at(0).size() > 9 || !validateNick(this->_params.at(0))) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_ERRONEUSNICKNAME(this->_params.at(0)));
    return;
  }

  // チャンネル名との競合を防ぐ処理
  if (this->isValidChannelName(this->_params.at(0))) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_ERRONEUSNICKNAME(this->_params.at(0)));
    return;
  }

  // 変換 { →[, } → ], | → \, ^ → ~
  convertChar(this->_params.at(0));

  // historyに存在するかどうか,this->serverにnickHistoryのsetが存在する
  if (this->_server.isNick(this->_params.at(0)) != 0) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NICKNAMEINUSE(this->_params.at(0)));
    return;
  }

  // 予約された名前の拒否
  if (isReservedNick(this->_params.at(0))) {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_NICKNAMEINUSE(this->_params.at(0)));
    return;
  }

  if (user.hasMode(User::Restricted)) {
    this->_server.sendReply(user.getFd(), Replies::ERR_RESTRICTED());
    return;
  }

  // success reply
  std::string successMessage;
  successMessage = this->_server.createUserPrefix(user);
  successMessage += "NIKC :";
  successMessage += this->_params.at(0);
  successMessage += "\r\n";

  // set
  user.setNickName(this->_params.at(0));
  this->_server.setNickHistory(user.getNickName());

  // 初期登録かどうかの判別
  if (user.getState() != User::REGISTERD) {
    user.setState(User::NICK, true);
    if (user.getState() == User::REGISTERD) {
      replyRegistered(user);
      this->_server.addRegisterMap(user.getFd(), user);
      this->_server.eraseTmpMap(user.getFd());
    }
  } else {
    this->_server.sendReply(user.getFd(), successMessage);
  }
  return;
}
