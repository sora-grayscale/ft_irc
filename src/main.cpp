#include "ircserv.hpp"
#include "util.hpp"
#include "Server.hpp"

// 今はfdで処理しているのをclassで渡してuserとかをこのexecuteでできるようにする
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
    close(client_fd);
    std::cout << "closed" << std::endl;
    if (send_size == -1) {
      std::cerr << "send error\n" << std::endl;
      return 1;
    }
  } else if (strcmp(recv_buf, "NICK") == 0) {
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
  return 0;
}

int main() {
  Util::start_announce();
  Server server;
  if (server.init())
    return 1;
  while (1) {
    if (server.start())
      break;
  }
  close(server.getfd());
  return 0;
}
