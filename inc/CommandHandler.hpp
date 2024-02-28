#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

class Server;

#include "Channel.hpp"
#include "Replies.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <sstream>
#include <string>
#include <vector>

class CommandHandler {
public:
  CommandHandler();
  CommandHandler(const Server &server);
  ~CommandHandler();

  void handleCommand(const std::string &message);

private:
  const Server &_server;

  std::string _prefix;
  std::string _command;
  std::vector<std::string> _params;


  // parseMessage
  void parseMessage(const std::string &message);
  void extractPrefix(std::istringstream &iss);
  void extractCommand(std::istringstream &iss);
  void extractParam(std::istringstream &iss);

  // executeCommand
  void executeCommand(User &user);

  // command
  const std::string PASS(const std::string &commandName,
                         const std::vector<std::string> &params, User &user);
};

#endif
