#ifndef _Target
#define _Target

#include "../linked_list/LinkedList.h"

typedef struct Target {
    char *name;
    /** @type Target* */
    LinkedList *dependencies;
    /** @type char* */
    LinkedList *recipes;
} Target;

/**
 * Allocates memory for and returns a pointer
 * to a new Target
 * 
 * @param name the name of the Target
 * */
Target *newTarget(char *name);

/**
 * Adds a recipe to the specified Target
 */
int addRecipe(Target *t, char *recipe);

/**
 * Adds a dependency to the specified target
 * */
int addDependency(Target *parent, Target *child);

#endif