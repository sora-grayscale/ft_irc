#include "CommandHandler.hpp"

CommandHandler::CommandHandler(const Server &server) : _server(server) {}
std::string CommandHandler::PASS(const std::string &commandName,
                                 const std::vector<std::string> &params,
                                 User &user) {
  if (params.size() < 1)
    return Replies::ERR_NEEDMOREPARAMS(commandName);
  if (user.getState() != User::NONE)
    return Replies::ERR_ALREADYREGISTRED();
  if (params.at(0) != this->_server.getPassword())
    return "";
  user.setState(User::PASS);
  return "";
}

std::string CommandHandler::USER(const std::string &commandName,
                                 const std::vector<std::string> &params,
                                 User &user) {
  const int REAL_NAME_MAX_LEN = 63;

  // paramsを確認
  if (params.size() < 4)
    return Replies::ERR_NEEDMOREPARAMS(commandName);
  // statusを確認
  if (user.getState() != User::NONE)
    return "";
  // stateが4,5,7だったら弾く(4以上)
  if (user.getState() >= User::USER)
    return Replies::ERR_ALREADYREGISTRED();

  // user処理
  // params[0]のバリデート
  if (params[0].empty() || params[1].empty() || params[2].empty() ||
      params[3].empty())
    return "";

  // params[0]のバリデート user
  for (std::size_t i = 0; i < params[0].size(); ++i) {
    char c = params[0].at(i);
    if (c == '@' || c == '\n' || !c)
      return "";
  }

  // params[1]のバリデート mode
  int mode;
  if (params[1].size() != 1)
    return "";
  char c = params[1].at(0);
  if (!std::isalnum(static_cast<unsigned char>(c)))
    return "";
  mode = params[1].at(0) - '0';
  if (mode > 3)
    return "";

  // params[2]のバリデート unused
  // do nothing

  // params[3]以降のバリデートrealname
  std::string realname;
  for (std::size_t i = 3; i < params.size(); ++i) {
    if (i == 3 && params[3].at(0) == ':')
      realname = params[3].substr(1);
    else if (i != params.size() - 1) {
      realname += " ";
      realname += params[i];
    } else
      realname += params[i];
    if (realname.size() > REAL_NAME_MAX_LEN)
      return "";
  }

  // 全部ok setをする
  user.setUserName(params[0]);
  user.setMode(mode, true);
  user.setRealName(realname);
  user.setState(User::USER);

  // 登録済みのmapに移動させる
  if (user.getState() == User::REGISTERD) {
  }

  return "";
}

