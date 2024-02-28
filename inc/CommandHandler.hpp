#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <string>
#include <vector>
#include <sstream>
#include "User.hpp"
#include "Channel.hpp"

class CommandHandler {
public:
  CommandHandler();
  ~CommandHandler();
  void handleCommand(const std::string &command, User &user);
  void handleCommand(const std::string &command, User &user, Channel &channel);
  void parseMessage(const std::string &message);

private:
  std::string _prefix;
  std::string _command;
  std::vector<std::string> _params;

  void executeCommand(const std::string &commandName,
                      const std::vector<std::string> &params, User &user);
  void extractPrefix(std::istringstream &iss);
  void extractCommand(std::istringstream &iss);

};

#endif
