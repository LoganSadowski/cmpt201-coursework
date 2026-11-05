#include <pthread.h>
#include <stdio.h>

static pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;
static int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

static void *thread0(void *arg) {
  int count = 0;

  pthread_mutex_lock(&data_mutex);
  {
    for (int i = 0; i < 10; i++) {
      count += data[i];
    }
  }
  pthread_mutex_unlock(&data_mutex);
  printf("Sum is %d\n", count);
  pthread_exit(0);
}

static void *thread1(void *arg) {
  pthread_mutex_lock(&data_mutex);
  {
    for (int i = 0; i < 10; i++) {
      data[i]++;
    }
  }
  pthread_mutex_unlock(&data_mutex);
  printf("Done update!\n");
  pthread_exit(0);
}

int main() {
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, thread0, NULL);
  pthread_create(&tid2, NULL, thread1, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  return 0;
}
