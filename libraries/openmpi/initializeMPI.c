#include "initializeMPI.h"

void *waitMessage(void *args){
    char confirmMessage[ALLSIMILIARITY];
    int type = 99;
    memset(confirmMessage, 0, ALLSIMILIARITY);
    MPI_Recv(confirmMessage, ALLSIMILIARITY, MPI_CHAR, currentSlave, type, MPI_COMM_WORLD, &statusGlobal);
    printf("%s\n", confirmMessage);
    strcat(result, confirmMessage);
    strcat(result, "\n\n\n");
    //printf("\n");
}

void initializeMPI(List* listOfTweets){
	/* Inicializa o ambiente de MPI */
	MPI_Init(NULL, NULL);

	/* Pega a quantidade de processos e o ranking */
    char confirmMessage[ALLSIMILIARITY];
    int countProcess, countTweets = listOfTweets -> size;
    int rank, type = 99;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &countProcess);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* Como MPI_Recv é bloqueante precisamos de um jeito de mandar para todos */
    /* É master */
    if(rank == 0){
        /* Se for só um processo eu mesmo tenho que executar */
        if(countProcess == 1){
            ListSimiliarity *listOfSimiliar = indexOfJaccard(listOfTweets);
            printListSimiliarity(listOfSimiliar);
        /* Se for mais de um processo dividido */
        } else {
            char message[SIZESTRING];
            int start = 0, end;
            /* Se for 2 processos signfica que temos 1 sendo o mestre e o 2 segundo escravo */
            if(countProcess == 2){
                end = countTweets - 1;
                sprintf(message, "%d-%d", start, end);
                MPI_Send(message, strlen(message), MPI_CHAR, 1, type, MPI_COMM_WORLD); 
                MPI_Recv(confirmMessage, SIZESTRING, MPI_CHAR, 1, type, MPI_COMM_WORLD, &status);
                printf("%s\n", confirmMessage);
            } else {
                int i, divide = countTweets / (countProcess - 1);
                int rest;
                end = divide - 1;
                //char c;
                for(i = 1; i < countProcess; i++){
                    if((i == countProcess - 1) && ((countProcess - 1) % 2 != 0)){
                        end = countTweets - 1;
                    }
                    memset(message, 0, SIZESTRING);
                    sprintf(message, "%d-%d", start, end);
                    MPI_Send(message, strlen(message), MPI_CHAR, i, type, MPI_COMM_WORLD);
                    //MPI_Recv(confirmMessage, ALLSIMILIARITY, MPI_CHAR, i, type, MPI_COMM_WORLD, &status);
                    //printf("%s\n", confirmMessage);
                    //scanf(" %c", &c);
                    start = end + 1;
                    end = start + divide;
                    end--;
                }

                pthread_t receiveResult[countProcess];
                for(i = 1; i < countProcess; i++){
                    currentSlave = i;
                    statusGlobal = status;
                    pthread_create(&receiveResult[i], NULL, waitMessage, NULL);
                    pthread_join(receiveResult[i], NULL);
                }

            }
        }
    /* É escravo */
    } else {
        char range[SIZESTRING], messageSimiliarity[ALLSIMILIARITY];
        memset(range, 0, SIZESTRING);
        MPI_Recv(range, SIZESTRING, MPI_CHAR, 0, type, MPI_COMM_WORLD, &status); 
        List *slaveTweets = specificTweets(listOfTweets, range);
        ListSimiliarity *listOfSimiliar = indexOfJaccard(slaveTweets);
        memset(messageSimiliarity, 0, ALLSIMILIARITY);
        strcpy(messageSimiliarity, getSimiliarity(listOfSimiliar));
        MPI_Send(messageSimiliarity, strlen(messageSimiliarity), MPI_CHAR, 0, type, MPI_COMM_WORLD);
    }
    
    /* Finaliza o ambiente do MPI */
    MPI_Finalize();
    //printf("%s\n", result);
    char c;
    scanf(" %c", &c);
    printf("%s\n", result);
}