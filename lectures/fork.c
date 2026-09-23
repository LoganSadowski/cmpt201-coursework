#include <stdio.h>
#include <unistd.h>

int main() {
  for (int i = 0; i < 20; i++) {
    printf("forking\n");
    sleep(1);
    fork();
  }
  printf("DONE\n");
  return 1;
}
