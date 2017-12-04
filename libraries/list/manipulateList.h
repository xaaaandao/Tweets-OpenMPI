#ifndef MANIPULATELIST_H
#define	MANIPULATELIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define SIZESTRING 3276

typedef struct node{
	char tweet[SIZESTRING];
	struct node *next;
}Node;

typedef struct{
	Node *first, *last;
	int size;
}List;

void cleanList(List*);
void initializeList(List*);
bool emptyList(List*);
void insertTweetList(List*, char*);
int sizeList(List*);
void printList(List*);

#endif /* MANIPULATELIST_H */