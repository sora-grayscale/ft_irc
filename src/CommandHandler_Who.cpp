#include "CommandHandler.hpp"

void displayWhoQuery(const int fd, const std::string &str, bool flag)
{
    if (str == '0')
      // displayAllUser();
    else if (str 実在するチャンネル)
      // displayChannelUser();
    else if (str == "127.0.0.1")
      // displayAllUser();
    else if (str == SERVER_NAME)
      // displayAllUser();
    else if (str == リアルネーム)
      // displayUser();
    else if (str == ニックネーム)
      // displayUser();
    else
      this->_server.sendReply(fd, Replies::ERR_NOSUCHSERVER(str));

}

void CommandHandler::WHO(User &user) {
  if (this->_params.size() == 0) {
    // displayAllUser();
  }
  else if (this->_params.size() == 1) {
    displayWhoQuery(user.getFd(), this->_params.at(0), false);
    return ;
  }
  else if (this->_params.size() >= 2) {
    if (this->_params.at(1) == 'o')
      displayWhoQuery(user.getFd(), this->_params.at(0), true);
  }
  this->_server.sendReply(user.getFd(), Replies::ERR_NOSUCHSERVER(str));
}
