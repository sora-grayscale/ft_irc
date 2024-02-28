#include "Server.hpp"

void Server::run() {
  CommandHandler commandhandler;
  struct pollfd server_fd_struct;

  server_fd_struct.fd = this->_sfd;
  server_fd_struct.events = POLLIN;
  this->_pollFd.push_back(server_fd_struct);

  while (true) {
    try {
      int ret = Server::pollSockets();
      if (ret == 0) { // timeoutの場合はここでは発生しないが、念のため
        continue;
      }

      for (std::size_t i = 0; i < this->_pollFd.size(); i++) {
        if (this->_pollFd.at(i).revents & POLLIN) {
          if (this->_pollFd.at(i).fd == this->_sfd) {
            acceptNewSocket();
          } else {
            std::string receivedMessage = readClientCommand(this->_pollFd.at(i).fd);
            if (!receivedMessage.empty()) {
              commandhandler.parseMessage(receivedMessage);
            }
          }
        }
      }

    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      continue;
    }
  }
}

int Server::pollSockets() {
  int ret;
  const int timeout = -1; // 無限に待機

  ret = poll(this->_pollFd.data(), this->_pollFd.size(), timeout);
  if (ret < 0) {
    throw std::runtime_error(std::strerror(errno));
  } else if (ret == 0) {
    return (0);
  }
  return (ret);
}

void Server::acceptNewSocket() {
  int client_fd = accept(this->_sfd, NULL, NULL);
  if (client_fd < 0) {
    throw std::runtime_error(std::strerror(errno));
  } else {

    // non blocking I/O
    int flags = fcntl(client_fd, F_GETFL, 0);
    if (flags == -1) {
      throw std::runtime_error(std::strerror(errno));
    }
    flags |= O_NONBLOCK;
    if (fcntl(client_fd, F_SETFL, flags) == -1) {
      throw std::runtime_error(std::strerror(errno));
    }

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

std::string Server::readClientCommand(int fd) {
  ssize_t count;
  char buf[RECEVE_MAX_LEN + 1];
  memset(buf, 0, RECEVE_MAX_LEN + 1);
  count = recv(fd, buf, RECEVE_MAX_LEN, 0);
  if (count < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return ("");
    }
    close(fd);
    this->_tmpUsers.erase(fd);
    throw std::runtime_error(std::strerror(errno));
  } else if (count == 0) { // クライアントが切断された場合
    close(fd);
    this->_tmpUsers.erase(fd);
    return ("");
  } else {
    return (buf);
  }
}