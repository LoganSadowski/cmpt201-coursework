#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *input = NULL;
  size_t size = 0;

  char *token;
  char *saveptr;

  while (1) {
    printf("Please enter some text: ");
    if (getline(&input, &size, stdin) == -1) {
      perror("getline failed");
      exit(EXIT_FAILURE);
    }
    printf("Tokens:\n");

    while (1) {
      token = strtok_r(input, " \t", &saveptr);
      if (token == NULL)
        break;
      printf("\t%s\n", token);
      input = NULL;
    }
  }

  free(input);
  return 0;
}
