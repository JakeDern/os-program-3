#ifndef _GRAPH
#define _GRAPH

#include "../linked_list/LinkedList.h"
#include "../target/Target.h"

typedef struct GraphNode {
    /** @type GraphNode */
    LinkedList *children;
    Target *Target;
} GraphNode;

typedef struct TargetGraph {
    int size;
    LinkedList nodes;
    GraphNode *root;
} Graph;

/**
 * Allocates memory for and returns a 
 * pointer to a new GraphNode
 * */
extern Graph *newRecipeGraph();

/**
 * Searches the graph for the parent and child nodes,
 * and adds creates an arc from parent to child.
 * 
 * @returns 0 if the operation was successful, 1 if either
 * the parent or child were not found 
 * */
extern int addArc(GraphNode *parent, GraphNode *child);

/**
 * Adds a node to be associated to this graph. This method
 * does not draw and arcs between the node containing
 * this recipe and any others
 * 
 * TODO: int return type?
 * */
void addNode(TargetGraph *graph, Target *r);

/**
 * Finds an returns the node containing the desired
 * Target.
 * 
 * @returns GraphNode* iff the Target is found,
 * null otherwise
 * */
GraphNode *findTarget(Target *target);

#endif