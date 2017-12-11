#ifndef JACCARD_H
#define	JACCARD_H

/**
* Autor: Alexandre Yuji Kajihara
* Descrição: Definimos as bibliotecas utilizadas nas funções e os protótipos 
* das funções para que outras funções possam invocar funções dessa biblioteca.
* Data de criaçãoo: 11/12/2017
* Data de atualização: 11/12/2017
**/

/* Incluíndo algumas bibliotecas */
#include "/home/xandao/cloud/Tweets-OpenMPI/libraries/string/manipulateString.h"
#include "/home/xandao/cloud/Tweets-OpenMPI/libraries/list/manipulateList.h"
#include "/home/xandao/cloud/Tweets-OpenMPI/libraries/files/manipulateFiles.h"

/* Protótipos de funções */
bool wordIsIntersection(char[][SIZESTRING], char*, int);
int countIntersectionTweets(char*, char*);
ListSimiliarity *indexOfJaccard(List*);

#endif /* JACCARD_H */