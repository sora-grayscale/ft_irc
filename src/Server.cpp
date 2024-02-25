#include "Server.hpp"

Server::Server(int argc, const char *argv[]) {
  try {
    Server::checkServerName(SERVER_NAME);
    Server::checkArgc(argc);
    Server::checkArgv(argv);
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::cout << argv[0] << std::endl;
}

Server::~Server() {}

void Server::checkServerName(const std::string &serverName) const {
  const size_t serverMaxLen = SERVER_MAX_LEN;

  if (serverMaxLen < serverName.size()) {
    throw std::runtime_error("Server name is too long.");
  }
  for (std::size_t i = 0; i < serverName.size(); ++i) {
    char c = serverName.at(i);
    if (!std::isalnum(static_cast<unsigned char>(c))) {
      throw std::runtime_error("Password contains invalid characters.");
    }
  }

}

void Server::checkArgc(const int argc) const {
  if (argc != 3) {
      throw std::runtime_error("usage ./ircserv port password");
  }
}

void Server::checkArgv(const char *argv[]) {
  short port;
  std::string password;
  std::istream iss = argv;

  iss >> port >> password;
  checkPortNum(port);
  checkPassword(password);
  this->port = port;
  this->password = password;
}

void Server::checkPortNum(const short port) const {
  if (port < 6665 || 6669 < port) {
    throw std::runtime_error("Port number must be between 6665 and 6669");
  }
}

void Server::checkPassword(const std::string &password) const {
  const size_t passMaxLen = PASS_MAX_LEN;

  if (password.size() > passMaxLen) {
    throw std::runtime_error("Password is too long.");
  }
  for (std::size_t i = 0; i < password.size(); ++i) {
    char c = password[i];
    if (!std::isalnum(static_cast<unsigned char>(c))) {
      throw std::runtime_error("Password contains invalid characters.");
    }
  }
  return;
}
