#include "manipulateList.h"

/**
* Autor: Alexandre Yuji Kajihara
* Descrição: Definimos as funções e implementamos elas para que se tenha
* um lugar para que possam ser armazenadas os tweets do arquivo de entrada.
* Data de criaçãoo: 11/12/2017
* Data de atualização: 11/12/2017
**/

/**
* A função specificTweets(List *list, char *range) recebe uma lista de tweets, com todos os tweets
* presentes no arquivo passado por parâmetro ou gerado durante a execução, e um intervalo de valores.
* A partir desse intervalo, todos os tweets que tem o identificador nesse intervalo são adicionados
* em uma lista e essa lista é retornada.
* @param list, é uma lista de tweets, com todos os tweets presentes no arquivo que foi passado
* por parâmetro quando rodamos o programa ou que foi gerado no nosso programa.
* @param range, é uma string com intervalo de tweets que deve ser adicionados em uma lista.
* @return listOfTweets, é uma lista de tweets, com todos os tweets presentes no intervalo que foi
* passado por parâmetro.
*/
List *specificTweets(List *list, char *range){
	int start, end;
	/* Pega o ínicio do intervalo */
	char *parserRange = strtok(range, "-");
	start = atoi(parserRange);

	List* listOfTweets = (List*) malloc (sizeof(List*));

	/* Inicializando na lista */
	initializeList(listOfTweets);

	/* Pega o fim do intervalo */
    while(parserRange != NULL){
    	end = atoi(parserRange);
    	parserRange = strtok(NULL, "-");
    }

    /* Percorre a lista atrás de tweets que estão naquele intervalo */
    Node *auxiliar = list -> first;
    while(auxiliar != NULL){
    	if(auxiliar -> id > end){
    		break;
    	}
    	if(auxiliar -> id >= start && auxiliar -> id <= end){
			insertTweetCompleteList(listOfTweets, auxiliar -> id, auxiliar -> originalTweet, auxiliar -> cleanTweet, auxiliar -> countWordOriginalTweet, auxiliar -> countWordCleanTweet);
    	}
    	auxiliar = auxiliar -> next;
    }

    /* Retorna a lista com os tweets daquele intervalo */
    return listOfTweets;
}

/**
* A função cleanList(List *list) recebe uma lista de tweets, com todos os tweets
* presentes no arquivo passado por parâmetro ou gerado durante a execução.
* Percorre nó por nó da lista e dá um free nele, e por fim da um free na lista.
* @param list, é uma lista de tweets, com todos os tweets presentes no arquivo que foi passado
* por parâmetro quando rodamos o programa ou que foi gerado no nosso programa.
* @return é void não retorna nada.
*/
void cleanList(List *list){
    Node *temporary, *current;
    current = list -> first;

    /* Percorre a lista */
    while(current != NULL){
    	temporary = current -> next;
    	/* Free nó da lista */
    	free(current);
    	current = temporary;
    }

    /* Free na lista */
    free(list);
}

/**
* A função cleanList(List *list) recebe uma lista de tweets, com todos os tweets
* presentes no arquivo passado por parâmetro ou gerado durante a execução.
* Inicializa essa lista apontando tudo para NULL.
* @param list, é uma lista de tweets, com todos os tweets presentes no arquivo que foi passado
* por parâmetro quando rodamos o programa ou que foi gerado no nosso programa.
* @return é void não retorna nada.
*/
void initializeList(List *list){
	/* Inicializa a lista */
	list -> first = NULL;
	list -> last = NULL;
	list -> size = 0;
}

/**
* A função emptyList(List *list) recebe uma lista de tweets, com todos os tweets
* presentes no arquivo passado por parâmetro ou gerado durante a execução.
* Verificando se a lista é vazia ou não, se for vazia retorna true caso contrário false.
* @param list, é uma lista de tweets, com todos os tweets presentes no arquivo que foi passado
* por parâmetro quando rodamos o programa ou que foi gerado no nosso programa.
* @return true ou false, true caso seja vazia, false caso não seja.
*/
bool emptyList(List *list){
	/* Verifica se a lista aponta para NULL, se sim ela está vazia */
	if(list -> first == NULL)
		return true;
	return false;
}  

/**
* A função insertTweetList(List *list, char* tweet) recebe uma lista de tweets
* onde será adicionado o tweet recebido por parâmetro. A partir desse parâmetro que é
* recebido será adicionado os outros valores nos outros campos do nó. Com o tweet original
* removemos algumas palavras e caracteres indesejados e adicionamos no outro campo do nó
* da lista e também contamos a quantidade de palavras após essa limpa do tweet original 
* e adicionamos nó campo do nó da lista.
* @param list, é uma lista de tweets onde será adiciona tweet, e outros valores a partir do tweet original.
* @param tweet, é uma string com o conteúdo que estava presente no arquivo.
* @return é void não retorna nada.
*/
void insertTweetList(List *list, char* tweet){
	/* Identificador dos tweets */
	static int id = 0;
	
	/* Aloca um novo nó */
	Node *newNode = (Node*) malloc(sizeof(Node));
	
	/* Copia os valores para os campos do novo nó, limpa o tweet e conta a quantidade
	de palavras nos dois twwets */
	newNode -> id = id;
	strcpy(newNode -> originalTweet, tweet);
	strcpy(newNode -> cleanTweet, filterWordsOfText(newNode -> originalTweet));
	newNode -> countWordOriginalTweet = countWords(newNode -> originalTweet);
	newNode -> countWordCleanTweet = countWords(newNode -> cleanTweet);
	newNode -> next = NULL;

	/* Adiciona na lista */
	if (emptyList(list)){
		list -> first = newNode;
		list -> last = newNode;
	} else {
		list -> last -> next = newNode;
		list -> last = newNode;
	}

	list -> size++;
	id++;
}

/**
* A função insertTweetCompleteList(List *list, int id, char* originalTweet, char *cleanTweet, int countWordOriginalTweet, int countWordCleanTweet)
* recebe uma lista de tweets, em que em cada nó é adicionado, o id, conteúdo original do tweet,
* a quantidade de palavras presentes no tweet original, contéudo após a remoção de palavras e caracteres não necessários,
* a quantidade de palavras presentes no tweet limpo.
* @param list, é uma lista de tweets onde será adiciona todos parâmetros que foram recebidos.
* @param id, é um inteiro com identificador do tweet.
* @param originalTweet, é uma string com conteúdo original do tweet.
* @param cleanTweet, é uma string com conteúdo do tweet após uma remoçaõ dos caracteres e palavras indesejadas.
* @param countWordOriginalTweet, é uma inteiro com a quantidade de palavras presentes no tweet original.
* @param countWordCleanTweet, é uma inteiro com a quantidade de palavras presentes no tweet limpo.
* @return é void não retorna nada.
*/
void insertTweetCompleteList(List *list, int id, char* originalTweet, char *cleanTweet, int countWordOriginalTweet, int countWordCleanTweet){
	/* Aloca um novo nó */
	Node *newNode = (Node*) malloc(sizeof(Node));
	
	/* Copia os valores para os campos do novo nó */
	newNode -> id = id;
	strcpy(newNode -> originalTweet, originalTweet);
	strcpy(newNode -> cleanTweet, cleanTweet);
	newNode -> countWordOriginalTweet = countWordOriginalTweet;
	newNode -> countWordCleanTweet = countWordCleanTweet;
	newNode -> next = NULL;

	/* Adiciona na lista */
	if (emptyList(list)){
		list -> first = newNode;
		list -> last = newNode;
	} else {
		list -> last -> next = newNode;
		list -> last = newNode;
	}

	list -> size++;
}

/**
* A função sizeList(List *list) recebe uma lista de tweets, com todos os tweets
* presentes no arquivo passado por parâmetro ou gerado durante a execução,
* e retorna a quantidade nós presentes na lista.
* @param list, é uma lista de tweets, com todos os tweets presentes no arquivo que foi passado
* por parâmetro quando rodamos o programa ou que foi gerado no nosso programa.
* @return list -> size, que é um inteiro com o tamanho da lista.
*/
int sizeList(List *list){
	/* Retorna o tamanho da lista */
	return (list -> size);
}

/**
* A função printList(List *list) recebe uma lista de tweets, com todos os tweets
* presentes no arquivo passado por parâmetro ou gerado durante a execução. 
* É impresso o conteúdo do tweet original, id do primeiro tweet, a quantidade de 
* palavras presente no tweet original, tweet após a remoção de algumas palavras não necessárias,
* e a quantidade de palavras após essa limpeza.
* @param list, é uma lista de tweets, com todos os tweets presentes no arquivo que foi passado
* por parâmetro quando rodamos o programa ou que foi gerado no nosso programa.
* @return é void não retorna nada.
*/
void printList(List *list){
	/* Verifica se a lista é vazia */
	if (emptyList(list)){
		printf(ANSI_COLOR_RED "Empty list!" ANSI_COLOR_RESET "\n");
	/* Se a lista não for vazia */
	} else {
		Node *printNode;
		printNode = list -> first;
		/* Percorre a lista e imprime o conteúdo de cada nó */
		while (printNode != NULL){ 
			printf("ID: %d \n", printNode -> id);
			printf("Tweet original: %s \n", printNode -> originalTweet);
			printf("Quantidade de palavras tweet original: %d\n", printNode -> countWordOriginalTweet);
			printf("Tweet filtrado: %s \n", printNode -> cleanTweet);
			printf("Quantidade de palavras tweet filtrado: %d\n\n", printNode -> countWordCleanTweet);
			printNode = printNode -> next;
		}
	}    
}

/**
* A função cleanListSimiliarity(ListSimiliarity *list) recebe uma lista de tweets que são similiares,
* que foram obtidos aplicando o índice de Jaccard. Percorre nó por nó da lista
* e dá um free nele, e por fim da um free na lista.
* @param list, é uma lista de tweets que são similiares, que são obtidos pelo índice de Jaccard.
* @return é void não retorna nada.
*/
void cleanListSimiliarity(ListSimiliarity *list){
    NodeSimiliarity *temporary, *current;
    current = list -> first;

    /* Percorre a lista */
    while(current != NULL){
    	temporary = current -> next;
    	/* Free nó da lista */
    	free(current);
    	current = temporary;
    }

    /* Free na lista */
    free(list);
}

/**
* A função initializeListSimiliarity(ListSimiliarity *list) recebe uma lista de tweets que são similiares,
* que foram obtidos aplicando o índice de Jaccard. Inicializa essa lista apontando tudo para NULL.
* @param list, é uma lista de tweets que são similiares, que são obtidos pelo índice de Jaccard.
* @return é void não retorna nada.
*/
void initializeListSimiliarity(ListSimiliarity *list){
	/* Inicializa a lista */
	list -> first = NULL;
	list -> last = NULL;
	list -> size = 0;
}

/**
* A função emptyListSimiliarity(ListSimiliarity *list) recebe uma lista de tweets que são similiares,
* que foram obtidos aplicando o índice de Jaccard.
* Verificando se a lista é vazia ou não, se for vazia retorna true caso contrário false.
* @param list, é uma lista de tweets que são similiares, que são obtidos pelo índice de Jaccard.
* @return true ou false, true caso seja vazia, false caso não seja.
*/
bool emptyListSimiliarity(ListSimiliarity *list){
	/* Verifica se a lista aponta para NULL, se sim ela está vazia */
	if(list -> first == NULL)
		return true;
	return false;
}  

/**
* A função insertTweetListSimiliarity(ListSimiliarity *list, int firstId, char* firstTweet, int secondId, char* secondTweet, int valueIntersection, int valueUnion, int valueSimiliarity)
* recebe uma lista de tweets onde serão adicionado os tweets que são similiares. Recebe
* o id do primeiro tweet, conteúdo do primeiro tweet, id do segundo tweet, conteúdo do segundo tweet,
* valor de união, interseccção e o valor de similiaridade, e adiciona todos esse parâmetros em um nó
* que será adicionado na lista recebida por parâmetro.
* @param list, é uma lista de tweets que são similiares, que são obtidos pelo índice de Jaccard.
* @param firstId, é um inteiro com identificador do primeiro tweet.
* @param firstTweet, é uma string com conteúdo do primeiro tweet.
* @param secondId, é um inteiro com identificador do segundo tweet.
* @param secondTweet, é uma string com conteúdo do segundo tweet.
* @param valueIntersection, é um inteiro com o valor de intersecção desses dois tweets.
* @param valueUnion, é um inteiro com o valor de união desses dois tweets.
* @param valueSimiliarity, é um inteiro com o valor de similiaridade desses dois tweets.
* @return é void não retorna nada.
*/
void insertTweetListSimiliarity(ListSimiliarity *list, int firstId, char* firstTweet, int secondId, char* secondTweet, int valueIntersection, int valueUnion, int valueSimiliarity){
	/* Aloca um novo nó */
	NodeSimiliarity *newNode = (NodeSimiliarity*) malloc(sizeof(NodeSimiliarity));

	/* Copia os valores para os campos do novo nó */
	newNode -> firstId = firstId;
	strcpy(newNode -> firstTweet, firstTweet);
	newNode -> secondId = secondId;
	strcpy(newNode -> secondTweet, secondTweet);
	newNode -> valueIntersection = valueIntersection;
	newNode -> valueUnion = valueUnion;
	newNode -> valueSimiliarity = valueSimiliarity;
	newNode -> next = NULL;

	/* Adiciona na lista */
	if (emptyListSimiliarity(list)){
		list -> first = newNode;
		list -> last = newNode;
	} else {
		list -> last -> next = newNode;
		list -> last = newNode;
	}

	list -> size++;
}
 
/**
* A função sizeListSimiliarity(ListSimiliarity *list) recebe uma lista de tweets que são similiares,
* que foram obtidos aplicando o índice de Jaccard, e retorna o seu tamanho.
* @param list, é uma lista de tweets que são similiares, que são obtidos pelo índice de Jaccard.
* @return list -> size, que é um inteiro com o tamanho da lista.
*/
int sizeListSimiliarity(ListSimiliarity *list){
	/* Retorna o tamanho da lista */
	return (list -> size);
}

/**
* A função printListSimiliarity(ListSimiliarity *list) recebe uma lista de tweets que são similiares,
* que foram obtidos aplicando o índice de Jaccard, e é impresso o conteúdo do primeiro tweet, id do
* primeiro tweet, o conteúdo do segundo tweet, id do segundo tweet, valor de união, interseccção
* e similiaridade de cada nó.
* @param list, é uma lista de tweets que são similiares, que são obtidos pelo índice de Jaccard.
* @return é void não retorna nada.
*/
void printListSimiliarity(ListSimiliarity *list){
	/* Verifica se a lista é vazia */
	if (emptyListSimiliarity(list)){
		printf(ANSI_COLOR_RED "Empty list!" ANSI_COLOR_RESET "\n");
	/* Se a lista não for vazia */
	} else {
		/* Percorre a lista e imprime o conteúdo de cada nó */
		NodeSimiliarity *printNode;
		printNode = list -> first;
		while (printNode != NULL){
			printf("First Id: %d\n", printNode -> firstId);
			printf("First Tweet: %s\n", printNode -> firstTweet);
			printf("Second Id: %d\n", printNode -> secondId);
			printf("Second Tweet: %s\n\n", printNode -> secondTweet);
			printNode = printNode -> next;
		}
	}    
}

/**
* A função getSimiliarity(ListSimiliarity *list) recebe uma lista de tweets que são similiares,
* que foram obtidos aplicando o índice de Jaccard, adiciona na string todos os identificadores dos
* tweets que são similiares.
* @param list, é uma lista de tweets que são similiares, que são obtidos pelo índice de Jaccard.
* @return similiarity, é uma string com todos os valores dos identificadores que são similiares.
*/
char *getSimiliarity(ListSimiliarity *list){
	char *similiarity = (char*) malloc(sizeof(char) * ALLSIMILIARITY);
	char range[SIZESTRING];
	/* Verifica se a lista é vazia */
	if (emptyListSimiliarity(list)){
		printf(ANSI_COLOR_RED "Empty list!" ANSI_COLOR_RESET "\n");
	/* Se a lista não for vazia */
	} else {
		NodeSimiliarity *printNode;
		printNode = list -> first;
		/* Adiciona o identificador dos dois tweets que são similiares */
		while (printNode != NULL){
			sprintf(range, "%d-%d;", printNode -> firstId, printNode -> secondId);
			strcat(similiarity, range);
			memset(range, 0, SIZESTRING);
			printNode = printNode -> next;
		}
	}  
	/* Retorna a string */ 
	return similiarity;
}

/**
* A função existSimiliar(ListSimiliarity *list, int firstId, int secondId) recebe uma lista de tweets que são similiares,
* e dois identificadores, em que é procurado um tweet com esses valores de identificadores
* que foram recebido por parâmetro.
* @param list, é uma lista de tweets que são similiares, que são obtidos pelo índice de Jaccard.
* @param firstId, é um inteiro com o identificado do tweet que será procurado.
* @return true ou false, true caso já esteja presente na lista e false caso não esteja presente.
*/
bool existSimiliar(ListSimiliarity *list, int firstId, int secondId){
	/* Verifica se a lista é vazia */
	if (emptyListSimiliarity(list)){
		printf(ANSI_COLOR_RED "Empty list!" ANSI_COLOR_RESET "\n");
	/* Se a lista não for vazia */
	} else {
		NodeSimiliarity *printNode;
		printNode = list -> first;
		/* Verifica se esses id's já estão presente na lista */
		while (printNode != NULL){
			if(printNode -> firstId == firstId && printNode -> secondId == secondId){
				return true;
			}
			printNode = printNode -> next;
		}
	}  
	return false;
}