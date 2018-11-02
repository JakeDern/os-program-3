#ifndef _FILEPARSER
#define _FILEPARSER

#include <stdlib.h>
#include <stdio.h>
#include "../types/graph/Graph.h"

/**
 * Parses the makefile and creates a dependency graph for the
 * targets
 * 
 * @param filename name of the makefile
 * @returns TargetGraph* the dependency graph
 * */
extern TargetGraph *parseMakefile(char *filename);

#endif