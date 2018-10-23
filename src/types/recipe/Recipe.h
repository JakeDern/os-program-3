#ifndef _RECIPE
#define _RECIPE

#include "../linked_list/LinkedList.h"

typedef struct Recipe {
    char *name;
    /** @type char* */
    LinkedList *dependencies;
    /** @type char* */
    LinkedList *commands;
} Recipe;

/**
 * Allocates memory for and returns a pointer
 * to a new Recipe
 * 
 * @param name the name of the recipe
 * */
Recipe *newRecipe(char *name);

int addCommand(Recipe *recipe, char *command);

int addDependency(Recipe *recipe, char *dependency);

#endif