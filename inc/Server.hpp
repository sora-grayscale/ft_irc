#ifndef SERVER_HPP 
#define SERVER_HPP

#include "ircserv.hpp"

// status
#define NOT_REGISTERED 0

class Command {
private:
public:
};

class User {
private:
  int fd;
  std::string nick;    // 9文字まで
  std::string service; // nick + server_name
  std::string command;
  int status; // statusをdefineしておくといいかも
public:
  void set_fd(int fd) { this->fd = fd; }
  int get_fd() { return this->fd; }
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
  std::vector<User> users;
  std::vector<Channnel> channnels;

  const std::string server_name; // 63文字まで

public:
  int init();
  int start();
  int execute(int client_fd);
  int newUser();
  int get_fd();
};

#endif // SERVER
