#include "Server.hpp"
#include "ircserv.hpp"
#include <csignal>

#define RUNNING 0
#define STOP 1

bool server_statu = RUNNING;
void sig_handler(int) { server_statu = STOP; }

int main() {
  Server server;
  signal(SIGINT, sig_handler);

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
