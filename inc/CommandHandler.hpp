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
  CommandHandler(Server &server);
  ~CommandHandler();
  void handleCommand(const std::string &message, const int fd);

private:
  CommandHandler();
  Server &_server;

  std::string _prefix;
  std::string _command;
  std::vector<std::string> _params;
  std::string _reply;

  // parseMessage
  void parseMessage(const std::string &message);
  void extractPrefix(std::istringstream &iss);
  void extractCommand(std::istringstream &iss);
  void extractParam(std::istringstream &iss);

  // checkRegisterdState
  bool checkRegisterdState(const User &user);

  // executeCommand
  void executeCommand(User &user);

  // command
  const std::string PASS(User &user);
  const std::string USER(User &user);
  const std::string NICK(User &user);
  void JOIN(User &user);
  
  // nick method
  void convertChar(std::string &str);
  bool isSpecialChar(const char c);
  bool validateNick(const std::string &str);

  // join method
  void splitChannelAndKey(std::vector<std::string> &channels,
                                          std::vector<std::string> &keys);
  bool isValidChannelName(const std::string &channelName);
  bool hasReachedChannelLimit(const User &user);
  bool verifyChannelKey(const Channel &channel, const std::string &key);
  bool checkBanStatus(const Channel &channel,
                                    const std::string &nickname);
  bool checkChannelCapacity(const Channel &channel);
  bool checkInviteOnlyStatus(const Channel &channel);
  bool validateChannelMask(const Channel &channel,
                                           const std::string &nickname);
  bool evaluateChannelJoinCondition(const User &user, const Channel &channel,
                                    const std::string &key);
  void sendTopicReply(const User &user, const Channel &channel) const;
  void sendNamReply(const User &user, const Channel &channel) const;
  void sendEndOfNamesReply(const User &user, const Channel &channel) const;
  void sendJoinResponses(const User &user, const Channel &channel) const;

  // debug
  void printStringAsInts(const std::string &input);
  void printVectorString(const std::vector<std::string> &vec);
  };

#endif
