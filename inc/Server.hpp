#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
#include "User.hpp"
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <set>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#define SERVER_NAME "localhost"

class Server {
public:
  Server(int argc, const char *argv[]);
  ~Server();
  void run();
  void changeNickname(const std::string &before, const std::string &after);
  const std::string &getServerName() const;
  const std::string &getNickHistory() const;
  void setNickHistory(const std::string &nick);

private:
  std::string
      serverName; //    > 1.1 サーバー
                  //    サーバーは名前で一意に識別されます。この名前は、最大63文字（63）の文字です。サーバー名で使用される可能性のあるもの、および使用されないものについては、プロトコル文法ルール（セクション2.3.1）を参照してください。

  std::string password; // 32 自分で決めた

  short port; //

  int sfd;
  struct sockaddr_in _addr;
  std::vector<struct pollfd> _pollFd;

  void checkServerName(const std::string &serverName) const;
  void checkArgc(int argc) const;
  void checkArgv(const char *argv[]);
  void checkPortNum(const short port) const;
  void checkPassword(const std::string &password) const;

  // std::map <const size_t clFd, std::string nickname> fdToNickname;
  std::map<const size_t, std::string> fdToNickname;
  // std::map<std::string nickname, User user> nicknameToUserMap;
  std::map<std::string, User> nicknameToUserMap;
  // std::map<std::string channelName, Channel & channel>
  // channelNameToChannelMap;
  std::map<std::string, Channel> channelNameToChannelMap;
  std::set<std::string> _nickHistory;

  Server();
  Server(const Server &server);
  Server &operator=(const Server &server);
};

#endif
