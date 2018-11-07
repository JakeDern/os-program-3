#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../interfaces/FileParser.h"
#include "../types/target/Target.h"
#include "../types/linked_list/ListIterator.h"
#include "../types/linked_list/LinkedList.h"

const int MAX_NAME_LENGTH = 255;
const int MAX_LINE_LENGTH = 1024;

static int nextLine(char *buff, int max, FILE *fptr, int lineCount);
static Target *readTarget(char* line, int lineLength, TargetGraph *g, int lineCount);
static char **readRecipe(char* line, int lineLength, int lineCount);
static int isValidTarget(char *s);
static Target *findOrCreateTarget(char *s, TargetGraph *g);
static Target *findOrCreateRoot(char *s, TargetGraph *g);
static int isWhiteSpace(char c);
static int isBlankLine(char *line, int length);
void printGraph(TargetGraph *graph);
static int isValidRecipeToken(char *token);
static void trimWhitespace(char *token);
static void rewindAndPerror(FILE *fptr, int len, int lineNum);

/** @override */
TargetGraph *parseMakefile(char *filename) {
  // open file
  FILE *fptr;
  if ( (fptr = fopen(filename, "r")) == NULL) {
    return NULL;
  }

  int lineCnt = 1;
  char readBuff[MAX_LINE_LENGTH];
  Target *currTarget = NULL;
  TargetGraph *graph = newTargetGraph();
  while (!feof(fptr)) {
    long int filePos = ftell(fptr);
    int lineLength = nextLine(readBuff, MAX_LINE_LENGTH, fptr, lineCnt);
    char firstChar = readBuff[0];

    switch (firstChar) {
      case '#': {
        break;
      }
      case '\t': {
        if (currTarget == NULL) {
          rewindAndPerror(fptr, filePos, lineCnt);
        }
        //TODO handle bad lines starting with multiple tabs
        char **recipe = readRecipe(readBuff, lineLength, lineCnt);
        if (recipe == NULL ){
          rewindAndPerror(fptr, filePos, lineCnt);
        }
        addRecipe(currTarget, recipe);
      }
      case '\0':
      case '\n': {
        break;
      }
      case ' ': {
        if (isBlankLine(readBuff, lineLength) == 0) {
          rewindAndPerror(fptr, filePos, lineCnt);
        } 
        break;
      }
      default: {
        currTarget = readTarget(readBuff, lineLength, graph, lineCnt);
        if (currTarget == NULL) {
          rewindAndPerror(fptr, filePos, lineCnt);
        }
      }
    }
    lineCnt++;
  }

  return graph;
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
    fprintf(stderr, "%d: Invalid line: %s...\n", lineCount, buff);
    exit(1);
  }
}

static Target *readTarget(char* line, int lineLength, TargetGraph *g, int lineCount) {
  // fetch name of target
  if (strchr(line, ':') == NULL) {
    return NULL;
  }

  char *tName;
  tName = strtok(line, ":");
  trimWhitespace(tName);
  // if NULL, reject line as invalid
  if ( (tName == NULL) || (isValidTarget(tName) == 0) ) {
    return NULL;
  }
  
  // invalid
  Target* t = findOrCreateRoot(tName, g);
  if (t == NULL) {
    return NULL;
  }

  /**
   * Parse all dependencies, create their nodes if necessary,
   * and draw arcs from the target to all of them in the graph
   * */
  char *depName;
  while ( (depName = strtok(NULL, " ") ) != NULL ) {
    int depLen = isValidTarget( depName );
    Target *dep;
    if ( depLen != 0) {
      dep = findOrCreateTarget(depName, g);
      if (dep == NULL) {
        return NULL;
      }
    } else {
      return NULL;
    }

    addDependency(t, dep);
  }
  return t;
}

static void trimWhitespace(char *token) {
  int lastChar = 0;
  int idx = 0;
  char c;
  while ( (c = token[idx]) != '\0') {
    if (isWhiteSpace(c) != 1) {
      lastChar = idx;
    }
    idx++;
  }
  token[lastChar+1] = '\0';
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
    } else {
      addBuildTarget(g ,t);
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

  return t;
}

static int isBlankLine(char *line, int lineLength) {
  for (int i = 0; i < lineLength; i++) {
    if (isWhiteSpace(line[i]) != 1) {
      return 0;
    }
  }

  return 1;
}

static char **readRecipe(char* line, int lineLength, int lineCount) {
  char *tok;
  LinkedList *tokens = newLinkedList(sizeof(char*), LIST);
  tok = strtok(line, " \t");
  
  if (tok == NULL) {
    return NULL;
  }

  while (tok != NULL) {
    if (isValidRecipeToken(tok) == 0) {
      freeList(tokens);
      return NULL;
    } else {
      add(tokens, (void*)strdup(tok));
    }
    tok = strtok(NULL, " \t");
  }

  char **argv = malloc(((tokens->size) + 1) * sizeof(char*));
  int idx = 0;
  char *curr = (char*)removeItem(tokens);
  int last = tokens->size;
  while (curr != NULL) {
    argv[idx] = curr;
    curr = removeItem(tokens);
    idx++;
  }
  argv[last + 1] = NULL;

  free(tokens->head);
  free(tokens);

  // //printf:("recipe: ");
  // printf("recipe: ");
  // for (int i = 0; i < idx; i++) {
  //   printf("\"%s\" ", argv[i]);
  // }
  // printf("\n");

  return argv;
}

static int isValidRecipeToken(char *token) {
  char c = '1'; 
  int idx = 0;
  while (c != '\0') {
    c = token[idx];
    switch(c) {
      case ' ':
      case '\t':
      case '\n':
      case ':': {
        return 0;
      }
      default: {
        idx++;
      }
    }
  }

  return idx == 0 ? 0 : 1;
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

void printGraph(TargetGraph *graph) {
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
    free(depItr);
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
    free(depItr);
    printf("\n");
  }
  printf("\n\n");

  free(targetItr);
  free(buildItr);
}

static void rewindAndPerror(FILE *fptr, int pos, int lineNum) {
  fseek(fptr, 0, pos);

  char c;
  fprintf(stderr, "%d: Invalid line: ", lineNum);
  while ( 1 ) {
    c = fgetc(fptr);
    if (c == '\n' || c == EOF) {
      break;
    }
    fprintf(stderr, "%c", c);
  }

  fprintf(stderr, "\n");
  exit(1);
}