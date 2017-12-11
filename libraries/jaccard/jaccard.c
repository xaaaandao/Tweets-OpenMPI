#include "jaccard.h"

/**
* A função wordIsIntersection(char array[][SIZESTRING], char *word, int size)
* recebe um vetor de string, uma string e o tamanho desse vetor, percorre se
* todo o vetor verificando se existe a palavra nesse vetor, se existir
* retorna true que significa que não pode ser adicionado no conjunto de intersecção
* caso não tenha retorna false, que pode ser adicionado.
* @param array[][SIZESTRING], é um vetor de string com todas as palavras presente em um tweet.
* @param word, é uma string que irá ser verificada a presença dela no vetor de string.
* @param size, é um inteiro com o tamanho do vetor de string. 
* @return true ou false, true caso já esteja no vetor de string, false caso não esteja.
*/
bool wordIsIntersection(char array[][SIZESTRING], char *word, int size){
	int i = 0;
	/* Verifica se a palavra está no vetor de String */
	while(i < size){
		/* Verifica se a palavra está presente no vetor */
		if(stringEquals(array[i], word)){
			return true;
		}
		i++;
	}
	return false;
}

/**
* A função countIntersectionTweets(char *firstTweet, char *secondTweet)
* recebe duas strings, que são dois tweets. Verifica quais palavras estão presente nas
* duas string, sempre é verificado se a palavra já não está presente no conjunto de 
* intersecção, por fim retorna a quantidade de palavras presentes no conjunto de intersecção.
* @param firstTweet, é uma string que é um tweet em que irá ser feito a  intersecção com o outro parâmetro.
* @param secondTweet, é uma string que é um tweet em que irá ser feito a intersecção com o outro parâmetro.
* @return countIntersection, é um inteiro com o valor de quantidade elementos presente no conjunto de intersecção.
*/
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

	/* Retorna a quantidade de elementos no conjunto de intersecção */
	return countIntersection;
}

/**
* A função indexOfJaccard(List* listOfTweets) recebe uma lista de tweets,
* em que irá ser verificado a similiaridade entre os tweets, dessa lista aplicando
* o conceito de índice de Jaccard, em que consiste em duas operações a intersecção
* e a união. A divisão dessas duas operações retorna um valor de 0 e 1, e só consideramos
* similiares aqueles que o resultado dessa operação retorna um valor superior ao 0.3.
* Tweets com valores superiores a 0.3 adicionamos em uma lista, que irá ser retornada.
* @param listOfTweets, é uma lista de tweets, com todos os tweets presentes no arquivo que foi passado
* por parâmetro quando rodamos o programa ou que foi gerado no nosso programa.
* @return listOfSimiliar, é uma lista de tweets, mas todos aqueles que são similiares.
*/
ListSimiliarity *indexOfJaccard(List* listOfTweets){
	ListSimiliarity* listOfSimiliar = (ListSimiliarity*) malloc (sizeof(ListSimiliarity*));
	Node *nodeFirst, *nodeSecond;
	char firstTweetAuxiliar[SIZESTRING], secondTweetAuxiliar[SIZESTRING];
	
	/* Inicializa a lista */
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

				/* Somente tweets com similiaridade maior que 0.3 são aceitos */
				double similiarity = (double)intersectionTweets / (double)unionTweets;
				if(similiarity > 0.3){
					printf(ANSI_COLOR_GREEN "É similiar\n" ANSI_COLOR_RESET);			
					insertTweetListSimiliarity(listOfSimiliar, nodeFirst -> id, nodeFirst -> originalTweet, nodeSecond -> id, nodeSecond -> originalTweet, intersectionTweets, unionTweets, similiarity);
				}
			}
			
			/* Vai para o próximo nó da lista */
			nodeSecond = nodeSecond -> next;
		}

		/* Vai para o próximo nó da lista */
		nodeFirst = nodeFirst -> next;
	}

	/* Retorna a lista de tweets similiares */
	return listOfSimiliar;
}