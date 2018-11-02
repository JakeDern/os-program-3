#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../interfaces/FileParser.h"
#include "../types/target/Target.h"
#include "../types/linked_list/ListIterator.h"

const int MAX_NAME_LENGTH = 200;
const int MAX_LINE_LENGTH = 10000;

static int nextLine(char *buff, int max, FILE *fptr, int lineCount);
static Target *readTarget(char* line, int lineLength, TargetGraph *g, int lineCount);
static char *readRecipe(char* line, int lineLength, int lineCount);
static int isValidTarget(char *s);
static Target *findOrCreateTarget(char *s, TargetGraph *g);
static Target *findOrCreateRoot(char *s, TargetGraph *g);
static int isWhiteSpace(char c);
static int isBlankLine(char *line, int length, int lineCount);

/** @override */
TargetGraph *parseMakefile(char *filename) {
  // open file
  FILE *fptr;
  if ( (fptr = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "failed to find makefile\n");
    exit(1);
  }

  int lineCnt = 1;
  char readBuff[MAX_LINE_LENGTH];
  Target *currTarget = NULL;
  TargetGraph *graph = newTargetGraph();
  while (!feof(fptr)) {
    int lineLength = nextLine(readBuff, MAX_LINE_LENGTH, fptr, lineCnt);
    char firstChar = readBuff[0];
    printf("line %d: %s\n", lineCnt, readBuff);
    switch (firstChar) {
      case '#': {
        break;
      }
      case '\t': {
        if (currTarget == NULL) {
          fprintf(stderr, "recipe detected before target\n");
          exit(1);
        }
        //TODO handle bad lines starting with multiple tabs
        char *recipe = readRecipe(readBuff, lineLength, lineCnt);
        addRecipe(currTarget, recipe);
      }
      case '\0':
      case '\n': {
        break;
      }
      case ' ': {
        if (isBlankLine(readBuff, lineLength, lineCnt) == 0) {
          fprintf(stderr, "Invalid line at line number %d\n", lineCnt);
          exit(1);
        } 
        break;
      }
      default: {
        currTarget = readTarget(readBuff, lineLength, graph, lineCnt);
      }
    }
    lineCnt++;
  }

  ListIterator *targetItr = newListIterator(graph->targets);
  ListIterator *buildItr = newListIterator(graph->buildTargets);
  
  printf("ALL TARGETS: \n\n");
  while (hasNext(targetItr)) {
    Target *curr = (Target*)getNext(targetItr);
    printf("%s: ", curr->name);
    ListIterator *depItr = newListIterator(curr->dependencies);
    while (hasNext(depItr)) {
      Target *dep = (Target *)getNext(depItr);
      printf("%s ", dep->name);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("ROOT TARGETS: \n\n");
  while (hasNext(buildItr)) {
    Target *curr = (Target*)getNext(buildItr);
    printf("%s: ", curr->name);
    ListIterator *depItr = newListIterator(curr->dependencies);
    while (hasNext(depItr)) {
      Target *dep = (Target *)getNext(depItr);
      printf("%s ", dep->name);
    }
    printf("\n");
  }
  printf("\n\n");

  // TODO no
  return NULL;
}

static int nextLine(char *buff, int max, FILE *fptr, int lineCount) {
  int length = 0;
  char c;
  int done = 0;
  while (length < max && !done) {
    c = fgetc(fptr);
    length++;
    switch (c) {
      case EOF:
      case '\n': {
        buff[length - 1] = '\0';
        done = 1;
        break;
      }
      default: {
        buff[length - 1] = c;
      }
    }
  }

  if (done) {
    return length;
  } else {
    fprintf(stderr, "Line exceeded maximum length of %d on line %d\n", max, lineCount);
    exit(1);
  }
}

static Target *readTarget(char* line, int lineLength, TargetGraph *g, int lineCount) {
  // fetch name of target
  // TODO handle when there is no colon, strok just resturns whole line
  // instead of null
  char *tName;
  tName = strtok(line, ":");

  // if NULL, reject line as invalid
  if (tName == NULL) {
    fprintf(stderr, "Invalid line detected on line %d\n", lineCount);
    exit(1);
  }
  
  // invalid
  Target* t = findOrCreateRoot(tName, g);
  if (t == NULL) {
    fprintf(stderr, "Invalid or duplicate target found on line %d\n", lineCount);
    exit(1);
  }

  /**
   * Parse all dependencies, create their nodes if necessary,
   * and draw arcs from the target to all of them in the graph
   * */
  char *depName;
  while ( (depName = strtok(NULL, " \t") ) != NULL ) {
    int depLen = isValidTarget( depName );
    Target *dep;
    if ( depLen != 0) {
      dep = findOrCreateTarget(depName, g);
      if (dep == NULL) {
        fprintf(stderr, "Invalid dependency \"%s\" found on line %d", depName, lineCount);
        exit(1);
      }
    } else {
      fprintf(stderr, "Invalid dependency name \"%s\" found on line %d", depName, lineCount);
      exit(1);
    }

    addDependency(t, dep);
  }
  return t;
}

/**
 * Determines if the provided string is a valid name for a
 * target.
 * 
 * @param s the string
 * @returns the length of the string if it is a valid target
 * name, 0 otherwise
 * */
static int isValidTarget(char *s) {
  char c;
  int idx = 0;
  while ( (c = s[idx]) != '\0' ) {
    switch (c) {
      case '\t':
      case ' ':
      case ':': {
        return 0;
      }
      default: {
        idx++;
      }
    }
  }

  return idx;
}

/**
 * Finds the BuildTarget in the provided graph if it already
 * exists or creates the BuildTarget if it does not.
 * 
 * @param s the target name
 * @param s the graph it belongs to
 * @returns Target* representing the target with the name provided
 * if that target was valid. NULL if the name was a duplicate of a
 * BuildTarget in the graph already
 * */
static Target *findOrCreateRoot(char *s, TargetGraph *g) {
  Target *t = NULL;
  if ( (t = findBuildTarget(g, s)) == NULL) {
    if ( (t = findTarget(g, s)) == NULL) {
      char *tName = strdup(s);
      t = newTarget(tName);
      addTarget(g, t);
      addBuildTarget(g, t);
    }
  } else {
    return NULL;
  }

  return t;
}

/**
 * Finds the Target in the provided graph if it already
 * exists or creates the BuildTarget if it does not.
 * 
 * @param s the target name
 * @param s the graph it belongs to
 * @returns Target* representing the target with the name provided
 * if that target was valid. NULL if the name was a duplicate of a
 * BuildTarget in the graph already
 * */
static Target *findOrCreateTarget(char *s, TargetGraph *g) {
  Target *t = NULL;
  if ( (t = findBuildTarget(g, s)) == NULL) {
    if ( (t = findTarget(g, s)) == NULL) {
      char *tName = strdup(s);
      t = newTarget(tName);
      addTarget(g, t);
    }
  }
  // TODO look at this logic again
  // } else {
  //   return NULL;
  // }

  return t;
}

static int isBlankLine(char *line, int lineLength, int lineCount) {
  for (int i = 0; i < lineLength; i++) {
    if (isWhiteSpace(line[i]) != 0) {
      return 0;
    }
  }

  return 1;
}

static char *readRecipe(char* line, int lineLength, int lineCount) {
  return strdup(line+1);
}

static int isWhiteSpace(char c) {
  switch (c) {
    case ' ':
    case '\t': {
      return 1;
    }
    default: {
      return 0;
    }
  }
}