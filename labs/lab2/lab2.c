#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char program[50];
  char arg = '.';
  while (1) {
    pid_t pid = fork();
    if (pid == 0) {
      printf("Enter programs to run.\n");
      scanf("%s", program);
      if (execl(program, &arg) == -1) {
        printf("Exec failure\n");
      }
      break;
    }
  }
}
