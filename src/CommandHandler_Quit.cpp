#include "CommandHandler.hpp"

void CommandHandler::QUIT(User &user) {
  // userに対してERRORで接続の終了を通達
  sendError(user.getFd(), "Terminate server connection\n\rThank you for using "
                          "our IRCserver :)\n\r");
  // その後deleteUser
  std::string message;
  message += "QUIT :";
  if (this->_params.size() >= 1) {
    for (std::size_t i = 0; i < this->_params.size(); i++) {
      if (i != 0) {
        message += " ";
      }

      if (i == 0 && this->_params.at(0).at(0) == ':') {
        if (this->_params.at(i).size() != 1) {
          message += this->_params.at(i).substr(1);
        }
      } else {
        message += this->_params.at(i);
      }
    }
  }
  message += "\n\r";
  this->_server.delUser(user, message);
}
