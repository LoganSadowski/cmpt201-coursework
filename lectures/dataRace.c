#include <pthread.h>
#include <stdio.h>

int cnt = 0;
void *count(void *arg) {
  for (int i = 0; i < 10000000; i++) {
    cnt++;
  }
  return 0;
}

int main() {
  pthread_t tid1;
  pthread_create(&tid1, NULL, count, NULL);
  pthread_t tid2;
  pthread_create(&tid2, NULL, count, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  printf("cnt = %d\n", cnt);
  return 0;
}
