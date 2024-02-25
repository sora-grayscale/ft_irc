#ifndef UTIL_HPP 
#define UTIL_HPP

#include "ircserv.hpp"
class Server;
#include "Server.hpp"

class Util {
public:
  static void start_announce();
  static int validateAndConvertPort(const char *portStr);
  static std::string validateServerPassword(const char *password);
  static int argcheck(int argc,char *argv[], Server &server);
};

#endif // UTIL
