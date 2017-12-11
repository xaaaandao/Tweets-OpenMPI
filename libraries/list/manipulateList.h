#ifndef MANIPULATELIST_H
#define	MANIPULATELIST_H

/**
* Autor: Alexandre Yuji Kajihara
* Descrição: Definimos as bibliotecas utilizadas nas funções, definimos alguns
* valores, a estrutura de lista e  os protótipos das funções para que outras 
* funções possam invocar funções dessa biblioteca.
* Data de criaçãoo: 11/12/2017
* Data de atualização: 11/12/2017
**/

/* Incluíndo algumas bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "/home/xandao/cloud/Tweets-OpenMPI/libraries/string/manipulateString.h"

/* Definindo alguns valores */
#define ALLSIMILIARITY 1000000
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

/* Definindo a estrutura de lista */
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

/* Protótipos de funções */
List *specificTweets(List*, char*);
void cleanList(List*);
void initializeList(List*);
bool emptyList(List*);
void insertTweetList(List*, char*);
void insertTweetCompleteList(List*, int, char*, char*, int, int);
int sizeList(List*);
void printList(List*);

/* Definindo a estrutura de lista */
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

/* Protótipos de funções */
void cleanListSimiliarity(ListSimiliarity*);
void initializeListSimiliarity(ListSimiliarity*);
bool emptyListSimiliarity(ListSimiliarity*);
void insertTweetListSimiliarity(ListSimiliarity*, int, char*, int, char*, int, int, int);
int sizeListSimiliarity(ListSimiliarity*);
void printListSimiliarity(ListSimiliarity*);
char *getSimiliarity(ListSimiliarity*);
bool existSimiliar(ListSimiliarity*, int, int);

#endif /* MANIPULATELIST_H */