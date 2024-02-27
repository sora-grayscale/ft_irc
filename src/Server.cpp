#include "Server.hpp"

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

void Server::run() {
  const int timeout = -1; // 無限に待機
  struct pollfd server_fd_struct;

  server_fd_struct.fd = this->_sfd;
  server_fd_struct.events = POLLIN;
  this->_pollFd.push_back(server_fd_struct);

  while (true) {
    try {
      int ret = poll(this->_pollFd.data(), this->_pollFd.size(), timeout);
      if (ret < 0) {
        throw std::runtime_error(std::strerror(errno));
      } else if (ret == 0) {
        continue; // timeout (無限待機のため発生しない)
      }

      for (std::size_t i = 0; i < this->_pollFd.size(); i++) {
        if (this->_pollFd.at(i).revents & POLLIN) {
          if (this->_pollFd.at(i).fd == this->_sfd) {
            acceptNewSocket();
          } else {
            readClientCommand(this->_pollFd.at(i).fd);
          }
        }
      }
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      continue;
    }
  }
}

void Server::acceptNewSocket() {
  int client_fd = accept(this->_sfd, NULL, NULL);
  if (client_fd < 0) {
    throw std::runtime_error(std::strerror(errno));
  } else {

    // add new user fd
    struct pollfd client_fd_struct;
    client_fd_struct.fd = client_fd;
    client_fd_struct.events = POLLIN;
    this->_pollFd.push_back(client_fd_struct);

    // add user instance to map
    User newUser(client_fd);
    this->_tmpUsers[client_fd] = newUser; // fd, user
    std::cout << "new socket" << std::endl;
  }
}

void Server::readClientCommand(int fd) {
  ssize_t count;
  char buf[RECEVE_MAX_LEN + 1];
  count = read(fd, buf, RECEVE_MAX_LEN);
  if (count < 0) {
    close(fd);
    this->_tmpUsers.erase(fd);
    throw std::runtime_error(std::strerror(errno));
  } else if (512 < count) {
    throw std::runtime_error("You can send up to 512 characters.");
  } else {
    std::cout << buf << std::endl;
  }
}

Server::Server() {}

Server::Server(const Server &server) {
  (void)server;
}

Server &Server::operator=(const Server &server) {
  (void)server;
  return (*this);
}
