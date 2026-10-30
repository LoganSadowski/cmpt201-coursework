#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
  long long counter = 0;
  time_t start_time = time(NULL);

  while (time(NULL) - start_time < 10) {
    counter++;
  }

  printf("\nProcess %d Completed %lld iterations\n", getpid(), counter);
  return 0;
}
