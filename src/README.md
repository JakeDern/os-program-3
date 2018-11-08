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

