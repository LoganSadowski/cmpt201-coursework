#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  char *program = NULL;
  size_t len = 0;
  while (1) {
    printf("Enter a program to run\n");
    getline(&program, &len, stdin);

    char *newline = strchr(program, '\n');
    if (newline) {
      *newline = '\0';
    }

    pid_t pid = fork();

    if (pid != 0) {
      int wstatus = 0;
      if (waitpid(pid, &wstatus, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }
    } else {
      if (execlp(program, program, (char *)NULL) == -1) {
        perror("execlp");
        exit(EXIT_FAILURE);
      }
    }
  }
}
