#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
# include <sys/socket.h>
# include <cstring>
# include <iostream>

// エラー処理ほぼないsocket programing

void execute(int client_fd) {
  int recv_size, send_size;
  char recv_buf[1025];
  recv(client_fd, recv_buf, 1024, 0);
  std::cout << recv_buf << std::endl;
}

int main() {
  int fd;
  struct sockaddr_in a_addr;

  // create socket
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1)
    return 1;
  memset(&a_addr, 0, sizeof(struct sockaddr_in));

  // setting server config
  a_addr.sin_family = AF_INET;
  a_addr.sin_port = htons(uint16_t(atoi("8080")));
  inet_aton("127.0.0.1", &a_addr.sin_addr);

  // setting config to socket
  bind(fd, (struct sockaddr *)&a_addr, sizeof(a_addr));

  // wait connection
  listen(fd, 5);
  
  while (1)
  {
    std::cout << "wait connection" << std::endl;
    int client_fd = accept(fd, NULL, NULL);
    std::cout << "conected" << std::endl;
    execute(client_fd);
    close(client_fd);
  }
  close(fd);
}

