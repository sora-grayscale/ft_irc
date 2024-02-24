#include "Server.hpp"
#include <iostream>

Server::Server(int argc, const char *argv[]) {
  if (argc != 3) {
    throw std::runtime_error("usage ./ircserv port password");
  }
  std::cout << argv[0] << std::endl;
}

Server::~Server() {}
