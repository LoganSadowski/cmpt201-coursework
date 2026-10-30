#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid != 0) {
    int wstatus = 0;
    if (waitpid(pid, &wstatus, 0) == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }

    if (WIFEXITED(wstatus)) {
      printf("Child exited normally: %d\n", WEXITSTATUS(wstatus));
    } else {
      printf("Child did not exit normally\n");
    }
  } else {
    execlp("ls", "ls", "-a", "-l", NULL);
  }

  printf("%d\n", getpid());
}
