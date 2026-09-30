#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main() {
  int head = 0, curr = 0;
  char *queue[5] = {0};

  while (1) {
    printf("Enter input: ");
    char *input = NULL;
    size_t len;
    if (getline(&input, &len, stdin) == -1) {
      perror("getline");
      exit(EXIT_FAILURE);
    }

    queue[curr % 5] = input;
    curr++;
    if (curr >= 5)
      head++;
    printf("%s", queue[curr % 5]);
  }
}
