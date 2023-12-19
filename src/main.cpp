#include "../inc/ircserv.hpp"

// ./ircserv <port> <password>

class server {
private:
  int port;
  std::string password;

public:
};

int check_port(std::string port) { return 1; }
int check_pass(std::string password) { return 1; }

int init_server(int port, str::string password) {
  // init server

  int fd = socket();
  // treat error
  setsockopt();
  // treat error
  bind();
  // treat error
  listen();
  // treat error
  accept();
}

bool argcheck(std::string port, std::string password) {
  if (check_port(port))
    throw std::runtime_error("port setting faild");
  if (check_pass(password))
    throw std::runtime_error("password setting faild");
  return true;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "error usage: ./ircserv <port> <password>" << std::endl;
    return 1;
  }
  try {
    argcheck(argv[2], argv[2])
  } catch (std::exeception &e){
    std::cout << e.what << std::endl;
  }
  // 無限loop
  // 構造体渡したほうがいいかも
  // init_server
  // while (1) server_start(port, password);
}

