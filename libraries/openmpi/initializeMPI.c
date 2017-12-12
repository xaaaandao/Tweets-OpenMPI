#include "initializeMPI.h"

/**
* Autor: Alexandre Yuji Kajihara
* Descrição: Definimos as funções e implementamos elas para que possa
* ser feito distribuído a tarefa entre o mestre e escravos, de acordo 
* com a quantidade de escravos.
* Data de criaçãoo: 11/12/2017
* Data de atualização: 11/12/2017
**/

/**
* A função waitMessage(void *args) é uma thread que fica esperando uma mensagem enviada
* pelo escravo com a resposta dos tweets similiares.
* @param *args, é um parâmetro do tipo void, sem utilização.
* @return é void não retorna nada.
*/
void *waitMessage(void *args){
    char confirmMessage[ALLSIMILIARITY];
    char numberOfSlave[SIZESTRING];
    int type = 99;
    memset(numberOfSlave, 0, SIZESTRING);
    memset(confirmMessage, 0, ALLSIMILIARITY);
    
    /* Fico aguardando a resposta */
    MPI_Recv(confirmMessage, ALLSIMILIARITY, MPI_CHAR, currentSlave, type, MPI_COMM_WORLD, &statusGlobal);

    /* Adiciona em uma string */
    strcat(result, confirmMessage);
    allSlaveAnswers++;
}

/**
* A função initializeMPI(List* listOfTweets) recebe uma lista de tweets, com todos os tweets
* presentes no arquivo passado por parâmetro ou gerado durante a execução. Verifica se o processo 
* é mestre ou escravo, se for escravo verifica quantos escravos terão se tiver somente o mestre
* ele mesmo executa, se tiver dois processos significa que teremos um mestre e um escravo então
* mando para o único escravo. Se tiver mais de dois processo significa que eu irei dividir
* igualmente se a quantidade escravos for par, e se for ímpar iremos todos escravos irão
* executar a mesma quantidade com exceção do último escravo que irá trabalhar um pouco mais.
* Depois de designar o intervalo de cada escravo, o mestre fica ouvindo esperando a resposta.
* Já o escravo recebe uma mensagem do mestre, aplica o índice de Jaccard e depois envia o resultado 
* para o mestre. Quando todos escravos responderam é impresso todos tweets similiares.
* @param listOfTweets, é uma lista de tweets, com todos os tweets presentes no arquivo que foi passado
* por parâmetro quando rodamos o programa ou que foi gerado no nosso programa.
* @return é void não retorna nada.
*/
void initializeMPI(List* listOfTweets){
    /* Utilizada para verificar se todos os escravos já responderam */
    allSlaveAnswers = 0;
    isDone = false;

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
            strcpy(result, getSimiliarity(listOfSimiliar));
            isDone = true;
        /* Se for mais de um processo dividido */
        } else {
            char message[SIZESTRING];
            int start = 0, end;
            /* Se for 2 processos signfica que temos 1 sendo o mestre e o 2 segundo escravo */
            if(countProcess == 2){
                end = countTweets - 1;
                sprintf(message, "%d-%d", start, end);
                MPI_Send(message, strlen(message), MPI_CHAR, 1, type, MPI_COMM_WORLD); 
                MPI_Recv(confirmMessage, ALLSIMILIARITY, MPI_CHAR, 1, type, MPI_COMM_WORLD, &status);
                strcpy(result, confirmMessage);                
                isDone = true;
            } else {
                /* Se for mais de um processo */
                int i, divide = countTweets / (countProcess - 1);
                int rest;
                end = divide - 1;
                /* Divido a quantidade tweets para cada um dos processo, e passo o intervalo
                * de tweets que o escravo deve verificar qual é a similiaridade.
                */
                for(i = 1; i < countProcess; i++){
                    if((i == countProcess - 1) && ((countProcess - 1) % 2 != 0)){
                        end = countTweets - 1;
                    }
                    memset(message, 0, SIZESTRING);
                    sprintf(message, "%d-%d", start, end);
                    MPI_Send(message, strlen(message), MPI_CHAR, i, type, MPI_COMM_WORLD);
                    start = end + 1;
                    end = start + divide;
                    end--;
                }

                /* Inicializo threads para o mestre esperar a resposta dos escravos */
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

        /* Recebe uma mensagem do mestre */
        MPI_Recv(range, SIZESTRING, MPI_CHAR, 0, type, MPI_COMM_WORLD, &status); 
        
        /* Aplica o índice de Jaccard*/
        List *slaveTweets = specificTweets(listOfTweets, range);
        ListSimiliarity *listOfSimiliar = indexOfJaccard(slaveTweets);
        memset(messageSimiliarity, 0, ALLSIMILIARITY);
        strcpy(messageSimiliarity, getSimiliarity(listOfSimiliar));
        
        /* Envia a resposta para o mestre com todos os tweets que foram encontrados que são similiares */
        MPI_Send(messageSimiliarity, strlen(messageSimiliarity), MPI_CHAR, 0, type, MPI_COMM_WORLD);
    }
    
    /* Finaliza o ambiente do MPI */
    MPI_Finalize();
 
    /* Verifico se todos os escravos responderam */
    if((allSlaveAnswers == countProcess - 1) || isDone){
        if(generateOutput(listOfTweets, result)){
            printf(ANSI_COLOR_GREEN "Arquivo de saída gerado com sucesso! (arquivo: output.txt)\n" ANSI_COLOR_RESET);   
        }
    }
}