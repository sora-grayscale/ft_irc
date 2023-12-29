#include "ircserv.hpp"
#include "util.hpp"

class Command {
private:
public:
};

class User {
private:
  std::string nick;    // 9文字まで
  std::string service; // nick + server_name
public:
};

class Channnel {
private:
public:
};

class Server {
private:
  const std::string server_name; // 63文字まで
public:
};

int execute(int client_fd) {
  int recv_size, send_size;
  char recv_buf[MAX_MESSAGE], send_buf;

  recv_size = recv(client_fd, recv_buf, MAX_MESSAGE, 0);
  if (recv_size < 0) {
    if (errno == EWOULDBLOCK || errno == EAGAIN) {
      std::cerr << "No data received" << std::endl;
      return 1;
    } else {
      perror("recv");
      return 1;
    }
  }

  recv_buf[recv_size] = '\0';
  std::cout << "Received: " << recv_buf << std::endl;

  if (strcmp(recv_buf, "finish") == 0) {
    send_buf = 0;
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

  return 0;
}

int main() {
  int fd;
  struct sockaddr_in a_addr;
  std::vector<struct pollfd> fds;

  Util::start_announce();

  // create socket
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return 1;
  }
  memset(&a_addr, 0, sizeof(struct sockaddr_in));

  // # set as a non blocking
  /* memo
      ただこれを入れるだけだと無限ループになる
     ←I/O待ちの間に実行をしてるから合ってる fcntl(fd, F_SETFL, O_NONBLOCK);
      これを入れると普通に動くけど、動作が別に変わらん
      ioctl(fd, (int)FIONBIO, (char *)1L);
  */

  // これがあるとI/Oのwait中も他の動作が実行される。ないとI/O待ちで止まる
  int flags = fcntl(fd, F_GETFL, 0);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);

  // setting server config
  a_addr.sin_family = AF_INET;
  a_addr.sin_port = htons(uint16_t(atoi("8080")));
  inet_aton("127.0.0.1", &a_addr.sin_addr);

  // setting config to socket
  if (bind(fd, (struct sockaddr *)&a_addr, sizeof(a_addr)) == -1) {
    perror("bind");
    return 1;
  }

  // wait connection
  if (listen(fd, 5) == -1) {
    perror("listen");
    return 1;
  }

  // vectorの0にserverのfdを足す
  // fds.push_back({fd, POLLIN}); // c++11の書き方でした
  fds.push_back(pollfd());
  fds.back().fd = fd;
  fds.back().events = POLLIN;

  while (1) {
    // std::cout << "wait connection" << std::endl;

    // poll setting
    if (poll(fds.data(), fds.size(), -1) < 0) {
      perror("poll");
      break;
    }

    if (fds[0].revents == POLLIN) {
      int client_fd = accept(fd, NULL, NULL);
      if (client_fd < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
          // std::cout << "No incomming connection" << std::endl;
          continue;
        } else {
          perror("accept");
          break;
        }
      } else {
        std::cout << "conected" << std::endl;
        fds.push_back(pollfd());
        fds.back().fd = client_fd;
        fds.back().events = POLLIN;
      }
    } else {
      for (std::vector<pollfd>::iterator it = fds.begin(); it != fds.end();
           ++it) {
        if ((*it).revents == POLLIN) {
          if (execute((*it).fd)) {
            close((*it).fd);
            std::cout << "closed" << std::endl;
          }
        }
      }
    }
  }
  close(fd);
  return 0;
}
