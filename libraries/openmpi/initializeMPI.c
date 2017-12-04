#include "initializeMPI.h"

void initializeMPI(){
	/* Inicializa o ambiente de MPI */
	MPI_Init(NULL, NULL);

	/* Pega a quantidade de processos */
    int countProcess;
    MPI_Comm_size(MPI_COMM_WORLD, &countProcess);

    /* É master */
    if(countProcess == 0){

    }
    /* É escravo */
	else if(countProcess > 0){

    }
    
    /* Finaliza o ambiente do MPI */
    MPI_Finalize();

}