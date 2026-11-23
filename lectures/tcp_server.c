#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
  int listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (listen_fd < 0) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_un my_addr;
  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sun_family = AF_UNIX;
  strncpy(my_addr.sun_path, "my_path", sizeof(my_addr.sun_path) - 1);
  if (bind(listen_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_un)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (listen(listen_fd, 10) != 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  int connection_fd = accept(listen_fd, NULL, NULL);
  if (connection_fd < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  char buff[1024];
  ssize_t bytes_read = 0;
  while ((bytes_read = read(connection_fd, buff, 1024)) > 0) {
    write(STDOUT_FILENO, buff, bytes_read);
  }
  close(connection_fd);
  close(listen_fd);
}
