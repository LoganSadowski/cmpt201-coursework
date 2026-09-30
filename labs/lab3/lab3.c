#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print5(char **queue, int head, int tail) {
  for (int i = 0; i < 5 && i <= tail; i++) {
    printf("%s", queue[(head + i) % 5]);
  }
}

int main() {
  int head = 0, tail = 0;
  char *queue[5] = {0};

  while (1) {
    printf("Enter input: ");
    size_t len;
    if (getline(&queue[tail % 5], &len, stdin) == -1) {
      perror("getline");
      exit(EXIT_FAILURE);
    }

    // Print last 5 inputs when the user enters "print"
    // Exit the program if the user enters "exit"
    if (strcmp(queue[tail % 5], "print\n") == 0) {
      print5(queue, head, tail);
    } else if (strcmp(queue[tail % 5], "exit\n") == 0) {
      break;
    }

    tail++;
    if (tail >= 5)
      head++;
  }

  // Free the memory allocated by getline()
  for (int i = 0; i < 5 && i <= tail; i++) {
    free(queue[i]);
  }
}
