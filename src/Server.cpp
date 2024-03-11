#include "Server.hpp"

const std::string &Server::getPassword() const { return (this->_password); }
Server::Server(int argc, const char *argv[]) {
  try {
    Server::checkServerName(SERVER_NAME);
    this->_serverName = SERVER_NAME;
    Server::checkArgc(argc);
    Server::checkArgv(argv);
    Server::initSocket();
    Server::initTimeOfStart();
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

bool Server::isNick(const std::string &nick) {
  if (this->_nickHistory.find(nick) != this->_nickHistory.end())
    return true;
  for (std::map<int, User>::iterator it = this->_tmpUsers.begin();
       it != this->_tmpUsers.end(); it++) {
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

void Server::addChannel(const std::string &channelName) {
  this->_channels[channelName] = Channel(channelName);
}

void Server::addChannel(const std::string &channelName,
                        const std::string &key) {
  this->_channels[channelName] = Channel(channelName, key);
}

void Server::setNickHistory(const std::string &nick) {
  this->_nickHistory.insert(nick);
}

const std::string &Server::getServerName() const { return this->_serverName; }

int Server::numOfUser() {
  return static_cast<int>(this->_registerdUsers.size());
}

int Server::numOfOpeUser() {
  int results = 0;

  for (std::map<int, User>::iterator it = this->_registerdUsers.begin();
       it != this->_registerdUsers.begin(); it++) {
    if (it->second.hasMode(User::Operator))
      results++;
  }
  return results;
}

int Server::numOfChannel() { return static_cast<int>(this->_channels.size()); }

const std::string &Server::getStartDay() const { return this->_startDay; }
