#ifndef MANIPULATEFILES_H
#define	MANIPULATEFILES_H

/**
* Autor: Alexandre Yuji Kajihara
* Descrição: Definimos as bibliotecas utilizadas nas funções e os protótipos 
* das funções para que outras funções possam invocar funções dessa biblioteca.
* Data de criaçãoo: 11/12/2017
* Data de atualização: 11/12/2017
**/

/* Incluíndo algumas bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "/home/xandao/cloud/Tweets-OpenMPI/libraries/jaccard/jaccard.h"
#include "/home/xandao/cloud/Tweets-OpenMPI/libraries/list/manipulateList.h"

/* Protótipos de funções */
void clearScreen();
List *loadTweets(char*);
List *parserJSON(char*);
bool generateOutput(List*, char*);

#endif /* MANIPULATEFILES_H */