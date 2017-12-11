#ifndef MANIPULATESTRING_H
#define	MANIPULATESTRING_H

/**
* Autor: Alexandre Yuji Kajihara
* Descrição: Definimos as bibliotecas utilizadas nas funções, definimos um 
* valor e os protótipos das funções para que outras funções possam invocar 
* funções dessa biblioteca.
* Data de criaçãoo: 11/12/2017
* Data de atualização: 11/12/2017
**/

/* Incluíndo algumas bibliotecas */
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

/* Protótipos de funções */
bool stringEquals(char*, char*);
void characterBlank(char*);
void removeBreakLine(char*);
void loadWord(char*, char[][SIZESTRING]);
char *filterWordsOfText(char*);
int countWords(char*);
void convertToLower(char*);


#endif /* MANIPULATESTRING_H */