#include "./interfaces/FileParser.h"
#include "./types/linked_list/LinkedList.h"
#include "./types/linked_list/ListIterator.h"
#include "./interfaces/ProgramBuilder.h"

int main(int argc, char **argv) {
  TargetGraph *graph;
   
  if ( (graph = parseMakefile("makefile")) == NULL) {
    fprintf(stderr, "failed to find specified makefile\n");
    exit(1);
  }

    printGraph(graph);

  //check for cycles in graph
  ListIterator *iterator = newListIterator(graph->buildTargets);
  while (hasNext(iterator)) {
    Target *curr = getNext(iterator);
    if (hasCycle(curr)) {
      free(iterator);
      fprintf(stderr,"Cycle Detected\n");
      exit(1);
    }
  }
  free(iterator);
  

   // determine build target
  Target *buildTarget;
  if (argc == 2) {
    char *targetName = argv[1];
    if ((buildTarget = findBuildTarget(graph, targetName)) == NULL) {
      fprintf(stderr, "build target %s not found in makefile", targetName);
      exit(1);
    }
  } else if (argc > 2) {
    fprintf(stderr, "Too many commmand line arguments for 537make\n");
    exit(1);
  } else {
    if (graph->buildTargets->size == 0) {
      fprintf(stderr, "no targets in makefile\n");
      exit(1);
    }
    buildTarget = getItemAt(graph->buildTargets, 0);
  }

  buildProgram(buildTarget);
}