#include "./LinkedList.h"
#include "./ListIterator.h"
#include <stdlib.h>
#include <stdio.h>


const int STACK = 1;
const int LIST = 2;

ListNode *newListNode();
static void freeHelper(ListNode *curr);

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
  n->next = NULL;

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
  void *data = n->data;
  l->head->next = l->head->next->next;
  l->size--;

  free(n);
  return data;
}

/** @override */
void push(LinkedList *l, void *d) {
  if (l->type != STACK) {
    fprintf(stderr, "cannot push on a non stack\n");
    exit(1);
  }

  ListNode *node = newListNode(d);
  node->next = l->head->next;
  l->head->next = node;
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
    return NULL;
  }

  ListNode *node = l->head->next;
  void *data = node->data;
  l->head->next = l->head->next->next;
  l->size--;

  free(node);
  return data;
}

/** @override */
void *getItemAt(LinkedList *l, int idx) {
  if (l->size <= idx) {
    fprintf(stderr, "cannot remove item at idx %d for list of size %d\n", idx, l->size);
    exit(1);
  }

  ListNode *curr = l->head;
  for (int i = 0; i <= idx; i++) {
    curr = curr->next;
  }

  return curr->data;
}

/** @override */
int isEmptyList(LinkedList *l) {
  return (l->size) == 0;
}

void* listContains(LinkedList *l, void *item) {

  ListIterator *iterator = newListIterator(l);
  
  while (hasNext(iterator)) {
    if (item == (getNext(iterator))) {
      free(iterator);
      return item;
    }
  }
  free(iterator);
  return NULL;

}

int freeList(LinkedList *l) {
  
    freeHelper(l->head);

    free(l);
    return 1;
  
}

static void freeHelper(ListNode *curr) {

  if(curr == NULL) {
    return;
  }

  freeHelper(curr->next);

  if(curr->data != NULL) {
    free(curr->data);
  }

  free(curr);
  return;

}