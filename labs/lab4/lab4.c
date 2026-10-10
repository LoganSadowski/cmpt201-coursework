#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[256];
  ssize_t len = snprintf(buf, 256, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    perror("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

void print_bytes(void *start, int c) {
  const unsigned char *bytes = (const unsigned char *)start;

  char buf[16];
  for (int i = 0; i < c; i++) {
    ssize_t len = snprintf(buf, 16, "%3u\n", bytes[i]);
    write(STDOUT_FILENO, buf, len);
  }
}

int main() {
  void *start_add = sbrk(256);
  struct header *block1 = (struct header *)start_add;
  struct header *block2 = (struct header *)(start_add + 128);
  block1->size = 128;
  block1->next = NULL;
  block2->size = 128;
  block2->next = block1;

  memset(block1 + 1, 0, 128 - sizeof(struct header));
  memset(block2 + 1, 1, 128 - sizeof(struct header));

  print_out("first block: \t\t%p\n", &block1, sizeof(&block1));
  print_out("second block: \t\t%p\n", &block2, sizeof(&block2));
  print_out("first block size: \t%d\n", &block1->size, sizeof(&block1->size));
  print_out("first block next: \t%p\n", &block1->next, sizeof(&block1->next));
  print_out("second block size: \t%d\n", &block2->size, sizeof(&block2->size));
  print_out("second block next: \t%p\n", &block2->next, sizeof(&block2->next));

  print_bytes(block1 + 1, 128 - sizeof(struct header));
  print_bytes(block2 + 1, 128 - sizeof(struct header));

  return 0;
}
