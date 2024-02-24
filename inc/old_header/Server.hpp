#ifndef SERVER_HPP
#define SERVER_HPP

#include "ircserv.hpp"
#include "util.hpp"
#define MAX_MESSAGE 512

// color
#define NC "\x1B[0m"
#define RED "\x1B[0;31m"
#define GRN "\x1B[0;32m"
#define PPL "\x1B[0;34m"
#define CYN "\x1B[0;36m"

// Command ===================================================
// status
#define ERROR 0
#define NICK 1

class Command {
private:
public:
};

// User ======================================================
// status
#define NOT_REGISTERED 0
#define PASSWORD_SENT 1

class User {
private:
  int _fd;
  std::string _nick;    // 9文字まで
  std::string _service; // nick + server_name
  std::string _buf;
  std::vector<std::string> _command; //
  int _status; // statusをdefineしておくといいかも
  int _level;  // userがどの程度の権限を持っているのかを保持
  int _mode;
public:
  User();
  ~User();
  int receive();
  void validate_input_format();
  void check_user_status();

  // setter getter
  void set_fd(const int fd);
  int get_fd()const;
  void set_buf(const std::string buf);
  std::string get_buf()const;
};

// Channnel ====================================================
class Channnel {
private:
  std::string _name;
  std::string _topic;

  std::vector<User> _users; // 参加者
public:
};

// Server ======================================================
class Server {
private:
  int _port;
  std::string _password;
  int _fd;
  struct sockaddr_in _a_addr;
  std::vector<struct pollfd> _fds;
  std::vector<User> _users;
  std::vector<Channnel> _channnels;
  const std::string _server_name; // 63文字まで

public:
  Server();
  int init();
  int start();
  int execute(User &user);
  int newUser();
  int get_fd()const;
  void set_port(const int port);
  int get_port()const;
  void set_password(const std::string password);
  std::string get_password()const;
  User *find_user_by_fd(const int fd);
};

#endif // SERVER