#ifndef _GRAPHBUILDER 
#define _GRAPHBUILDER

#include "../types/graph/Graph.h"

/**
 * Determines if the given graph has a cycle
 * by performing a depth first seach.
 * 
 * @returns 1 iff the graph is cyclical, 0 otherwise
 * */
int hasCycle(GraphNode *root);

#endif