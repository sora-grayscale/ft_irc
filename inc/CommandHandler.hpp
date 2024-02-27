#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <string>
#include <vector>

class CommandHandler {
public:
  void handleCommad(const std::string &command, User &user);

private:
  Server &_server;

  void parseCommand(const std::string &commad);
  void executeCommand(const std::string &commandName,
                      const std::vector<string> &params, User &user);
  // command
  std::string PASS(const std::string &commandName,
                   const std::vector<string> &params, User &user);
};

#endif
