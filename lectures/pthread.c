#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void *func(void *arg) {
  char *str = arg;

  // Print str and thread ID (using gettid())
  printf("%s, %d\n", str, gettid());

  // Return the length of the receieved string
  return (void *)strlen(str);
}

int main() {
  // Create thread
  pthread_t tid;
  char *str = "Hello";
  if (pthread_create(&tid, NULL, func, str) != 0) {
    perror("Unable to create thread");
    exit(EXIT_FAILURE);
  }

  // Wait until thread terminates
  void *ret_val = 0;
  if (pthread_join(tid, &ret_val) != 0) {
    perror("Unable to join thread");
    exit(EXIT_FAILURE);
  }

  // Print the return value
  printf("%lu\n", (uint64_t)ret_val);

  return 0;
}
