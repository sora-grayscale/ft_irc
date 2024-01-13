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
  ~Server() {
    close(fd);
    std::cout << "Server closed!" << std::endl;
  }
  int init();
  int start();
  int execute(User &user);
  int newUser();
  int get_fd();
  User *find_user_by_fd(int fd);
};

#endif // SERVER
