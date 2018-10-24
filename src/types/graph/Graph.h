#ifndef _GRAPH
#define _GRAPH

#include "../linked_list/LinkedList.h"
#include "../recipe/Recipe.h"

typedef struct GraphNode {
    /** @type GraphNode */
    LinkedList *children;
    Recipe *recipe;
} GraphNode;

typedef struct RecipeGraph {
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
 * 
 * */
extern void addNode(RecipeGraph *graph, Recipe *r);

/**
 * Finds an returns the node containing the desired
 * recipe.
 * 
 * @returns GraphNode* iff the recipe is found,
 * null otherwise
 * */
extern GraphNode *findRecipe(RecipeGraph *graph, Recipe *target);

#endif