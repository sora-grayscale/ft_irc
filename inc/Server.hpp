#ifndef SERVER_HPP 
#define SERVER_HPP

#include "ircserv.hpp"

// command
#define ERROR 0
#define NICK 1

class Command {
private:
public:
};

// status
#define NOT_REGISTERED 0

class User {
private:
  int _fd;
  std::string _nick;    // 9文字まで
  std::string _service; // nick + server_name
  std::string _command;
  int _status; // statusをdefineしておくといいかも
  int _level; // userがどの程度の権限を持っているのかを保持
public:
  void set_fd(int fd) { this->_fd = fd; }
  int get_fd() { return this->_fd; }
  void set_command(std::string command) { this->_command = command; }
};

class Channnel {
private:
public:
};

class Server {
private:
  int _fd;
  struct sockaddr_in _a_addr;
  std::vector<struct pollfd> _fds;
  std::vector<User> _users;
  std::vector<Channnel> _channnels;
  const std::string _server_name; // 63文字まで

public:
  ~Server() {
    close(this->_fd);
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
