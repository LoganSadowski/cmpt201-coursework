#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  fork();
  if (getpid() == 0) {
    execl("/usr/bin/ls", ".", "-a", "-l", "-h", NULL);
  } else {
    execl("/usr/bin/ls", ".", "-a", NULL);
  }
  printf("Pid: %d\n", getpid());
}
