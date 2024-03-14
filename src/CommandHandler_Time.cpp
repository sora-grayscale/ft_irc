#include "CommandHandler.hpp"

void CommandHandler::TIME(User &user) {
  if (!(this->_params.size() == 0)) {
    if (this->_params.at(0) != this->_server.getServerName()) {
      this->_server.sendReply(user.getFd(),
                              Replies::ERR_NOSUCHSERVER(this->_params.at(0)));
      return;
    }
  }
  std::stringstream ss;
  std::string time;

  std::time_t result = std::time(NULL);
  ss << std::ctime(&result);
  time = ss.str();
  this->_server.sendReply(
      user.getFd(), Replies::RPL_TIME(this->_server.getServerName(), time));
}
