#include "CommandHandler.hpp"

void CommandHandler::handleCommand(const std::string &message, const int fd) {
  User &user = this->_server.findUser(fd);

  parseMessage(message);
  if (!checkRegisterdState(user)) {
    return;
  }
  executeCommand(user);
  return;
}

// The `parseMessage` function is implemented in a separate file.

bool CommandHandler::checkRegisterdState(const User &user) {
  std::string reply;
  if (user.getState() == User::NONE) {
    if (this->_command != "PASS") {
      reply = Replies::ERR_NOTREGISTERED();
      reply += " [You need PASS command first] \r\n";
      this->_server.sendReply(user.getFd(), reply);
      return (false);
    }
  } else if (user.getState() != User::REGISTERD) {
    if (this->_command != "PASS" && this->_command != "NICK" &&
        this->_command != "USER") {
      reply = Replies::ERR_NOTREGISTERED();
      reply += " [You can only use PASS, NICK, USER command now!] \r\n";
      this->_server.sendReply(user.getFd(), reply);
      return (false);
    }
  }
  return (true);
}

void CommandHandler::executeCommand(User &user) {
  if (this->_command == "PASS") {
    PASS(user);
  } else if (this->_command == "USER") {
    USER(user);
  } else if (this->_command == "NICK") {
    NICK(user);
  } else if (this->_command == "OPER") {
    OPER(user);
  } else if (this->_command == "QUIT") {
    QUIT(user);
  } else if (this->_command == "JOIN") {
    JOIN(user);
  } else if (this->_command == "PART") {
    PART(user);
  } else if (this->_command == "MODE") {
    MODE(user);
  } else if (this->_command == "TOPIC") {
    TOPIC(user);
  } else if (this->_command == "NAMES") {
    NAMES(user);
  } else if (this->_command == "LIST") {
    LIST(user);
  } else if (this->_command == "INVITE") {
    INVITE(user);
  } else if (this->_command == "KICK") {
    KICK(user);
  } else if (this->_command == "PRIVMSG") {
    PRIVMSG(user);
  } else if (this->_command == "NOTICE") {
    NOTICE(user);
  } else if (this->_command == "MOTD") {
    MOTD(user);
  } else if (this->_command == "LUSERS") {
    LUSERS(user);
  } else if (this->_command == "VERSION") {
    VERSION(user);
  } else if (this->_command == "LINKS") {
    LINKS(user);
  } else if (this->_command == "TIME") {
    TIME(user);
  } else if (this->_command == "CONNECT") {
    CONNECT(user);
  } else if (this->_command == "TRACE") {
    TRACE(user);
  } else if (this->_command == "ADMIN") {
    ADMIN(user);
  } else if (this->_command == "INFO") {
    INFO(user);
  } else if (this->_command == "WHO") {
    WHO(user);
  } else if (this->_command == "WHOIS") {
    WHOIS(user);
  } else if (this->_command == "WHOWAS") {
    WHOWAS(user);
  } else if (this->_command == "KILL") {
    KILL(user);
  } else if (this->_command == "PING") {
    PING(user);
  } else if (this->_command == "PONG") {
    PONG(user);
  } else {
    this->_server.sendReply(user.getFd(),
                            Replies::ERR_UNKNOWNCOMMAND(this->_command));
  }
}
