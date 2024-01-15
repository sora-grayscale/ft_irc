#include "Server.hpp"
#include "ircserv.hpp"
#include <csignal>

bool stop = false;
void sig_handler(int) { stop = true; }

int main() {
  Server server;
  signal(SIGINT, sig_handler);

  if (server.init())
    return 1;
  while (stop == false) {
    if (server.start())
      break;
  }

  std::cout << RED << "Server END" << NC << std::endl;
  close(server.get_fd());
  return 0;
}
