#include "Server.hpp"

const std::string &Server::getPassword() const { return (this->_password); }
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
}

Server::~Server() {}

Server::Server() {}

Server::Server(const Server &server) { (void)server; }

Server &Server::operator=(const Server &server) {
  (void)server;
  return (*this);
}

void Server::eraseTmpMap(const int fd) { this->_tmpUsers.erase(fd); }

void Server::addRegisterMap(const int fd, const User &user) {
  this->_registerdUsers[fd] = user; // fd, user
}

bool Server::isNick(const std::string &nick)
{
  if (this->_nickHistory.find(nick) != this->_nickHistory.end())
    return true;
  for (std::map<int, User>::iterator it = this->_tmpUsers.begin();
       it != this->_tmpUsers.begin(); it++) {
    if (it->second.getNickName() == nick)
      return true;
  }
  return false;
}

bool Server::isExistChannel(const std::string &channelName) {
  if (this->_channels.find(channelName) != this->_channels.end()) {
    return (true);
  }
  return (false);
}

Channel &Server::getChannel(const std::string &channelName) {
  return (this->_channels.at(channelName));
}

void Server::addChannel(const std::string &channelName){
  this->_channels[channelName] = Channel(channelName);
}

void Server::addChannel(const std::string &channelName, const std::string &key){
  this->_channels[channelName] = Channel(channelName, key);
}
