#include "Server.hpp"

User::User() { this->_status = NOT_REGISTERED; }
User::~User() { /*close(this->_fd);*/
}

void User::validate_input_format()
{
  // コマンドだったらcommandにいい感じにstrを入れる感じかな
    // buf をあくまでbufとして使うなら
  // 何をするのか全然わかってない
  // command or messageを見る
  // パース時にコマンドの種類をset_command_type
  // みたいので管理して、それを実行時に判断
  // 実行のときはcommandをdefineしたintで管理してそれでswitch文でいいかも #define NICK 1
}

void User::check_user_status() {
  if (this->_status == NOT_REGISTERED && this->_buf != "PASS")
    return ;
  if (this->_status == PASSWORD_SENT && (this->_buf != "NICK" || this->_buf != "USER"))
    return ;
  // 実行だめ条件を弾き終わった
  // 実行();
  return ;
}

Server::Server() { Util::start_announce(); }

int Server::execute(User &user) {
  int client_fd = user.get_fd();
  // receive --------------------------------------------
  if (user.receive())
    return 1;
  std::cout << GRN << "Received: " << NC << user.get_buf() << std::endl;

  //parser  ------ ------------------------------------
  user.validate_input_format();

  // check status  ------ -----------------------------
  user.check_user_status();

  // execute ------------------------------------------
  int send_size;
  char send_buf;

  if (user.get_buf() == "finish") {
    send_buf = 0;
    send_size = send(client_fd, &send_buf, 1, 0);
    close(client_fd);
    // ToDo: pollfd,userからこのfdを取り出す
    std::cout << "closed" << std::endl;
    if (send_size == -1) {
      std::cerr << "send error\n" << std::endl;
      return 1;
    }
  } else if (user.get_buf() == "NICK") {
    std::cout << "Exec Nick Command" << std::endl;
    send_buf = 1;
    send_size = send(client_fd, &send_buf, 1, 0);
    if (send_size == -1) {
      std::cerr << "send error\n" << std::endl;
      return 1;
    }
  } else {
    send_buf = 1;
    send_size = send(client_fd, &send_buf, 1, 0);
    if (send_size == -1) {
      std::cerr << "send error\n" << std::endl;
      return 1;
    }
  }
  // ----- --------------------------------------------
  return 0;
}

int Server::newUser() {
  int client_fd = accept(this->_fd, NULL, NULL);
  if (client_fd < 0) {
    if (errno == EWOULDBLOCK || errno == EAGAIN) {
      // std::cout << "No incomming connection" << std::endl;
      // continue;
    } else {
      perror("accept");
      return 1;
    }
  } else {
    std::cout << "conected" << std::endl;
    this->_fds.push_back(pollfd());
    this->_fds.back().fd = client_fd;
    this->_fds.back().events = POLLIN;
    // Userのクラスにも入れてるけどあんまりなっとくいってない
    // Userの識別が内側まで行かないとできないのが面倒
    this->_users.push_back(User());
    this->_users.back().set_fd(client_fd);
  }
  return 0;
}

int Server::init() {
  // create socket
  this->_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_fd == -1) {
    perror("socket");
    return 1;
  }
  memset(&this->_a_addr, 0, sizeof(struct sockaddr_in));

  // # set as a non blocking
  // これがあるとI/Oのwait中も他の動作が実行される。ないとI/O待ちで止まる
  int flags = fcntl(this->_fd, F_GETFL, 0);
  fcntl(this->_fd, F_SETFL, flags | O_NONBLOCK);

  // setting server config
  this->_a_addr.sin_family = AF_INET;
  this->_a_addr.sin_port = htons(uint16_t(atoi("8080")));
  inet_aton("127.0.0.1", &this->_a_addr.sin_addr);

  // setting config to socket
  if (bind(this->_fd, (struct sockaddr *)&this->_a_addr,
           sizeof(this->_a_addr)) == -1) {
    perror("bind");
    return 1;
  }

  // wait connection
  if (listen(this->_fd, 5) == -1) {
    perror("listen");
    return 1;
  }

  // vectorの0にserverのfdを足す
  this->_fds.push_back(pollfd());
  this->_fds.back().fd = this->_fd;
  this->_fds.back().events = POLLIN;
  return 0;
}

int Server::start() {
  // poll setting
  if (poll(this->_fds.data(), this->_fds.size(), -1) < 0) {
    perror("poll");
    return 1;
  }

  if (this->_fds[0].revents == POLLIN) {
    newUser();
  } else {
    // userからの処理
    for (std::vector<pollfd>::iterator it = this->_fds.begin();
         it != this->_fds.end(); ++it) {
      if ((*it).revents == POLLIN) {
        User *tmp = find_user_by_fd((*it).fd);
        if (!tmp)
          return 1;
        if (execute(*tmp)) {
          // executeはfdのUserを渡したい。(コマンドはUserに影響するものだから)
          // (*it).fdと一致するfdを持ったUserを取り出してServerに渡す

          // ToDo: execute でfdは閉じてるけど、vectorから外してない
          // ここの中を通ってない感じがする
          return 1;
        }
      }
    }
  }
  return 0;
}

int Server::get_fd() { return this->_fd; }

User *Server::find_user_by_fd(int fd) {
  for (std::vector<User>::iterator it = this->_users.begin();
       it != this->_users.end(); ++it) {
    if (it->get_fd() == fd)
      return &(*it);
  }
  return NULL;
}
