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

class Server {
public:
  Server(int argc, const char *argv[]);
  ~Server();

  void run();

  void changeNickname(const std::string &before, const std::string &after);
  const std::string &getServerName() const;
  const std::string &getNickHistory() const;
  void setNickHistory(const std::string &nick);
  const std::string &getPassword() const;

private:
  std::string
      _serverName; //    > 1.1 サーバー
                   //    サーバーは名前で一意に識別されます。この名前は、最大63文字（63）の文字です。サーバー名で使用される可能性のあるもの、および使用されないものについては、プロトコル文法ルール（セクション2.3.1）を参照してください。
  std::string _password; // 32 自分で決めた
  unsigned short _port;  //
  int _sfd;
  struct sockaddr_in _addr;
  std::vector<struct pollfd> _pollFd;
  std::map<const size_t, std::string> _fdToNickname; // client fd, nickname
  std::map<int, User> _tmpUsers;                     // fd, user
  std::map<std::string, User> _registerdUsers;       // nickname, user
  std::map<std::string, Channel> _channels;          /// channelname, channel
  std::set<std::string> _nickHistory;

  // Server init
  void checkServerName(const std::string &serverName) const;
  void checkArgc(const int argc) const;
  void checkArgv(const char *argv[]);
  void checkPortNum(const unsigned short port) const;
  void checkPassword(const std::string &password) const;
  void initSocket();

  // Server run
  int pollSockets();
  void acceptNewSocket();
  std::string readClientCommand(int fd);

  Server();
  Server(const Server &server);
  Server &operator=(const Server &server);
};

#endif
