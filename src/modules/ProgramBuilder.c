#include "../interfaces/ProgramBuilder.h"
#include "../interfaces/FileChecker.h"
#include "../types/graph/Graph.h"
#include "../types/linked_list/LinkedList.h"
#include "../types/linked_list/ListIterator.h"
#include "../types/target/Target.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static int buildProgramHelper(Target *t);
static int needsRebuilding(Target *t);
static int buildTarget(Target *t);

int buildProgram(Target *t) {
    if (hasCycle(t)) {
        exit(1);
    }
    buildProgramHelper(t);

    return 1;
}

static int buildProgramHelper(Target *t) {
    ListIterator *iterator = newListIterator(t->dependencies);

    while (hasNext(iterator)) {
        buildProgramHelper(getNext(iterator));
    }

    if (needsRebuilding(t)) {
        buildTarget(t);
    }

    free(iterator);
    return 1;
}

static int needsRebuilding(Target *t) {
    ListIterator *iterator = newListIterator(t->dependencies);

    while (hasNext(iterator)) {
        if (fileIsOlder(t->name, ((Target*)getNext(iterator))->name)) {
            free(iterator);
            return 1;
        }
    }
    free(iterator);
    return 0;
}

static int buildTarget(Target *t) {
    pid_t pid = fork();
    if (pid) {
        int exitVal = wait(&pid);
        if (exitVal) {
            fprintf(stderr, "failed to execute recipe for target \"%s\"", t->name);
            exit(1);
        }
    } else {
        ListIterator *iterator = newListIterator(t->recipes);
        while (hasNext(iterator)) {
            char **curr = (char**)getNext(iterator);
            if (execvp(curr[0], curr)) {
                printf("bad\n");
                exit(1);
            }
        }
    }

    return 0;
}