#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

class Server;

#include "Channel.hpp"
#include "Replies.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <sstream>
#include <ctime>
#include <string>
#include <vector>

#define USER_CHANNEL_LIMIT 10

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
  void PASS(User &user);
  void USER(User &user);
  void NICK(User &user);
  void OPER(User &user);
  void JOIN(User &user);
  void MOTD(User &user);
  void LUSERS(User &user);
  void VERSION(User &user);
  void LINKS(User &user);
  void TIME(User &user);
  void CONNECT(User &user);
  void TRACE(User &user);
  void ADMIN(User &user);
  void INFO(User &user);

  // nick method
  void convertChar(std::string &str);
  bool isSpecialChar(const char c);
  bool validateNick(const std::string &str);

  // join method
  void splitChannelAndKey(std::vector<std::string> &channels,
                          std::vector<std::string> &keys) const;
  bool isValidChannelName(const std::string &channelName) const;
  bool hasReachedChannelLimit(const User &user) const;
  bool verifyChannelKey(const Channel &channel, const std::string &key) const;
  bool checkBanStatus(const Channel &channel,
                      const std::string &nickname) const;
  bool checkChannelCapacity(const Channel &channel) const;
  bool checkInviteOnlyStatus(const Channel &channel,
                             const std::string &nickname) const;
  bool evaluateChannelJoinCondition(const User &user, const Channel &channel,
                                    const std::string &key) const;
  void addUserToChannel(User &user, Channel &channel) const;
  void sendTopicReply(const User &user, const Channel &channel) const;
  void sendNamReply(const User &user, const Channel &channel) const;
  void sendEndOfNamesReply(const User &user, const Channel &channel) const;
  void sendJoinResponses(const User &user, const Channel &channel) const;

  // debug
  void printStringAsInts(const std::string &input);
  void printVectorString(const std::vector<std::string> &vec);
};

#endif
