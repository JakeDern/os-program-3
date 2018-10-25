#ifndef _LINKEDLIST
#define _LINKEDLIST

#include <stdlib.h>

const int STACK = 1;
const int LIST = 2;

typedef struct ListNode {
    struct ListNode *next;
    void *data;
} ListNode; 

typedef struct LinkedList {
    ListNode *head;
    ListNode *tail;
    int size;
    int type;
    size_t dataSize;
} LinkedList;

/**
 * Allocates memory for and returns a new Linked List
 * 
 * @param dataSize the size of the data in this list
 * @param isStack indicates if this is to be a list or
 * stack
 * @returns LinkedList*
 * */
extern LinkedList *newLinkedList(size_t dataSize, int isStack);

/**
 * Removes an item from the front of this list,
 * fails and exits if the list is not a stack
 * 
 * @returns pointer to next item in the list, or
 * NULL if this list is empty
 * */
extern void *pop(LinkedList *l);

/**
 * Pushes an item to the front of this list,
 * fails and exits if the list is not a stack
 * */
extern void push(LinkedList *l, void *d);

/**
 * Adds an item to the end of a LinkedList
 * 
 * @param l the list
 * @param d the data to add to the list
 * */
extern void add(LinkedList *l, void *d);

/**
 * Removes the first item in this list
 *
 * @param l the list
 * @returns a pointer to the first item in the list
 * if it is not empty, NULL otherwise.
 * */
extern void *removeItem(LinkedList *l);

/**
 * Determines if the given list is empty
 * 
 * @returns 1 iff the list is empty, 0 otherwise
 * */
extern int isEmptyList(LinkedList *l);

/**
 * Retrieves and returns the item at the specified index
 * 
 * */
extern void* getItemAt(LinkedList *l, int idx);

#endif