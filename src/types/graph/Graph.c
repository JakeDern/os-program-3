#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Graph.h"
#include "../linked_list/ListIterator.h"
#include "../linked_list/LinkedList.h"

static int containsTarget(Target *t, LinkedList *l);
static int hasCycleHelper(Target *t, LinkedList *l);

// int main(int argc, char **argv) {
  
// }

/** @override */
TargetGraph *newTargetGraph() {
  TargetGraph *g;
  if( (g = malloc(sizeof(TargetGraph))) == NULL) {
    fprintf(stderr, "failed to allocate mem for graph\n");
    exit(1);
  }

  size_t targetSize = sizeof(Target);
  g->targets = newLinkedList(targetSize, LIST);
  g->buildTargets = newLinkedList(targetSize, LIST);
  return g;
}

/** @override */
int addArc(Target *parent, Target *child) {
  add(parent->dependencies, (void*) child);
  return 0;
}


/** @override */
void addTarget(TargetGraph *graph, Target *t) {
  add(graph->targets, t);
}

/** @override */
void addBuildTarget(TargetGraph *graph, Target *t) {
    add(graph->buildTargets, t);
}

/** @override */
Target *findTarget(TargetGraph *graph, char *t) {
  ListIterator *itr = newListIterator(graph->targets);
  while (hasNext(itr)) {
    Target *curr = getNext(itr);
    
    if (strcmp(curr->name, t) == 0) {
      return curr;
    }
  }

  return NULL;
}

/** @override */
Target *findBuildTarget(TargetGraph *graph, char *t) {
  ListIterator *itr = newListIterator(graph->buildTargets);
  while (hasNext(itr)) {
    Target *curr = getNext(itr);
    
    if (strcmp(curr->name, t) == 0) {
      return curr;
    }
  }

  return NULL;
}


/** @override */
int hasCycle(Target *t) {

  ListIterator *iterator = newListIterator(t->dependencies);
  LinkedList *l = newLinkedList(sizeof(Target*), STACK);
  int returnVal = 0;

  push(l, t);
  while(hasNext(iterator)) {
    Target *next = getNext(iterator);
    if (hasCycleHelper(next, l)) {
      return 1;
    }
  }

  return 0;  
}

static int hasCycleHelper(Target *t, LinkedList *l) {
  ListIterator *iterator = newListIterator(t->dependencies);
  
  if (listContains(l, t)) {
    return 1;
  }

  push(l, t);

  while(hasNext(iterator)) {
    Target *next = getNext(iterator);
    if (hasCycleHelper(next, l)) {
      return 1;
    }
  }

  pop(l);
  return 0;

}

static int containsTarget(Target *t, LinkedList *l) {
  ListIterator *iterator = newListIterator(l);
  while (hasNext(iterator)) {
    if (t == (Target*)getNext(iterator)) {
      return 1;
    }
  }
  return 0;
}
