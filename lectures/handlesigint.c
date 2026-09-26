#define _POSIX_C_SOURCE_
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handle_sigint() {
  char *message = "CTRL-C Pressed";
  write(STDOUT_FILENO, message, strlen(message));
}
