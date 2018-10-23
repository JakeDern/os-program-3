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
GraphNode *newGraphNode();

/**
 * Allocates memory for and returns a 
 * pointer to a new GraphNode
 * */
Graph *newRecipeGraph();

/**
 * Adds a child to the provided graph node
 * */
void addChild(GraphNode *parent, GraphNode *child);

/**
 * 
 * */
void addNode(RecipeGraph *graph, Recipe *r);

/**
 * Finds an returns the node containing the desired
 * recipe.
 * 
 * @returns GraphNode* iff the recipe is found,
 * null otherwise
 * */
GraphNode *findRecipe(Recipe *target);

#endif