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

#define BUF_SIZE 1024

// エラー処理ほぼないsocket programing

// 本来なら終了を意味する何kが来るまでここで無限ループする
void execute(int client_fd) {
  int recv_size, send_size;
  char recv_buf[BUF_SIZE], send_buf;

  while (1) {
    recv_size = recv(client_fd, recv_buf, BUF_SIZE, 0);
    if (recv_size < 0) {
      if (errno == EWOULDBLOCK || errno == EAGAIN)
      {
        std::cout << "No data received" << std::endl;
        break ;
      }
      else {
        perror("recv");
        break ;
      }
    }
    recv_buf[recv_size] = '\0';
    std::cout << "Received: " << recv_buf << std::endl;

    if (strcmp(recv_buf, "finish") == 0) {
      send_buf = 0;
      send_size = send(client_fd, &send_buf, 1, 0);
      if (send_size == -1) {
        std::cout << "send error\n" << std::endl;
        break;
      }
    } else {
      send_buf = 1;
      send_size = send(client_fd, &send_buf, 1, 0);
      if (send_size == -1) {
        printf("send error\n");
        break;
      }
    }
  }
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

  // これがあるとI/Oのwait中も他の動作が実行される。ないとI/O待ちで止まる
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
    // std::cout << "wait connection" << std::endl;
    int client_fd = accept(fd, NULL, NULL);

    if (client_fd < 0) {
      if (errno == EWOULDBLOCK || errno == EAGAIN)
      {
        // std::cout << "No incomming connection" << std::endl;
        continue ;
      }
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

