#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
# include <sys/socket.h>
# include <cstring>
# include <iostream>

int main() {
  int fd;
  struct sockaddr_in a_addr;

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1)
    return 1;
  memset(&a_addr, 0, sizeof(struct sockaddr_in));

  a_addr.sin_family = AF_INET;
  a_addr.sin_port = htons(uint16_t(atoi("3368")));
  inet_aton("127.0.0.1", &a_addr.sin_addr);

  bind(fd, (struct sockaddr *)&a_addr, sizeof(a_addr));

  listen(fd, 5);
}

