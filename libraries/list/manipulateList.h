#ifndef MANIPULATELIST_H
#define	MANIPULATELIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "/home/xandao/cloud/Tweets-OpenMPI/libraries/string/manipulateString.h"

#define ALLSIMILIARITY 1000000
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct node{
	int id;
	char originalTweet[SIZESTRING];
	char cleanTweet[SIZESTRING];
	int countWordOriginalTweet;
	int countWordCleanTweet;
	struct node *next;
}Node;

typedef struct{
	Node *first, *last;
	int size;
}List;

List *specificTweets(List*, char*);
void cleanList(List*);
void initializeList(List*);
bool emptyList(List*);
void insertTweetList(List*, char*);
void insertTweetCompleteList(List*, int, char*, char*, int, int);
int sizeList(List*);
void printList(List*);

typedef struct nodeSimiliarity{
	int firstId;
	char firstTweet[SIZESTRING];
	int secondId;
	char secondTweet[SIZESTRING];
	int valueIntersection;
	int valueUnion;
	int valueSimiliarity;
	struct nodeSimiliarity *next;
}NodeSimiliarity;

typedef struct{
	NodeSimiliarity *first, *last;
	int size;
}ListSimiliarity;

void cleanListSimiliarity(ListSimiliarity*);
void initializeListSimiliarity(ListSimiliarity*);
bool emptyListSimiliarity(ListSimiliarity*);
void insertTweetListSimiliarity(ListSimiliarity*, int, char*, int, char*, int, int, int);
int sizeListSimiliarity(ListSimiliarity*);
void printListSimiliarity(ListSimiliarity*);
char *getSimiliarity(ListSimiliarity*);

#endif /* MANIPULATELIST_H */