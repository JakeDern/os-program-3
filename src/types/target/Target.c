#include <stdlib.h>
#include <stdio.h>

#include "./Target.h"
#include "../linked_list/LinkedList.h"

// int main(int argc, char **argv) {

// }

/** @override */
Target *newTarget(char *name) {
  Target *t;
  if ( (t = malloc(sizeof(Target))) == NULL) {
    fprintf(stderr, "failed to allocate memory for target\n");
    exit(1);
  }

  if (name == NULL) {
    fprintf(stderr, "null targets are not allowed\n");
    exit(1);
  }

  t->rebuilt = 0;
  t->name = name;
  t->dependencies = newLinkedList(sizeof(Target), LIST);
  t->recipes = newLinkedList(sizeof(char*), LIST);
  
  return t;
}

/** @override */
int addRecipe(Target *t, char **recipe) {
  add(t->recipes, (void *)recipe);
  return 0;
}

/** @override */
int addDependency(Target *parent, Target *child) {
  add(parent->dependencies, (void*) child);
  return 0;
}