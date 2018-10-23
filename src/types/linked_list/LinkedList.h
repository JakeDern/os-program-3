#ifndef _LINKEDLIST
#define _LINKEDLIST

typedef struct ListNode {
    void *data;
    ListNode *next;
} ListNode; 

typedef struct LinkedList {
    ListNode *head;
    ListNode *tail;
    int size;
    int isStack;
    size_t dataSize;
} LinkedList;

LinkedList *newLinkedList(size_t dataSize, int isStack);

/**
 * Removes an item from the front of this list,
 * fails and exits if the list is not a stack
 * 
 * @returns pointer to next item in the list, or
 * NULL if this list is empty
 * */
void *pop(LinkedList *l);

/**
 * Pushes an item to the front of this list,
 * fails and exits if the list is not a stack
 * */
void push(LinkedList *l, void *d);

/**
 * Adds an item to the end of a LinkedList
 * 
 * @param l the list
 * @param d the data to add to the list
 * */
void add(LinkedList *l, void *d);

/**
 * Removes the first item in this list
 *
 * @param l the list
 * @returns a pointer to the first item in the list
 * if it is not empty, NULL otherwise.
 * */
void *remove(LinkedList *l);

/**
 * Determines if the given list is empty
 * 
 * @returns 1 iff the list is empty, 0 otherwise
 * */
int isEmpty(LinkedList *l);

#endif