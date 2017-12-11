#ifndef INITIALIZEMPI_H
#define	INITIALIZEMPI_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <mpi.h>
#include "/home/xandao/cloud/Tweets-OpenMPI/libraries/jaccard/jaccard.h"

int currentSlave;
static int allSlaveAnswers;
MPI_Status statusGlobal;
char result[ALLSIMILIARITY];

void initializeMPI(List*);


#endif /* INITIALIZEMPI_H */