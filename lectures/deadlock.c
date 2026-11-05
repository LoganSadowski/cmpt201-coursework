#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;

static void *thread0(void *arg) {
  pthread_mutex_lock(&mutexA);
  printf("A\n");
  pthread_mutex_lock(&mutexB);
  printf("B\n");
  pthread_mutex_unlock(&mutexB);
  pthread_mutex_unlock(&mutexA);
  printf("Thread0 finished\n");
  pthread_exit(0);
}
static void *thread1(void *arg) {
  pthread_mutex_lock(&mutexB);
  printf("B\n");
  pthread_mutex_lock(&mutexA);
  printf("A\n");
  pthread_mutex_unlock(&mutexA);
  pthread_mutex_unlock(&mutexB);
  printf("Thread1 finished\n");
  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  pthread_t t0, t1;
  if (pthread_create(&t0, NULL, thread0, NULL) != 0)
    exit(EXIT_FAILURE);
  if (pthread_create(&t1, NULL, thread1, NULL) != 0)
    exit(EXIT_FAILURE);

  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
}
