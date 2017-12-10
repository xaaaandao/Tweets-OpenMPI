#ifndef MANIPULATEFILES_H
#define	MANIPULATEFILES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "/home/xandao/Tweets-OpenMPI/libraries/list/manipulateList.h"

void clearScreen();
List *loadTweets(char*);
List *parserJSON(char*);

#endif /* MANIPULATEFILES_H */