# os-program-3
os-program-3: Write the make command

# Overview
This program implements the core functionality of the make program. It has one optional command line argument "-f" which allows a user to specify the name of a makefile beyond just "makefile" or "Makefile".

# Usage
```
$ ./537make | -f <makefile name> | <target name>
```

# Architecture
This program is made up of 3 core modules and a couple of types. These types include a Linked List (which also contains stack methods), a Graph, and "Targets" which represent both nodes in the graph and Build Targets as you would think about them in the context of make.

1. FileChecker - This module is responsible for checking files for existence and comparing ages of said files

2. FileParser - This module is largely the backbone of the program, doing much of the heavy lifting by parsing the file, checking for any formatting errors, and constructing the graph whilst doing so.

3. ProgramBuilder - This module is responsible for identifying the correct target to build, performing cycle detection, and executing recipes for all out of date targets in the proper order

# Valgrind
The output from our valgrind originally displayed several errors, due to various things such as uninitialized values. It is now down to a single error indicating a memory leak. This leak is simply just the contents of the dependency graph before the program exits, and thus does not need to be freed and is not problematic. A summary of the other changes made to the program are listed below: 

1. Main.c, line 69: Failed to check return value of malloc and exit on failure.

Code before: 
```
CommandParse *cmd = malloc(sizeof(CommandParse));
```

Code after:
```
CommandParse *cmd;
if ((cmd = malloc(sizeof(CommandParse))) == NULL) {
  fprintf(stderr, "Unable to allocate heap memory\n");
  exit(1);
}
```
2. Main.c, lines 76, 98, and 115: Failed to free memory before exit

Code before: 
```
if (argc > 4) {
    fprintf(stderr, "Usage error: too many command arguments\n");
    exit(1);
}
```
```
fprintf(stderr, "Usage error: too many command arguemnts\n");
exit(1);
```
```
fprintf(stderr, "Usage error: -f must be accompanied by a makefile name\n");
exit(1);
```

Code after:
```
if (argc > 4) {
    fprintf(stderr, "Usage error: too many command arguments\n");
    free(cmd);
    exit(1);
}
```
```
fprintf(stderr, "Usage error: too many command arguemnts\n");
free(cmd);
exit(1);
```
```
fprintf(stderr, "Usage error: -f must be accompanied by a makefile name\n");
free(cmd);
exit(1);
```

3. main.c, line 70: Jump based on uninitialized value

Code before:
```
if ( (cmd = malloc(sizeof(CommandParse))) == NULL) {
    fprintf(stderr, "Unable to allocate heap memory\n");
    exit(1);
  }
```

Code after:
```
if ( (cmd = malloc(sizeof(CommandParse))) == NULL) {
    fprintf(stderr, "Unable to allocate heap memory\n");
    exit(1);
  }
cmd->fflag = 0;
```

4. main.c, lines 75, 76: Jump based on uninitialized value. Fixed by adding the following lines
Additions:
```
cmd->buildTarget = NULL;
cmd->makeFile = NULL;
```

5. ProgramBuilder.c, line 83: Unfreed struct.

Code before: 
```
if (pid != 0) {
  fprintf(stderr, "failed to execute recipe for target \"%s\"\n", t->name);
  exit(1);
}
```

Code after:
```
if (pid != 0) {
  fprintf(stderr, "failed to execute recipe for target \"%s\"\n", t->name);
	free(iterator);
  exit(1);
}
```

6. Graph.c, lines 80-91: Unfreed LinkedList.

Code before:
```
 Target *next = getNext(iterator);
    if (hasCycleHelper(next, l)) {
      free(iterator);
      return 1;
    }
  }
  return 0;  
}
```

Code after:
```
 Target *next = getNext(iterator);
    if (hasCycleHelper(next, l)) {
      free(iterator);
      pop(l);
      freeList(l);
      return 1;
    }
  }
   pop(l);
  free(iterator);
  freeList(l);
  return 0;  
}
```