#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
#include "CommandHandler.hpp"
#include "User.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <set>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

#define SERVER_NAME "localhost"

#define PASS_MAX_LEN 32
#define SERVER_MAX_LEN 63
#define RECEVE_MAX_LEN 512
#define REAL_NAME_MAX_LEN 63
#define MAX_CHANNEL_LIMIT 10

#define OPER_USER "operatuser"
#define OPER_PASSWORD "password"

#define SERVER_VERSION "2.0"
#define SERVER_VERSION_COMMENT "This is our server :)"

#define DEBUG_LEVEL "normal"
#define PATCH_LEVEL "normal"
#define ADMIN_NAME "admin"

#define ADMIN_LOCATION "Tokyo"
#define ADMIN_AFFILIATION "42Tokyo"
#define ADMIN_MAIL "admin@student.42tokyo.fr"
#define ANON_NAME "anonymous"

#define PING_TIME 100000

#define RED "\033[31m"
#define GRN "\033[32m"
#define YEL "\033[33m"
#define BLU "\033[34m"
#define MGN "\033[35m"
#define CYN "\033[36m"
#define RES "\033[m"

class Server {
public:
  Server(int argc, const char *argv[]);
  ~Server();

  void run();

  // getter
  const std::string &getServerName() const;
  const std::string &getNickHistory() const;
  const std::string &getPassword() const;
  const std::string &getStartDay() const;
  std::map<std::string, Channel> &getChannels();
  std::size_t numOfUser() const;
  std::size_t numOfChannel() const;
  std::size_t numOfOpeUser() const;

  // setter
  void changeNickname(const std::string &before, const std::string &after);
  void setNickHistory(const std::string &nick);
  void eraseTmpMap(const int fd);
  void eraseRegiMap(const int fd);
  void erasePollfd(const int fd);
  void addRegisterMap(const int fd, const User &user);
  void setPingTime(const std::time_t time);

  // Lookup
  User &findUser(const int fd);
  User &findUser(const std::string &nick);
  bool isHisNick(const std::string &nick) const;
  bool isTmpNick(const std::string &nick) const;
  bool isRegiNick(const std::string &nick) const;
  bool isNick(const std::string &nick) const;
  bool isRegiUser(const int &fd) const;

  // send
  static const std::string createUserPrefix(const User &user);
  static void sendReply(const int fd, const std::string &reply);
  static void sendReply(const User &sender, const int fd,
                        const std::string &reply);
  static void sendReply(const std::string &host, const int fd,
                        const std::string &reply);

  // user
  int getUserFd(const std::string &nick) const;

  // channel
  bool isExistChannel(const std::string &channelName) const;
  Channel &
  getChannel(const std::string &channelName); // channelがあるかのチェックが必要
  void addChannel(const std::string &channelName);
  void addChannel(const std::string &channelName, const std::string &key);
  std::map<std::string, Channel>::const_iterator getChannelsBegin() const;
  std::map<std::string, Channel>::const_iterator getChannelsEnd() const;
  std::map<int, User>::const_iterator getUserBegin() const;
  std::map<int, User>::const_iterator getUserEnd() const;
  void eraseChannel(const std::string &channelName);

  // erase method
  void delUser(User &user, const std::string &comment);
  void delUser(const int fd);

private:
  std::string _serverName;
  std::string _password;
  unsigned short _port;
  int _sfd;
  struct sockaddr_in _addr;
  std::vector<struct pollfd> _pollFd;
  std::map<const size_t, std::string> _fdToNickname; // client fd, nickname
  std::map<int, User> _tmpUsers;                     // fd, user
  std::map<int, User> _registerdUsers;               // fd, user
  std::map<std::string, Channel> _channels;          /// channelname, channel
  std::set<std::string> _nickHistory;
  std::string _startDay;
  std::time_t _lastPingSent;

  // Server init
  void checkServerName(const std::string &serverName) const;
  void checkArgc(const int argc) const;
  void checkArgv(const char *argv[]);
  void checkPortNum(const unsigned short port) const;
  void checkPassword(const std::string &password) const;
  void initSocket();
  void initTimeOfStart();

  // Server run
  int pollSockets();
  void acceptNewSocket();
  std::string readClientCommand(int fd);
  void checkPing();

  // ping method
  void sendPing(User &user) const;
  void checkPong(User &user);

  // delUser method
  void eraseUserList(User &user);
  void delUserChannel(User &user, const std::string &comment);

  Server();
  Server(const Server &server);
  Server &operator=(const Server &server);
};

#endif
