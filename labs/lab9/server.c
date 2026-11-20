#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 64
#define PORT 8000
#define LISTEN_BACKLOG 32

#define handle_error(msg)                                                                          \
  do {                                                                                             \
    perror(msg);                                                                                   \
    exit(EXIT_FAILURE);                                                                            \
  } while (0)

// Shared counters for: total # messages, and counter of clients (used for
// assigning client IDs)
int total_message_count = 0;
int client_id_counter = 1;

// Mutexs to protect above global state.
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t client_id_mutex = PTHREAD_MUTEX_INITIALIZER;

struct client_info {
  int cfd;
  int client_id;
};

void *handle_client(void *arg) {
  struct client_info *client = (struct client_info *)arg;

  printf("New client created! ID %d on socket FD %d\n", client->client_id, client->cfd);
  char buf[1024];
  while (1) {
    int bytes = read(client->cfd, buf, 1024);
    if (bytes <= 0) {
      break;
    }
    buf[bytes] = '\0';

    pthread_mutex_lock(&count_mutex);
    total_message_count++;
    pthread_mutex_unlock(&count_mutex);
    printf("MSG #\t%d; Client ID %d: %s", total_message_count, client->client_id, buf);
  }

  close(client->cfd);
  printf("Ending thread for client %d\n", client->client_id);
  return NULL;
}

int main() {
  struct sockaddr_in addr;
  int sfd;

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    handle_error("socket");
  }

  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) {
    handle_error("bind");
  }

  if (listen(sfd, LISTEN_BACKLOG) == -1) {
    handle_error("listen");
  }

  struct client_info *cl_info[16];
  pthread_t tid;

  for (;;) {
    // create a new thread when a new connection is encountered
    cl_info[client_id_counter - 1] = malloc(sizeof(struct client_info));
    struct client_info *info = cl_info[client_id_counter - 1];
    if (info == NULL) {
      handle_error("malloc");
    }
    info->cfd = accept(sfd, NULL, NULL);
    info->client_id = client_id_counter;

    // call handle_client() when launching a new thread, and provide client_info
    pthread_create(&tid, NULL, handle_client, info);
    pthread_detach(tid);
    client_id_counter++;
  }

  if (close(sfd) == -1) {
    handle_error("close");
  }

  return 0;
}
