#include "Server.hpp"

const std::string &Server::getPassword() const {
  return (this->_password);
}
Server::Server(int argc, const char *argv[]) {
  try {
    Server::checkServerName(SERVER_NAME);
    Server::checkArgc(argc);
    Server::checkArgv(argv);
    Server::initSocket();
    Server::run();
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::cout << argv[0] << std::endl;
}

Server::~Server() {}

Server::Server() {}

Server::Server(const Server &server) { (void)server; }

Server &Server::operator=(const Server &server) {
  (void)server;
  return (*this);
}

void Server::eraseTmpMap(const int fd) { this->_tmpUsers.erase(fd); }

void Server::addRegisterMap(const std::string &nick, const User user)
{
    this->_registerdUsers[nick] = user; // fd, user
}
