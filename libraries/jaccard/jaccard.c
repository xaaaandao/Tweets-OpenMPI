#include "jaccard.h"

bool wordIsIntersection(char array[][SIZESTRING], char *word, int size){
	int i = 0;
	while(i < size){
		if(stringEquals(array[i], word)){
			return true;
		}
		i++;
	}
	return false;
}

int countIntersectionTweets(char *firstTweet, char *secondTweet){
	char firstTweetAuxiliar[SIZESTRING], secondTweetAuxiliar[SIZESTRING];
	strcpy(firstTweetAuxiliar, firstTweet);
	strcpy(secondTweetAuxiliar, secondTweet);
	
	int numberOfWordsFirst = countWords(firstTweetAuxiliar);
	int numberOfWordsSecond = countWords(secondTweetAuxiliar);
	int i, j, k = 0, countIntersection = 0;
	
	char wordsFirstTweet[numberOfWordsFirst][SIZESTRING];
	char wordsSecondTweet[numberOfWordsSecond][SIZESTRING];
	char result[SIZESTRING][SIZESTRING];

	loadWord(firstTweet, wordsFirstTweet);
	loadWord(secondTweet, wordsSecondTweet);

	for(i = 0; i < numberOfWordsFirst; i++){
		for(j = 0; j < numberOfWordsSecond; j++){
			if((stringEquals(wordsFirstTweet[i], wordsSecondTweet[j])) && (strlen(wordsFirstTweet[i]) == strlen(wordsSecondTweet[j]))){
				if(k == 0){
					strcpy(result[k], wordsFirstTweet[i]);
					countIntersection++;
					k++;
				} else {
					if(wordIsIntersection(result, wordsFirstTweet[i], k) == false){
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

List *indexOfJaccard(List* listOfTweets, char *nameFile){
	int countLinesOfFileOriginal = countLinesOfFile(nameFile);
	
	/* Se a quantidade de linhas do arquivo só com tweets for diferente das linhas do arquivo original ERRO! */
	if(countLinesOfFile("teste.txt") != countLinesOfFileOriginal){
		return NULL;

	/* Caso contrário é igual atualiza o tamanho da lista */
	/* Observação: não sabemos porque, mas o valor da lista tava valores diferentes */
	} else {
		listOfTweets -> size = countLinesOfFileOriginal;
	}

	List* listSimiliar = (List*) malloc (sizeof(List*));
	Node *nodeFirst, *nodeSecond;
	char firstTweetAuxiliar[SIZESTRING], secondTweetAuxiliar[SIZESTRING];
	double maxSimiliarity = 0;

	/* Percorremos a lista */
	nodeFirst = listOfTweets -> first;
	while (nodeFirst != NULL){ 
		
		/* Percorremos a lista */
		nodeSecond = listOfTweets -> first;
		while(nodeSecond != NULL){

			/* Ou seja, as string não são iguais */
			if(strcmp(nodeFirst -> cleanTweet, nodeSecond -> cleanTweet) > 0 || strcmp(nodeFirst -> cleanTweet, nodeSecond -> cleanTweet) < 0){
				/* Necessário ter uma cópia devido que se você passa o ponteiro ele altera lá na memória e não conta certo */
				strcpy(firstTweetAuxiliar, nodeFirst -> cleanTweet);
				strcpy(secondTweetAuxiliar, nodeSecond -> cleanTweet);
				int intersectionTweets = countIntersectionTweets(firstTweetAuxiliar, secondTweetAuxiliar);
				
				/* Necessário ter uma cópia devido que se você passa o ponteiro ele altera lá na memória e não conta certo */
				int unionTweets = nodeFirst -> countWordCleanTweet + nodeSecond -> countWordCleanTweet;

				double similiarity = (double)intersectionTweets / (double)unionTweets;
				//printf("similiarity: %.2f\n", similiarity);
				if(similiarity > maxSimiliarity){
					maxSimiliarity = similiarity;
				}

				if(similiarity > 0.3){
					printf("intersectionTweets: %d\n", intersectionTweets);
					printf("unionTweets: %d\n", unionTweets);
					printf("similiarity %.2f\n", similiarity);
					printf("f: %s\n", nodeFirst -> cleanTweet);
					printf("s: %s\n\n", nodeSecond -> cleanTweet);
				}
			}
			
			nodeSecond = nodeSecond -> next;
		}

		nodeFirst = nodeFirst -> next;
	}
	printf("max: %.2f\n", maxSimiliarity);

	return listSimiliar;
}