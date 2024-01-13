#include "ircserv.hpp"
#include "util.hpp"
#include "Server.hpp"

int main() {
  Util::start_announce();
  Server server;
  if (server.init())
    return 1;
  while (1) {
    if (server.start())
      break;
  }
  close(server.get_fd());
  return 0;
}
