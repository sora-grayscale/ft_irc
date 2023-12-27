#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

// エラー処理ほぼないsocket programing

// 本来なら終了を意味する何kが来るまでここで無限ループする
void execute(int client_fd) {
  int recv_size, send_size;
  char recv_buf[1025];

  recv_size = recv(client_fd, recv_buf, 1024, 0);

  std::cout << recv_buf << std::endl;
}

int main() {
  int fd;
  struct sockaddr_in a_addr;

  // create socket
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return 1;
  }
  memset(&a_addr, 0, sizeof(struct sockaddr_in));

  // # set as a non blocking
  // ただこれを入れるだけだと無限ループになる
  // fcntl(fd, F_SETFL, O_NONBLOCK);
  int flags = fcntl(fd, F_GETFL, 0);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  // これを入れると普通に動くけど、動作が別に変わらん
  // ioctl(fd, (int)FIONBIO, (char *)1L);

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

  while (1) {
    std::cout << "wait connection" << std::endl;
    int client_fd = accept(fd, NULL, NULL);

    if (client_fd < 0) {
      if (errno == EWOULDBLOCK || errno == EAGAIN)
        std::cout << "No incomming connection" << std::endl;
      else {
        perror("accept");
        break;
      }
    } else {
      std::cout << "conected" << std::endl;
      execute(client_fd);
      close(client_fd);
      std::cout << "closed" << std::endl;
    }
  }
  close(fd);
  return 0;
}

