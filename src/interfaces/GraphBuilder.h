#ifndef _GRAPHBUILDER 
#define _GRAPHBUILDER

#include "../types/graph/Graph.h"

/**
 * Builds a build dependency graph out of the provided
 * recipes
 * 
 * PRECONDITION: recipes contains no duplicate
 * recipes, the behavior of this function is undefined
 * if it does
 * 
 * @param recipes a list of all recipes that will go into
 * this graph
 * @returns Graph* if the recipe list resulted in a valid
 * graph, NULL otherwise
 * */
Graph *buildDependencyGraph(LinkedList *Targets);

#endif