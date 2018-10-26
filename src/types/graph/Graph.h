#ifndef _GRAPH
#define _GRAPH

#include "../linked_list/LinkedList.h"
#include "../target/Target.h"

typedef struct TargetGraph {
    LinkedList *targets;
} TargetGraph;

/**
 * Allocates memory for and returns a 
 * pointer to a new GraphNode
 * */
extern TargetGraph *newTargetGraph();

/**
 * Searches the graph for the parent and child nodes,
 * and adds creates an arc from parent to child.
 * 
 * @returns 0 if the operation was successful, 1 if either
 * the parent or child were not found 
 * */
extern int addArc(Target *parent, Target *child);

/**
 * Adds a node to be associated to this graph. This method
 * does not draw and arcs between the node containing
 * this recipe and any others
 * 
 * TODO: int return type?
 * */
extern void addTarget(TargetGraph *graph, Target *t);

/**
 * Finds an returns the node containing the desired
 * Target.
 * 
 * @returns GraphNode* iff the Target is found,
 * null otherwise
 * */
extern Target *findTarget(TargetGraph *graph, Target *target);

#endif