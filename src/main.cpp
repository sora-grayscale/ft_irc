#include "Server.hpp"
#include "ircserv.hpp"
#include <csignal>

#define RUNNING 0
#define STOP 1

bool server_statu = RUNNING;
void sig_handler(int) { server_statu = STOP; }

int validateAndConvertPort(const char *portStr) {
  int port = 0;
  size_t length = std::strlen(portStr);

  if (length == 0 || length > 5)
    throw std::runtime_error("port length is invalid");
  for (size_t i = 0; i < length; ++i) {
    if (!std::isdigit(portStr[i]))
      throw std::runtime_error("Non-digit character found");
    port = port * 10 + (portStr[i] - '0');
  }
  if (port < 1 || port > 65535)
    throw std::runtime_error("port number is in the invalid range");
  return port;
}

std::string validateServerPassword(const char *password) {
  const size_t MAX_LENGTH = 20; // パスワードの最大長

  if (password == NULL || *password == '\0') {
    throw std::runtime_error("Password cannot be empty.");
  }

  size_t length = 0;
  for (const char *p = password; *p != '\0'; ++p, ++length) {
    if (!isalnum(*p) && *p != '_') {
      throw std::runtime_error("Password contains invalid characters.");
    }
    if (length > MAX_LENGTH) {
      throw std::runtime_error("Password is too long.");
    }
  }
  return std::string(password, length); // パスワードが有効
}

int argcheck(int argc, char *argv[]) {
  int port;
  std::string password;
  if (argc != 3)
    return 1;
  try {
    port = validateAndConvertPort(argv[1]);
    password = validateServerPassword(argv[2]);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  std::cout << port << std::endl;
  std::cout << password << std::endl;
  return 0;
}

int main(int argc, char *argv[]) {
  Server server;
  signal(SIGINT, sig_handler);

  if (argcheck(argc, argv)) {
    std::cerr << "arg error:" << std::endl;
    std::cerr << "usage: ./ircserv <port> <password>" << std::endl;
    return 1;
  }
  if (server.init())
    return 1;
  while (server_statu == RUNNING) {
    if (server.start())
      break;
  }

  std::cout << RED << "Server END" << NC << std::endl;
  close(server.get_fd());
  return 0;
}
