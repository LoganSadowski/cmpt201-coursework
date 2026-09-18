#include <stdio.h>
#include <unistd.h>

int main() {
  while (1) {
    sleep(3);
    printf("Slept for 3 seconds\n");
  }
  return 1;
}
