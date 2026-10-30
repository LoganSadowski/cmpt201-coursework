#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

struct Node *createNode(int data) {
  struct Node *newNode = malloc(sizeof(*newNode));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void append(struct Node **head, int data) {
  struct Node *newNode = createNode(data);
  if (*head == NULL) {
    *head = newNode;
  } else {
    struct Node *current = *head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = createNode(data);
  }
}

void traverse(struct Node *head) {
  for (struct Node *current = head; current; current = current->next) {
    printf("%d ", current->data);
  }
  printf("\n");
}

int main() {
  struct Node *head = NULL;

  append(&head, 1);
  append(&head, 2);
  append(&head, 3);

  printf("Linked List: ");
  traverse(head);

  struct Node *current = head;
  while (current != NULL) {
    struct Node *temp = current;
    current = current->next;
    free(temp);
  }
  head = NULL;

  return 0;
}
