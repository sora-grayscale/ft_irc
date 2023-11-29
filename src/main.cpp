#include "../inc/ircserv.hpp"

// ./ircserv <port> <password>


int check_port(std::string port);
int check_pass(std::string password);

bool argcheck(std::string port, std::string password) {
  if (check_port(port))
    return false;
  if (check_pass(password))
    return false;
  return true;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "error usage: ./ircserv <port> <password>" << std::endl;
    return 1;
  }
  if (argcheck(argv[1], argv[2]))
    return 1;
  // 無限loop
  // server_start(port, password);
}
