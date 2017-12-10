#include "initializeMPI.h"

bool partitionEqual(int countTweets, int countProcess){
    if(countTweets % countProcess == 0)
        return true;
    return false;
}

void initializeMPI(int countTweets){
	/* Inicializa o ambiente de MPI */
	MPI_Init(NULL, NULL);

	/* Pega a quantidade de processos e o ranking */
    int countProcess, rank, type = 99;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &countProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* É master */
    if(rank == 0){
        printf("sou mestre\n");
        /**
        1 - Se só tem um processo, então sou eu mesmo o mestre que vai ter que executar
        2 - Se tem mais de um processo, divido em parte iguais;
        3 - Envio a mensagem qual range eu quero que o escravo processe;
        4 - O escravo recebe processa e depois disso retorna ao pai falando quais são similiares
        5 - O pai recebe a mensagem;
        */
        /* Se for só um processo eu mesmo tenho que executar */
        if(countProcess == 1){

        /* Se for mais de um processo dividido */
        } else {
            char message[SIZESTRING];
            char confirmMessage[SIZESTRING];
            int start = 0, end;
            /* Se for 2 processos signfica que temos 1 sendo o mestre e o 2 segundo escravo */
            if(countProcess == 2){
                end = countTweets - 1;
                sprintf(message, "%d-%d", start, end);
                printf("message: %s\n", message);
                MPI_Send(message, strlen(message), MPI_CHAR, 1, type, MPI_COMM_WORLD); 
                MPI_Recv(confirmMessage, SIZESTRING, MPI_CHAR, 1, type, MPI_COMM_WORLD, &status);
            } else {
                int i, divide = countTweets / (countProcess - 1);
                int rest;
                end = divide - 1;
                for(i = 1; i < countProcess; i++){
                    if((i == countProcess - 1) && ((countProcess - 1) % 2 != 0)){
                        end = countTweets - 1;
                    }
                    printf("%d-%d\n", start, end);
                    start = end + 1;
                    end = start + divide;
                    end--;
                }
            }
            /*int i, divide = countTweets / (countProcess - 1);
            int start = 0, end;
            bool messageEqual = partitionEqual(countTweets, countProcess);
            for (i = 1; i < countProcess; i++){
                if(!messageEqual){
                    if(i == countProcess - 1){
                        end = (divide * i) - countTweets;
                    }
                    printf("%d - %d\n", start, end);
                    start = end + 1;
                    end = end + divide;
                } else {
                    printf("%d - %d\n", start, end);
                    start = end + 1;
                    end = end + divide;
                }
            }*/
        }
        /*int i, divide = countTweets / (countProcess - 1);
        int start = 0, end;
        bool messageEqual = partitionEqual(countTweets, countProcess);
        for (i = 1; i < countProcess; i++){
            if(!messageEqual){
                if(i == countProcess - 1){
                    end = (divide * i) - countTweets;
                }
                printf("%d - %d\n", start, end);
                start = end + 1;
                end = end + divide;
            } else {
                printf("%d - %d\n", start, end);
                start = end + 1;
                end = end + divide;
            }
        }*/
    /* É escravo */
    } else {
        printf("sou escravo\n");
    }
    
    /* Finaliza o ambiente do MPI */
    MPI_Finalize();

}