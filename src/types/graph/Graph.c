#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Graph.h"
#include "../linked_list/ListIterator.h"
#include "../linked_list/LinkedList.h"

int main(int argc, char **argv) {
  
}

/** @override */
TargetGraph *newTargetGraph() {
  TargetGraph *g;
  if( (g = malloc(sizeof(TargetGraph))) == NULL) {
    fprintf(stderr, "failed to allocate mem for graph\n");
    exit(1);
  }

  size_t targetSize = sizeof(Target);
  g->targets = newLinkedList(targetSize, LIST);

  return g;
}

/** @override */
int addArc(Target *parent, Target *child) {
  add(parent->dependencies, (void*) child);
  return 0;
}


/** @override */
void addTarget(TargetGraph *graph, Target *t) {
  if (findTarget(graph, t) != NULL) {
    fprintf(stderr, "error: Target %s is already in the graph\n", t->name);
    exit(1);
  }

  add(graph->targets, t);
}

/** @override */
Target *findTarget(TargetGraph *graph, Target *t) {
  ListIterator *itr = newListIterator(graph->targets);
  while (hasNext(itr)) {
    Target *curr = getNext(itr);
    
    if (strcmp(curr->name, t->name) == 0) {
      return curr;
    }
  }

  return NULL;
}
