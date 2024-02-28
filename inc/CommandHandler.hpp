#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "Replies.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <string>
#include <vector>

class CommandHandler {
public:
  void handleCommand(const std::string &command, User &user);
  void handleCommand(const std::string &command, User &user, Channel &channel);

  CommandHandler(Server &server);
  ~CommandHandler();
private:
  Server &_server;

  void parseCommand(const std::string &commad);
  void executeCommand(const std::string &commandName,
                      const std::vector<std::string> &params, User &user);
  // command
  std::string PASS(const std::string &commandName,
                   const std::vector<std::string> &params, User &user);
  std::string USER(const std::string &commandName,
                   const std::vector<std::string> &params, User &user);
};

#endif
