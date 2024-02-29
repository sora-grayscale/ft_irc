#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "Replies.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <string>
#include <vector>
#include <sstream>

class CommandHandler {
public:
  void handleCommand(const std::string &command, User &user);
  void handleCommand(const std::string &command, User &user, Channel &channel);

  CommandHandler(Server &server);
  ~CommandHandler();
  Server &_server;
  std::string _prefix;
  std::string _command;
  std::vector<std::string> _params;

  Server &_server;

  void parseCommand(const std::string &commad);
  void executeCommand(const std::string &commandName,
                      const std::vector<std::string> &params, User &user);
  // command

  // command
  const std::string PASS(User &user);
  const std::string USER(User &user);

};

#endif
