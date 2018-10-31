#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../interfaces/FileChecker.h"

// int main(int argc, char**argv){
//     return 0;
// }

/** @override */
int fileIsOlder(char *file1, char *file2) {
    struct stat *f1Stat = malloc(sizeof(struct stat));
    struct stat *f2Stat = malloc(sizeof(struct stat));

    if (stat(file1, f1Stat)) {
        fprintf(stderr, "Failed to find file at location %s\n", file1);
        exit(1);
    }

    if (stat(file2, f2Stat)) {
        fprintf(stderr, "Failed to find file at location %s\n", file1);
        exit(1);
    }

    if (f1Stat->st_mtime < f2Stat->st_mtime) {
        free(f1Stat);
        free(f2Stat);
        return 1;
    }
    free(f1Stat);
    free(f2Stat);
    return 0;
}