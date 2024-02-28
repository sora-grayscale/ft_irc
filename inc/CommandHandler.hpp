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
  void handleCommand(const std::string &command, User &user);
  void handleCommand(const std::string &command, User &user, Channel &channel);
  void parseMessage(const std::string &message);

private:
  std::string _prefix;
  std::string _command;
  std::vector<std::string> _params;
  const Server &_server;

  void executeCommand(const std::string &commandName,
                      const std::vector<std::string> &params, User &user);
  void extractPrefix(std::istringstream &iss);
  void extractCommand(std::istringstream &iss);

  // command
  const std::string PASS(const std::string &commandName,
                         const std::vector<std::string> &params, User &user);
};

#endif
