#ifndef _LISTITERATOR
#define _LISTITERATOR

#include "./LinkedList.h"

typedef struct ListIterator {
  ListNode *head;
  ListNode *curr;
  int idx;
  int size;
} ListIterator;

/**
 * Returns a new iterator for the specified list
 * */
extern ListIterator *newListIterator(LinkedList *l);

/**
 * Determines if there is a next item to retriev from
 * the list this iterator is associated with
 * 
 * @returns 1 iff there is a next item, 0 otherwise
 * */
extern int hasNext(ListIterator *itr);

/**
 * Gets the next value in the list that this iterator is
 * associated with
 * 
 * @returns void* pointer to the next item in the list if
 * it exists, NULL otherwise. 
 * */
extern void* getNext(ListIterator *itr);

#endif