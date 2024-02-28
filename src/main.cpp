#include "Server.hpp"
#include "User.hpp"
#include <iostream>

// short validateAndConvertPort(const char *portStr) {
//   int port = 0;
//   size_t length = std::strlen(portStr);
//
//   if (length == 0 || length > 5)
//     throw std::runtime_error("port length is invalid");
//   for (size_t i = 0; i < length; ++i) {
//     if (!std::isdigit(portStr[i]))
//       throw std::runtime_error("Non-digit character found");
//     port = port * 10 + (portStr[i] - '0');
//   }
//   if (port < 1 || port > 65535)
//     throw std::runtime_error("port number is in the invalid range");
//   return static_cast<short>port;
// }
//
// std::string validateServerPassword(const char *password) {
//   const size_t MAX_LENGTH = 32;
//
//   if (password == NULL || *password == '\0') {
//     throw std::runtime_error("Password cannot be empty.");
//   }
//
//   size_t length = 0;
//   for (const char *p = password; *p != '\0'; ++p, ++length) {
//     if (!isalnum(*p) && *p != '_') {
//       throw std::runtime_error("Password contains invalid characters.");
//     }
//     if (length > MAX_LENGTH) {
//       throw std::runtime_error("Password is too long.");
//     }
//   }
//   return std::string(password, length);
// }

int main(int argc, const char *argv[]) { Server server(argc, argv); }
