#include "jaccard.h"

bool wordIsIntersection(char array[][SIZESTRING], char *word, int size){
	int i = 0;
	/* Verifica se a palavra está no vetor de String */
	while(i < size){
		if(stringEquals(array[i], word)){
			return true;
		}
		i++;
	}
	return false;
}

int countIntersectionTweets(char *firstTweet, char *secondTweet){
	/* Faz uma cópia para poder alterar */
	char firstTweetAuxiliar[SIZESTRING], secondTweetAuxiliar[SIZESTRING];
	strcpy(firstTweetAuxiliar, firstTweet);
	strcpy(secondTweetAuxiliar, secondTweet);
	
	/* Conta a quantidade de palavras presentes no twitter */
	int numberOfWordsFirst = countWords(firstTweetAuxiliar);
	int numberOfWordsSecond = countWords(secondTweetAuxiliar);
	int i, j, k = 0, countIntersection = 0;
	
	/* Aloca cada palavra em um vetor de String */
	char wordsFirstTweet[numberOfWordsFirst][SIZESTRING];
	char wordsSecondTweet[numberOfWordsSecond][SIZESTRING];
	char result[SIZESTRING][SIZESTRING];

	/* Coloca cada palavra em um vetor de String */
	loadWord(firstTweet, wordsFirstTweet);
	loadWord(secondTweet, wordsSecondTweet);

	/* Compara os dois vetores de String */
	for(i = 0; i < numberOfWordsFirst; i++){
		for(j = 0; j < numberOfWordsSecond; j++){
			if((stringEquals(wordsFirstTweet[i], wordsSecondTweet[j])) && (strlen(wordsFirstTweet[i]) == strlen(wordsSecondTweet[j]))){
				/* Se as duas palavras são iguais verifico se o vetor de String está vazio se sim só adiciono */
				if(k == 0){
					strcpy(result[k], wordsFirstTweet[i]);
					countIntersection++;
					k++;
				/* Se o vetor de String já está preenchido verifico se aquele valor já está presente, se já não adiciono, caso contrário sim */
				} else {
					if(!wordIsIntersection(result, wordsFirstTweet[i], k)){
						strcpy(result[k], wordsFirstTweet[i]);
						countIntersection++;
						k++;
					}
				}
			}
		}
	}						

	return countIntersection;
}

ListSimiliarity *indexOfJaccard(List* listOfTweets){
	ListSimiliarity* listOfSimiliar = (ListSimiliarity*) malloc (sizeof(ListSimiliarity*));
	Node *nodeFirst, *nodeSecond;
	char firstTweetAuxiliar[SIZESTRING], secondTweetAuxiliar[SIZESTRING];
	
	initializeListSimiliarity(listOfSimiliar);

	/* Percorremos a lista */
	nodeFirst = listOfTweets -> first;
	while (nodeFirst != NULL){ 
		
		/* Percorremos a lista */
		nodeSecond = listOfTweets -> first;
		while(nodeSecond != NULL){

			/* Ou seja, as string não são iguais */
			if(strcmp(nodeFirst -> cleanTweet, nodeSecond -> cleanTweet) > 0 || strcmp(nodeFirst -> cleanTweet, nodeSecond -> cleanTweet) < 0){
				clearScreen();
				printf(ANSI_COLOR_GREEN "Tweets na lista\n" ANSI_COLOR_RESET);
				printf(ANSI_COLOR_GREEN "Aplicando Índice de Jaccard (t1:%d-t2:%d/t:%d)\n" ANSI_COLOR_RESET, nodeFirst -> id, nodeSecond -> id, listOfTweets -> size);
				printf(ANSI_COLOR_GREEN "Contando as intersecções dos dois tweets\n" ANSI_COLOR_RESET);
				/* Necessário ter uma cópia devido que se você passa o ponteiro ele altera lá na memória e não conta certo */
				strcpy(firstTweetAuxiliar, nodeFirst -> cleanTweet);
				strcpy(secondTweetAuxiliar, nodeSecond -> cleanTweet);
				int intersectionTweets = countIntersectionTweets(firstTweetAuxiliar, secondTweetAuxiliar);
				
				/* Necessário ter uma cópia devido que se você passa o ponteiro ele altera lá na memória e não conta certo */
				printf(ANSI_COLOR_GREEN "Contando as uniões dos dois tweets\n" ANSI_COLOR_RESET);
				int unionTweets = nodeFirst -> countWordCleanTweet + nodeSecond -> countWordCleanTweet;

				double similiarity = (double)intersectionTweets / (double)unionTweets;
				if(similiarity > 0.3){
					printf(ANSI_COLOR_GREEN "É similiar\n" ANSI_COLOR_RESET);			
					/*printf("intersectionTweets: %d\n", intersectionTweets);
					printf("unionTweets: %d\n", unionTweets);
					printf("similiarity %.2f\n", similiarity);
					printf("f: %s\n", nodeFirst -> cleanTweet);
					printf("s: %s\n\n", nodeSecond -> cleanTweet);*/
					insertTweetListSimiliarity(listOfSimiliar, nodeFirst -> id, nodeFirst -> originalTweet, nodeSecond -> id, nodeSecond -> originalTweet, intersectionTweets, unionTweets, similiarity);
				}
			}
			
			nodeSecond = nodeSecond -> next;
		}

		nodeFirst = nodeFirst -> next;
	}

	return listOfSimiliar;
}