#include "Server.hpp"

Server::Server(int argc, const char *argv[]) {
  try {
    Server::checkServerName(SERVER_NAME);
    Server::checkArgc(argc);
    Server::checkArgv(argv);
    Server::initSocket();
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
  std::istringstream issPort(argv[1]);
  std::istringstream issPassword(argv[2]);

  issPort >> port;
  if (issPort.bad()) {
    throw std::runtime_error("Unexpected read error port.");
  } else if (issPort.fail()) {
    throw std::runtime_error("Invalid port number format.");
  } else if (!issPort.eof()) {
    throw std::runtime_error("Trailing characters after port number.");
  }

  issPassword >> password;
  if (issPassword.bad()) {
    throw std::runtime_error("Unexpected read error password.");
  } else if (issPassword.fail()) {
    throw std::runtime_error("Invalid password format.");
  } else if (!issPassword.eof()) {
    throw std::runtime_error("Trailing characters after password.");
  }

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

void Server::initSocket() {
  this->sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->sfd == -1) {
    throw std::runtime_error(std::strerror(errno));
  }

  memset(&this->_addr, 0, sizeof(struct sockaddr_in));
  this->_addr.sin_family = AF_INET;
  this->_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  this->_addr.sin_port = htons(this->port);

  if (bind(this->sfd, reinterpret_cast<struct sockaddr *>(&this->_addr),
           sizeof(struct sockaddr_in)) == -1) {
    throw std::runtime_error(std::strerror(errno));
  }

  if (listen(this->sfd, SOMAXCONN) == -1) {
    throw std::runtime_error(std::strerror(errno));
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
