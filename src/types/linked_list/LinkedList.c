#include "./LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

ListNode *newListNode();

int main(int argc, char **argv) {

}

/** @override */
LinkedList *newLinkedList(size_t dataSize, int isStack) {
  LinkedList *l;
  if ( (l = malloc(sizeof(LinkedList))) == NULL) {
    fprintf(stderr, "Failed to allocate mem for linked list\n");
    exit(1);
  }

  // init head tail and size
  l->head = newListNode(NULL);
  l->tail = l->head;
  l->size = 0;

  // verify valid type of list
  if ( (isStack != STACK) && (isStack != LIST) ) {
    fprintf(stderr, "Invalid list type\n");
    exit(1);
  }

  // set type of list and datasize
  l->type = isStack;
  l->dataSize = dataSize;

  return l;
}

/**
 * Creates and returns a pointer to a new ListNode
 * with the provided data
 * 
 * @private
 * @returns pointer to a new ListNode
 * */
ListNode *newListNode(void *data) {
  ListNode *n;
  if ( (n = malloc(sizeof(ListNode))) == NULL ) {
    fprintf(stderr, "failed allocation for linked list node\n");
    exit(1);
  }

  n->data = data;

  return n;
}

/** @override */
void *pop(LinkedList *l) {
  // verify list is a stack
  if (l->type != STACK) {
    fprintf(stderr, "cannot pop on a non stack\n");
    exit(1);
  }

  // verify list is not empty
  if (isEmptyList(l)) {
    fprintf(stderr, "pop attempted on empty stack\n");
    exit(1);
  }

  // remove head
  ListNode *n = l->head->next;
  l->head->next = l->head->next->next;
  l->size--;

  return n->data;
}

/** @override */
void push(LinkedList *l, void *d) {
  if (l->type != STACK) {
    fprintf(stderr, "cannot push on a non stack\n");
    exit(1);
  }

  ListNode *node = newListNode(d);
  node->next = l->head->next;
  l->head->next = node->next;
  l->size++;
}

/** @override */
void add(LinkedList *l, void *d) {
  if (l->type != LIST) {
    fprintf(stderr, "cannot add on a non list\n");
    exit(1);
  }

  ListNode *node = newListNode(d);
  l->tail->next = node;
  l->tail = node;
  l->size++;
}

/** @override */
void *removeItem(LinkedList *l) {
  if (l->type != LIST) {
    fprintf(stderr, "cannot remove on a non list\n");
    exit(1);
  }

  if (isEmptyList(l)) {
    fprintf(stderr, "remove item attempted on an empty list\n");
    exit(1);
  }

  ListNode *node = l->head->next;
  l->head->next = l->head->next->next;
  l->size--;

  return node->data;
}

/** @override */
void *getItemAt(LinkedList *l, int idx) {
  if (l->size <= idx) {
    fprintf(stderr, "cannot remove item at idx %d for list of size %d\n", idx, l->size);
  }

  ListNode *curr = l->head;
  for (int i = 0; i < idx; i++) {
    curr = curr->next;
  }

  return curr->data;
}

/** @override */
int isEmptyList(LinkedList *l) {
  return (l->size) == 0;
}