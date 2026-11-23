#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int fd = open("tmp", O_RDWR | O_CREAT, S_IRUSR, S_IWUSR);
  if (write(fd, "Hello World!", 12) < 12) {
    perror("write");
    exit(EXIT_FAILURE);
  }
  lseek(fd, -6, SEEK_CUR);

  char buf[12];
  int bytes = read(fd, &buf, 12);
  write(STDOUT_FILENO, buf, bytes);

  close(fd);
}
