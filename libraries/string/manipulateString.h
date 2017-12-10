#ifndef MANIPULATESTRING_H
#define	MANIPULATESTRING_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* O tamanho não pode ser 140 ou 280, que é o quanto é aceito no 
* Twitter devido que por exemplo, caracteres em japonês 
* irá faltar se utilizar 140 ou 280, por isso o tamanho do 1000
*/
#define SIZESTRING 1000

bool stringEquals(char*, char*);
void characterBlank(char*);
void removeBreakLine(char*);

void loadWord(char*, char[][SIZESTRING]);
char *filterWordsOfText(char*);
int countWords(char*);
void convertToLower(char*);


#endif /* MANIPULATESTRING_H */