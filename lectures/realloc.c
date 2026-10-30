#include <stdlib.h>
#include <string.h>

int main() {
  char *str = "Hello world";
  int len = strlen(str);
  str = realloc(&str, len);

  return 0;
}
