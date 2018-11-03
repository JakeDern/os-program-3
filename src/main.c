#include "./interfaces/FileParser.h"
#include "./types/linked_list/LinkedList.h"
#include "./types/linked_list/ListIterator.h"
#include "./modules/ProgramBuilder.h"

int main(int argc, char **argv) {
  
  TargetGraph *graph;
   
  if ((graph = parseMakefile("makefile")) == NULL) {
    exit(1);
  }

  //check for cycles in graph
  ListIterator *iterator = newListIterator(graph->buildTargets);
  while (hasNext(iterator)) {
    Target *curr = getNext(iterator);
    if (hasCycle(curr)) {
      fprintf(stderr, "Cyclical dependency detected with target %s exiting program\n", curr->name);
      exit(1);
    }
  }
  

   // determine build target
  if (argc == 2) {
    char *buildTarget = argv[1];
  } else if (argc > 2) {
    fprintf(stderr, "Too many commmand line arguments for 537make\n");
    exit(1);
  } else {
    char *buildTarget = getItemAt(graph->buildTargets, 0);
  }

  buildProgram(buildTarget);
  

}