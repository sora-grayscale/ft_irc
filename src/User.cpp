#include "Server.hpp"

int User::receive() {
  int recv_size;
  char recv_buf[MAX_MESSAGE + 1];

  recv_size = recv(this->_fd, recv_buf, MAX_MESSAGE, 0);
  if (recv_size < 0) {
    if (errno == EWOULDBLOCK || errno == EAGAIN) {
      std::cerr << "No data received" << std::endl;
      return 1;
    }
    perror("recv");
    return 1;
  }
  recv_buf[recv_size] = '\0';
  this->set_buf(recv_buf);
  return 0;
}

void User::set_fd(const int fd) { this->_fd = fd; }

int User::get_fd()const { return this->_fd; }

void User::set_buf(const std::string buf) {
  // this->_buf += buf;
  // ↓これだとMAX_SIZE より大きいメッセージが送られてきた場合困る
  // もしMAX_MESSAGEが3文字だったら"hello"が"hel"と"lo"に分かれる
  // それをいい感じに組み合わせられるようにするorしない
  this->_buf = buf;
}

std::string User::get_buf()const { return this->_buf; }
