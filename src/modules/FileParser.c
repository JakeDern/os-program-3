#include <stdio.h>
#include <stdlib.h>

#include "../interfaces/FileParser.h"
#include "../types/target/Target.h"

const int MAX_NAME_LENGTH = 200;
const int MAX_LINE_LENGTH = 10000;

static int nextLine(char *buff, int max, FILE *fptr, int lineCount);
static Target *readTarget(char* line, int lineLength, TargetGraph *g, int lineCount);
static char *readRecipe(char* line, int lineLength, int lineCount);
static void flushToEndOfLine(FILE *fptr);

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
        //TODO verify line is blank;
        break;
      }
      default: {
        currTarget = readTarget(readBuff, lineLength, graph, lineCnt);
      }
    }
    lineCnt++;
  }

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
  // validate target name
  char c;
  int len = 0;
  int done = 0;
  int err = 0;
  int idx = 0;
  while (!done && !err) {
    c = line[idx];
    idx++;
    len++;
    switch ( c ) {
      // TODO invesitage valid chars for targets
      case '\t':
      case '#':
      case '\n':
      case ' ': {
        err = 1;
        break;
      }
      case ':': {
        done = 1;
      }
    }
  }

  if (err) {
    fprintf(stderr, "Invalid target on line %d\n", lineCount);
    exit(1);
  }

  // read the target name
  char *tName = malloc(len);
  for (int i = 0; i < len - 1; i++) {
    tName[i] = line[i];
  }
  tName[len] = '\0';

  printf("tname: %s\n", tName);

  // fetch target if already exists
  Target *t;
  if ( (t = findBuildTarget(g, tName)) == NULL ) {
    if ( (t = findTarget(g, tName)) == NULL ) {
      t = newTarget(tName);
      addTarget(g, t);
      addBuildTarget(g, t);
    }
  } else {
    fprintf(stderr, "duplicate target %s found on line %d\n", tName, lineCount);
  }
  
  // read rest of line to get all dependencies
  while (idx < lineLength) {
    // iterate through any whitespace
    c = line[idx];
    while ( c == ' ' || c == '\t' && idx < lineLength) {
      idx++;
      c = line[idx];
    }

    // read next token
    int depLen = 0;
    int depStart = idx;
    int depErr = 0;
    while (!depErr) {
      c = line[idx];
      break;
    }
    break;
  }
  return t;
}

// char *getNextToken(char *buff, int start, int end) {
//   int idx = start;
//   char c = buff[start];
//   while ( isWhiteSpace(c) && idx <= end) {
//     idx++;
//     c = buff[idx];
//   }

//   if (idx > end) {
//     return NULL;
//   }

//   int len = 0;
//   int tokStart = idx;
//   while ( idx <= end  && !isWhiteSpace(buff[idx])) {
//     idx++;
//     len++;
//   }

//   char* buff = malloc(len + 1);
//   while ( tokStart < idx ) {

//   }
  
// }

// int isValidDepChar(char c) {
//   switch(c) {
//     case ':':
//     case '#': {
//       return 0;
//     }
//     default: {
//       return 1;
//     }
//   }
// }

int isWhiteSpace(char c) {
  switch(c) {
    case '\t':
    case ' ': {
      return 1;
    }
    default: {
      return 0; 
    }
  }
}

static char *readRecipe(char* line, int lineLength, int lineCount) {
  return NULL;
}

static void flushToEndOfLine(FILE *fptr) {
  while (fgetc(fptr) != EOF && fgetc(fptr) != '\n'){}
}