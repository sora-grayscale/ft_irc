#include "Server.hpp"

// public

Server::Server(int argc, const char *argv[])
    : _serverName(""), _password(""), _port(0), _sfd(0), _addr(), _pollFd(),
      _fdToNickname(), _tmpUsers(), _registerdUsers(), _channels(),
      _nickHistory(), _startDay(), _lastPingSent(std::time(NULL)) {
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

// getter
const std::string &Server::getServerName() const { return this->_serverName; }
const std::string &Server::getPassword() const { return (this->_password); }
const std::string &Server::getStartDay() const { return this->_startDay; }
std::size_t Server::numOfUser() const { return (this->_registerdUsers.size()); }
std::size_t Server::numOfChannel() const { return (this->_channels.size()); }
std::size_t Server::numOfOpeUser() const {
  size_t results = 0;

  for (std::map<int, User>::const_iterator it = this->_registerdUsers.begin();
       it != this->_registerdUsers.begin(); it++) {
    if (it->second.hasMode(User::Operator)) {
      results++;
    }
  }
  return (results);
}

// setter

// void Server::changeNickname(const std::string &before, const std::string
// &after){}

void Server::setNickHistory(const std::string &nick) {
  this->_nickHistory.insert(nick);
}

void Server::eraseTmpMap(const int fd) { this->_tmpUsers.erase(fd); }
void Server::eraseRegiMap(const int fd) { this->_registerdUsers.erase(fd); }
void Server::erasePollfd(const int fd) {
  for (std::vector<struct pollfd>::iterator it = this->_pollFd.begin();
       it != this->_pollFd.end(); it++) {
    if (it->fd == fd) {
      this->_pollFd.erase(it);
      return;
    }
  }
}

void Server::addRegisterMap(const int fd, const User &user) {
  this->_registerdUsers[fd] = user; // fd, user
}

// Lookup
User &Server::findUser(const int fd) {
  std::map<int, User>::const_iterator tIt = this->_tmpUsers.find(fd);
  if (tIt != this->_tmpUsers.end()) {
    return (this->_tmpUsers.at(fd));
  }
  std::map<int, User>::const_iterator rIt = this->_registerdUsers.find(fd);
  if (rIt != this->_registerdUsers.end()) {
    return (this->_registerdUsers.at(fd));
  }
  throw std::runtime_error("Not found User");
}

User &Server::findUser(const std::string &nick) {
  for (std::map<int, User>::iterator it = this->_registerdUsers.begin();
       it != this->_registerdUsers.end(); it++) {
    if (it->second.getNickName() == nick)
      return it->second;
  }
  throw std::runtime_error("Not found User");
}

bool Server::isHisNick(const std::string &nick) {
  if (this->_nickHistory.find(nick) != this->_nickHistory.end())
    return true;
  return false;
}

bool Server::isTmpNick(const std::string &nick) {
  for (std::map<int, User>::const_iterator it = this->_tmpUsers.begin();
       it != this->_tmpUsers.end(); it++) {
    if (it->second.getNickName() == nick)
      return true;
  }
  return false;
}

bool Server::isRegiNick(const std::string &nick) {
  for (std::map<int, User>::const_iterator it = this->_registerdUsers.begin();
       it != this->_registerdUsers.end(); it++) {
    if (it->second.getNickName() == nick)
      return true;
  }
  return false;
}

bool Server::isNick(const std::string &nick) {
  if (isHisNick(nick))
    return true;
  if (isTmpNick(nick))
    return true;
  return false;
}

bool Server::isRegiUser(const int &fd) {
  if (this->_registerdUsers.find(fd) != this->_registerdUsers.end()) {
    return true;
  }
  return false;
}

// user
int Server::getUserFd(const std::string &nick) const {
  for (std::map<int, User>::const_iterator it = this->_registerdUsers.begin();
       it != this->_registerdUsers.end(); it++) {
    if (it->second.getNickName() == nick) {
      return (it->second.getFd());
    }
  }
  throw std::runtime_error("Not found User");
}

// channel
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

std::map<std::string, Channel>::const_iterator
Server::getChannelsBegin() const {
  return (this->_channels.begin());
}

std::map<std::string, Channel>::const_iterator Server::getChannelsEnd() const {
  return (this->_channels.end());
}

std::map<std::string, Channel> &Server::getChannels() {
  return (this->_channels);
}

std::map<int, User>::const_iterator Server::getUserBegin() const {
  return (this->_registerdUsers.begin());
}

std::map<int, User>::const_iterator Server::getUserEnd() const {
  return (this->_registerdUsers.end());
}

void Server::delUserChannel(User &user, const std::string &comment) {
  int fd = user.getFd();
  if (!this->isRegiUser(fd)) {
    return;
  }
  std::map<std::string, Channel> &channels = this->getChannels();

  for (std::map<std::string, Channel>::iterator it = channels.begin();
       it != channels.end(); it++) {
    if (it->second.isUserInChannel(user.getNickName())) {
      it->second.broadcastMessage(comment, user);
      it->second.removeUser(user);
    }
  }
}

void Server::eraseUserList(User &user) {
  int fd = user.getFd();
  if (!this->isRegiUser(fd)) {
    this->eraseTmpMap(fd);
  } else {
    this->eraseRegiMap(fd);
  }
  this->erasePollfd(fd);
}

void Server::delUser(User &user, const std::string &comment) {
  int fd = user.getFd();
  // userをチャンネルから消去, messageの送信
  delUserChannel(user, comment);
  // userを持っているリスト系から取り除く
  eraseUserList(user);
  // userのfdをクローズ
  close(fd);
  std::cout << "close socket: " << fd << std::endl;
}

void Server::delUser(const int fd) {
  if (!this->isRegiUser(fd)) {
    this->eraseTmpMap(fd);
  } else {
    this->eraseRegiMap(fd);
  }
  erasePollfd(fd);
  close(fd);
  std::cout << "close socket: " << fd << std::endl;
}
