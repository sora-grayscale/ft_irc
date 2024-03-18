#include "CommandHandler.hpp"

void CommandHandler::QUIT(User &user) {
  // userに対してERRORで接続の終了を通達
  sendError(user.getFd(), "Terminate server connection\n\rThank you for using "
                          "our IRCserver :)\n\r");
  // その後deleteUser
  std::string message;
  message += "QUIT :";
  if (this->_params.size() > 1) {
    for (std::size_t i = 0; i < this->_params.size(); i++) {
      message += " ";
      message += this->_params.at(i);
    }
  }
  message += "\n\r";
  this->_server.delUser(user, message);
}
