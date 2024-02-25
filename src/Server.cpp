#include "Server.hpp"

Server::Server(int argc, const char *argv[]) {
  try {
    //    Server::checkServerName(SERVER_NAME);
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

// void Server::checkServerName(const std::string &serverName) const {
//   if (63 < serverName.size()) {
//     throw std::runtime_error("");
//   }
// }

void Server::checkArgc(int argc) const {
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
  issPassword >> password;
  if (!(issPort >> port)) {
    if (issPort.bad()) {
      throw std::runtime_error("Unexpected read error port.");
    } else if (issPort.fail()) {
      throw std::runtime_error("Invalid port number format.");
    }
  } else if (!issPort.eof()) {
    throw std::runtime_error("Trailing characters after port number.");
  }
  if (!(issPassword >> port)) {
    if (issPassword.bad()) {
      throw std::runtime_error("Unexpected read error password.");
    } else if (issPassword.fail()) {
      throw std::runtime_error("Invalid password format.");
    }
  } else if (!issPassword.eof()) {
    throw std::runtime_error("Trailing characters after password.");
  }
  checkPortNum(port);
  //  checkPassword(password);
  this->port = port;
  this->password = password;
}

void Server::checkPortNum(const short port) const {
  if (port < 6665 || 6669 < port) {
    throw std::runtime_error("Port number must be between 6665 and 6669");
  }
}

// void Server::checkPassword(const std::string &password) const {
// }

void Server::initSocket() {
  this->sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->sfd == -1) {
    throw std::runtime_error(std::strerror(errno));
  }

  memset(&_addr, 0, sizeof(struct sockaddr_in));
  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  _addr.sin_port = htonl(this->port);

  if (bind(this->sfd, (struct sockaddr *)&this->_addr,
           sizeof(struct sockaddr_in)) == -1) {
    throw std::runtime_error(std::strerror(errno));
  }

  if (listen(this->sfd, SOMAXCONN) == -1) {
    throw std::runtime_error(std::strerror(errno));
  }
}
