#ifndef _Target
#define _Target

#include "../linked_list/LinkedList.h"

typedef struct Target {
    char *name;
    /** @type char* */
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

int addRecipe(char *recipe);

int addDependency(char *dependency);

#endif