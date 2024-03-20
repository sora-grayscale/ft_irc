#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

class Server;

#include "Channel.hpp"
#include "Replies.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <ctime>
#include <sstream>
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
  void QUIT(User &user);
  void JOIN(User &user);
  void PART(User &user);
  void MODE(User &user);
  void TOPIC(User &user);
  void NAMES(User &user);
  void LIST(User &user);
  void INVITE(User &user);
  void KICK(User &user);
  void MOTD(User &user);
  void LUSERS(User &user);
  void VERSION(User &user);
  void LINKS(User &user);
  void TIME(User &user);
  void CONNECT(User &user);
  void TRACE(User &user);
  void ADMIN(User &user);
  void INFO(User &user);
  void PRIVMSG(User &user);
  void NOTICE(User &user);
  void KILL(User &user);
  void WHO(User &user);
  void WHOIS(User &user);
  void WHOWAS(User &user);
  void PING(User &user);
  void PONG(User &user);
  void ERROR(User &user);

  // nick method
  void convertChar(std::string &str);
  bool isSpecialChar(const char c);
  bool validateNick(const std::string &str);
  bool isReservedNick(const std::string &nick);
  void replyRegistered(const User &user);

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
  bool evaluateChannelJoinCondition(const User &user,
                                    const Channel &channel) const;
  bool evaluateChannelJoinCondition(const User &user, const Channel &channel,
                                    const std::string &key) const;
  void addUserToChannel(User &user, Channel &channel,
                        Channel::UserStatusFlags mode) const;
  void sendTopicReply(const User &user, const Channel &channel) const;
  void sendNamReply(const User &user, const Channel &channel) const;
  void sendEndOfNamesReply(const User &user, const Channel &channel) const;
  void sendJoinResponses(const User &user, const Channel &channel) const;

  // part method
  void splitChannel(std::vector<std::string> &channels);

  // mode method
  void handleChannnelMode(User &user);
  void handleUserMode(User &user);
  const std::string generateUserModeString(const User &user);
  bool checkUserModeFlag(const std::string &flag);
  void setUserModeFlag(User &user, const std::string &flag);

  // topic method
  void setTopic(const User &user, Channel &channel) const;

  // kick method
  void splitStringByColon(const std::string &str,
                          std::vector<std::string> &vec);

  // who method
  void displayAllUser(const int fd, bool flag) const;
  void displayChannelUser(const int fd, const Channel &channel,
                          bool flag) const;
  void displayUser(const int fd, const User &user, bool flag) const;
  void displayWhoQuery(const int fd, const std::string &str, bool flag) const;

  // whois method
  void displayWhoisQuery(const User &user, const std::string &nick) const;
  void displayOpeUser(const int fd, const std::string &nick) const;
  void displayAllChannel(const int fd, const std::string &nick) const;

  // pong method
  void sendPong(User &user);

  // error method
  void sendError(const int fd, const std::string &message);

  // privmsg method
  void CreateParamToOneString(std::string &message);
  void sendPrivMessageChannel(const User &sender,
                              const std::string &channelName,
                              const std::string &message);
  void sendPrivMessageUser(const User &sender, const std::string &nick,
                           const std::string &message);
  void sendPrivMessage(const User &user, const std::vector<std::string> &sendTo,
                       const std::string &message);
  const std::string createPrivMessage(const std::string &sendTo,
                                      const std::string &message);

  // notice method
  void sendNoticeMessageChannel(const User &sender,
                                const std::string &channelName,
                                const std::string &message);
  void sendNoticeMessageUser(const std::string &nick,
                             const std::string &message);
  void sendNoticeMessage(const User &user,
                         const std::vector<std::string> &sendTo,
                         const std::string &message);
  const std::string createNoticeMessage(const std::string &sendTo,
                                        const std::string &message);

  // debug
  void printStringAsInts(const std::string &input);
  void printVectorString(const std::vector<std::string> &vec);
};

#endif
