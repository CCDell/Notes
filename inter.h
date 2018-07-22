#ifndef NOTES_INTER
#define NOTES_INTER

#define throw(str) {fprintf(stderr, "%s\n", str); exit(1);}
#define NOTES_FILENAME "/home/noah/Desktop/notes"
#define NOTES_MAXSTR 500
#define NOTES_INFO_LEN 3

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void getPromptStr(const char * prompt, const char * prompts[], const int,char * args[], int, char*);
short inStrArray(const char *[], char *, int );

#endif  

