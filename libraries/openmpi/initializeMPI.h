#ifndef INITIALIZEMPI_H
#define	INITIALIZEMPI_H

/**
* Autor: Alexandre Yuji Kajihara
* Descrição: Definimos as bibliotecas utilizadas nas funções, definimos
* algumas variáveis globais e  os protótipos das funções para que outras 
* funções possam invocar funções dessa biblioteca.
* Data de criaçãoo: 11/12/2017
* Data de atualização: 11/12/2017
**/

/* Incluíndo algumas bibliotecas */
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <mpi.h>
#include "/home/xandao/cloud/Tweets-OpenMPI/libraries/jaccard/jaccard.h"

/* Variáveis globais */
int currentSlave;
static int allSlaveAnswers;
MPI_Status statusGlobal;
char result[ALLSIMILIARITY];

/* Protótipos de funções */
void *waitMessage(void*);
void initializeMPI(List*);

#endif /* INITIALIZEMPI_H */