#include "Server.hpp"
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
  unsigned short port;
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
  this->_port = port;
  this->_password = password;
}

void Server::checkPortNum(const unsigned short port) const {
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

void Server::initSocket() {
  this->_sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_sfd == -1) {
    throw std::runtime_error(std::strerror(errno));
  }

  // non blocking I/O
  // int flags = fcntl(this->_sfd, F_GETFL, 0);
  // if (flags == -1) {
  //   throw std::runtime_error(std::strerror(errno));
  // }
  // flags |= O_NONBLOCK;
  int flags = O_NONBLOCK;
  if (fcntl(this->_sfd, F_SETFL, flags) == -1) {
    throw std::runtime_error(std::strerror(errno));
  }

  memset(&this->_addr, 0, sizeof(struct sockaddr_in));
  this->_addr.sin_family = AF_INET;
  this->_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  this->_addr.sin_port = htons(this->_port);

  if (bind(this->_sfd, reinterpret_cast<struct sockaddr *>(&this->_addr),
           sizeof(struct sockaddr_in)) == -1) {
    throw std::runtime_error(std::strerror(errno));
  }

  if (listen(this->_sfd, SOMAXCONN) == -1) {
    throw std::runtime_error(std::strerror(errno));
  }
}

void Server::initTimeOfStart() {
  std::stringstream ss;
  std::string tmp;
  std::string day;

  std::time_t result = std::time(NULL);
  ss << std::ctime(&result);
  for (int i = 0; !ss.eof(); i++) {
    ss >> tmp;
    if (i == 1 || i == 2) {
      day += tmp;
    }
  }
  this->_startDay = day;
}
