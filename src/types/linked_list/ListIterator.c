#include <stdlib.h>
#include <stdio.h>
#include "./ListIterator.h"
#include "./LinkedList.h"

int main(int argc, char **argv) {

}

ListIterator *newListIterator(LinkedList *l) {
  if (l == NULL) {
    fprintf(stderr, "cannot create iterator from NULL list\n");
    exit(1);
  }
  
  ListIterator *itr;
  if ( (itr = malloc(sizeof(ListIterator))) == NULL ) {
    fprintf(stderr, "failed ot allocate mem for iterator\n");
    exit(1);
  }

  itr->list = l;
  itr->idx = 0;
  itr->curr = l->head;

  return itr;
}

int hasNext(ListIterator *itr) {
  return itr->curr->next != NULL;
}

void *getNext(ListIterator *itr) {
  if (hasNext(itr) == 0) {
    return NULL;
  }

  ListNode *curr = itr->curr->next;
  itr->curr = itr->curr->next;
  return curr->data;
}

