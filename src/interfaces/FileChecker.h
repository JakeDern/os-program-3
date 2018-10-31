#ifndef _FILECHECKER
#define _FILECHECKER

/*
* fileIsOlder determines whether input file2 has been modified more
* recently than input file1
*
*@param file1, file2 are file paths relative to the execution of the program
*@return 1 for file1 being less recently modified, 0 for equal time or file 2 being less recent
* */
extern int fileIsOlder(char *file1, char *file2);




#endif