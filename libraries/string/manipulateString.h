#ifndef MANIPULATESTRING_H
#define	MANIPULATESTRING_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZESTRING 280


bool stringEquals(char*, char*);
void characterBlank(char*);
void removeBreakLine(char*);

void loadWord(char*, char[][SIZESTRING]);
char *filterWordsOfText(char*);
int countWords(char*);
void convertToLower(char*);


#endif /* MANIPULATESTRING_H */