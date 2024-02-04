#include "util.hpp"

void Util::start_announce() {
  std::cout
      << "\033[1;34m"
      << " __  __         ___ ____   ____   ____                           \n"
         "|  \\/  |_   _  |_ _|  _ \\ / ___| / ___|  ___ _ ____   _____ _ __ \n"
         "| |\\/| | | | |  | || |_) | |     \\___ \\ / _ \\ '__\\ \\ / / _ \\ "
         "'__|\n"
         "| |  | | |_| |  | ||  _ <| |___   ___) |  __/ |   \\ V /  __/ |   \n"
         "|_|  |_|\\__, | |___|_| \\_\\____| |____/ \\___|_|    \\_/ \\___|_|  "
         " \n"
         "        |___/                                                     \n"
         "     _             _           _                                  \n"
         " ___| |_ __ _ _ __| |_ ___  __| |                                 \n"
         "/ __| __/ _` | '__| __/ _ \\/ _` |                                 \n"
         "\\__ \\ || (_| | |  | ||  __/ (_| |  _ _ _ _                        "
         "\n"
         "|___/\\__\\__,_|_|   \\__\\___|\\__,_| (_|_|_|_)                     "
         "  \n"
      << "\033[0m";
}

int Util::validateAndConvertPort(const char *portStr) {
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

std::string Util::validateServerPassword(const char *password) {
  const size_t MAX_LENGTH = 20;

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
  return std::string(password, length);
}

int Util::argcheck(int argc, char *argv[], Server &server) {
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
  server.set_port(port);
  server.set_password(password);
  return 0;
}
