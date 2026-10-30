#include <stdio.h>
#include <unistd.h>

int main() {
  void *currBreak = sbrk(0);
  printf("First program break: \t%p\n", currBreak);

  currBreak = (void *)sbrk(0);
  printf("Second program break: \t%p\n", currBreak);

  currBreak = (void *)sbrk(1024);
  printf("Third program break: \t%p\n", currBreak);

  currBreak = (void *)sbrk(0);
  printf("Fourth program break: \t%p\n", currBreak);

  return 0;
}
