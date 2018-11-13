#include "./interfaces/FileParser.h"
#include "./types/linked_list/LinkedList.h"
#include "./types/linked_list/ListIterator.h"
#include "./interfaces/ProgramBuilder.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct CommandParse {
  char *buildTarget;
  char *makeFile;
  int fflag;
} CommandParse;

static CommandParse *parseCommand(int argc, char **argv);


// TODO -f flag
// TODO check makefile and Makefile

int main(int argc, char **argv) {
  TargetGraph *graph;
  CommandParse *cmd = parseCommand(argc, argv);
  Target *buildTarget;
  
  //create graph
  if (cmd->fflag) {
    if ( (graph = parseMakefile(cmd->makeFile)) == NULL) {
      fprintf(stderr, "Unable to find makefile at %s\n", cmd->makeFile);
    }
  } else {
      if ( (graph = parseMakefile("makefile")) == NULL) {
        if ( (graph = parseMakefile("Makefile")) == NULL) {
          fprintf(stderr, "Unable to find makefile 'makefile' or 'Makefile'\n");
        }
      }
  }

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
  if (cmd->buildTarget != NULL) {
    if ((buildTarget = findBuildTarget(graph, cmd->buildTarget)) == NULL) {
      fprintf(stderr, "build target %s not found in makefile", cmd->buildTarget);
      exit(1);
    }
  } else {
    if (graph->buildTargets->size == 0) {
      fprintf(stderr, "no valid targets in makefile\n");
      exit(1);
    }
    buildTarget = getItemAt(graph->buildTargets, 0);
  }

  buildProgram(buildTarget);
}

static CommandParse *parseCommand(int argc, char **argv) {
  CommandParse *cmd;
  if ((cmd = malloc(sizeof(CommandParse))) == NULL) {
    fprintf(stderr, "Unable to allocate heap memory\n");
    exit(1);
  }
  
  if (argc > 4) {
    fprintf(stderr, "Usage error: too many command arguments\n");
    exit(1);
  }

  if (argc == 1) {
    return cmd;
  }

  if (argc == 4) {
    if ( (strcmp(argv[1], "-f")) == 0) {
      cmd->makeFile = argv[2];
      cmd->buildTarget = argv[3];
      cmd->fflag = 1;
      return cmd;
    }
    else if ( (strcmp(argv[2], "-f")) == 0) {
      cmd->makeFile = argv[3];
      cmd->buildTarget = argv[1];
      cmd->fflag = 1;
      return cmd;
    }
    else {
      fprintf(stderr, "Usage error: too many command arguemnts\n");
      exit(1);
    }
  }
  
  if (argc == 3) {
    if ( (strcmp(argv[1], "-f")) == 0) {
      cmd->makeFile = argv[2];
      cmd->fflag = 1;
    }
    else {
      fprintf(stderr, "Usage eror: too many command arguments\n");
    }
  }

  if (argc == 2) {
    if ( (strcmp(argv[1], "-f")) == 0) {
      fprintf(stderr, "Usage error: -f must be accompanied by a makefile name\n");
      exit(1);
    }
    else {
      cmd->buildTarget = argv[1];
      return cmd;
    }
  }
}