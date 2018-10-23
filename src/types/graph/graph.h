#ifndef _GRAPH
#define _GRAPH

#include "../linked_list/LinkedList.h"
#include "../recipe/recipe.h"

typedef struct GraphNode {
    /** @type GraphNode */
    LinkedList *children;
    Recipe *recipe;
} GraphNode;

typedef struct Graph {
    LinkedList nodes;
    int size;
    GraphNode *root;
} Graph;

#endif