#ifndef _GRAPH
#define _GRAPH

#include "../linked_list/LinkedList.h"
#include "../target/Target.h"

typedef struct TargetGraph {
    LinkedList *targets;
    LinkedList *buildTargets;
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
 * */
extern void addTarget(TargetGraph *graph, Target *t);

/**
 * Adds a buildTarget node to be associated to this graph. This method
 * does not draw and arcs between the node containing
 * this recipe and any others
 * 
 * */
extern void addBuildTarget(TargetGraph *graph, Target *t);


/**
 * Finds an returns the node containing the desired
 * Target.
 * 
 * @returns GraphNode* iff the Target is found,
 * null otherwise
 * */
extern Target *findTarget(TargetGraph *graph, char *target);

/**
 * Finds an returns the node containing the desired
 * Target.
 * 
 * @returns GraphNode* iff the Buildtarget is found,
 * null otherwise
 * */
extern Target *findBuildTarget(TargetGraph *graph, char *target);

/*
 * Determines whether a graph containing this target contains a cycle
 * 
 *@param t is the target in question 
 * @return 1 if there exists a cycle, 0 if there is no cycle
 * */
extern int hasCycle(Target *t);


#endif