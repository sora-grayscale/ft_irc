#include "Server.hpp"
#include "ircserv.hpp"
#include <csignal>

#define RUNNING 0
#define STOP 1

bool server_statu = RUNNING;
void sig_handler(int) { server_statu = STOP; }

int main(int argc, char *argv[]) {
  Server server;
  signal(SIGINT, sig_handler);

  if (Util::argcheck(argc, argv, server)) {
    std::cerr << "arg error:" << std::endl;
    std::cerr << "usage: ./ircserv <port> <password>" << std::endl;
    return 1;
  }
  if (server.init())
    return 1;
  while (server_statu == RUNNING) {
    if (server.start())
      break;
  }

  std::cout << RED << "Server END" << NC << std::endl;
  close(server.get_fd());
  return 0;
}
