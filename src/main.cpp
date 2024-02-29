#include "Server.hpp"
#include "User.hpp"

int main(int argc, const char *argv[]) {
  Server server(argc, argv);
  server.run();
}
