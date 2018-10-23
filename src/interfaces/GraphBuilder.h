#ifndef _GRAPHBUILDER 
#define _GRAPHBUILDER

#include "../types/graph/Graph.h"

/**
 * Returns Graph* if the build resulted in a valid
 * graph, NULL otherwise
 * */
Graph *buildDependencyGraph(LinkedList *recipes);

#endif