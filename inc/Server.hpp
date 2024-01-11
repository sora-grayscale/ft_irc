#ifndef SERVER_HPP 
#define SERVER_HPP

#include "ircserv.hpp"

class Command {
private:
public:
};

class User {
private:
  std::string nick;    // 9文字まで
  std::string service; // nick + server_name
  int fd;
  std::string command;
public:
};

class Channnel {
private:
public:
};

class Server {
private:
  int fd;
  struct sockaddr_in a_addr;
  std::vector<struct pollfd> fds;
  std::vector<User> user;
  std::vector<Channnel> channnel;

  const std::string server_name; // 63文字まで

public:
  int init();
  int start();
  int execute(int client_fd);
  int newUser();
  int getfd();
};

#endif // SERVER
