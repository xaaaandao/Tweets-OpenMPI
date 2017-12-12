#include "manipulateFiles.h"

/**
* Autor: Alexandre Yuji Kajihara
* Descrição: Definimos as funções e implementamos elas para que possa
* ser feito a manipulação de arquivos.
* Data de criaçãoo: 11/12/2017
* Data de atualização: 11/12/2017
**/

/**
* A função clearScreen() executa o comando no terminal de limpar a tela.
* @param nenhum parâmetro.
* @return é void não retorna nada.
*/
void clearScreen(){
	/* Executa o comando no terminal */
	system("clear");
}

/**
* A função loadTweets(char *fileJSON) recebe o nome de um arquivo como parâmetro
* abre o arquivo lê linha por linha e adiciona em uma lista cada linha que representa
* um tweet, e após de colocar todos os tweets na linha retorna essa lista.
* @param fileJSON, é uma string com o nome do arquivo.
* @return listOfTweets, é uma lista que contém todos os tweets presentes no arquivo.
*/
List *loadTweets(char *fileJSON){
	/* Abro o arquivo e inicializo a lista */
	FILE *file = fopen(fileJSON, "r");
	List* listOfTweets = (List*) malloc (sizeof(List*));
	char tweet[SIZESTRING];

	/* Inicializando na lista */
	initializeList(listOfTweets);

	while((fgets(tweet, sizeof(tweet), file)) != NULL){
		clearScreen();
		printf(ANSI_COLOR_GREEN "Carregando os tweets na lista\n" ANSI_COLOR_RESET);

		/* Tirando o caractere " da última posição */
		tweet[strlen(tweet) - 2] = '\0';
		
		/* Tirando o caractere " da primeira posição */
		char newTweet[SIZESTRING];
		strncpy(newTweet, tweet + 1, strlen(tweet) - 1);

		/* Adicionando na lista */
		insertTweetList(listOfTweets, newTweet);
		
		/* Limpando a string */
		memset(tweet, 0, SIZESTRING);
		memset(newTweet, 0, SIZESTRING);
	}

	/* Retorna todos os tweets em uma lista */
	fclose(file);
	return listOfTweets;
}

/**
* A função parserJSON(char *nameFile) recebe o nome de um arquivo JSON
* verifica se o arquivo é JSON mesmo, se for executa um comando nesse 
* arquivo para pegar somente o campo text desse JSON, após isso escreve a 
* saída em um arquivo e chama a função que carrega todo o conteúdo desse
* arquivo gerado para uma lista e retorna essa lista.
* @param nameFile, é uma string com o nome do arquivo JSON.
* @return loadTweets("teste.txt"), é uma lista que contém todos os tweets presentes no arquivo.
*/
List *parserJSON(char *nameFile){
	/* Verifico se o arquivo é um JSON ou não */
	if(strstr(nameFile, ".json") == NULL)
		return NULL;

	/* Dando um parser no .json recebido como parâmetro */
	char commandCat[SIZESTRING] = "cat ";
	strcat(commandCat, nameFile);
	char parserTweet[SIZESTRING] = " | jq '.text' > teste.txt";
	strcat(commandCat, parserTweet);
	char command[SIZESTRING] = "";
	strcat(command, commandCat);

	/* Executando o parser */
	system(command);

	/* Retorno a lista de tweet */
	return loadTweets("teste.txt");
}

/**
* A função existVector(int array[], int value, int size) recebe um arranjo
* na qual irá ser verificado se o elemento passado por parâmetro, está presente
* ou não no arranjo.
* @param array[], é uma vetor de inteiros onde será procurado o valor.
* @param value, é o elemento a ser procurado no arranjo.
* @param size, é o tamanho do vetor de inteiros.
* @return true ou false, true caso exista o elemento no arranjo, e false caso não exista.
*/
bool existVector(int array[], int value, int size){
	int i = 0;
	while(i < size){
		if(array[i] == value){
			return true;
		}
		i++;
	}
	return false;
}

/**
* A função generateOutput(List *listOfTweets, char *tweets) recebe o vetor
* com todos os tweets, e todos os tweets que são similares, com isso imprime
* em um arquivo todos tweets que são similares.
* @param listOfTweets, é uma lista com todos os tweets.
* @param tweets, é uma string com os tweets que são similares.
* @return true ou false, true caso consiga gerar o arquivo, e false caso não consiga.
*/
bool generateOutput(List *listOfTweets, char *tweets){
	int value, i = 0, j = 0, k = 0;
	int id[listOfTweets -> size];
	char string[SIZESTRING];
	
	/* Remove o último hífen */
	tweets[strlen(tweets) - 1] = '\0';

	/* Percorre a string pegando os valores */
	while(tweets[i] != '\0'){
		if(tweets[i] == '-'){
			string[j] = '\0';
			if(k == 0){
				id[k] = atoi(string);
				k++;
			} else {
				if(!existVector(id, atoi(string), k)){
					id[k] = atoi(string);
					k++;
				}
			}
			memset(string, 0, SIZESTRING);
			j = 0; 
		} else {
			string[j] = tweets[i];
			j++;
		}
		i++;
	}

	FILE *file = fopen("/home/xandao/cloud/Tweets-OpenMPI/output.txt", "w");
	fprintf(file, "Tweet que são similares\n");
	if (emptyList(listOfTweets)){
		printf(ANSI_COLOR_RED "Empty list!" ANSI_COLOR_RESET "\n");
		return false;
	/* Se a lista não for vazia */
	} else {
		Node *printNode;
		/* Percorre a lista e imprime o conteúdo de cada nó */
		for(i = 0; i < k; i++){
			printNode = listOfTweets -> first;
			while (printNode != NULL){ 
				/* Verifica se o valor do identificador tweet é igual ao que temos no vetor */
				if(printNode -> id == id[i]){
					fprintf(file, "Tweet: %s\n", printNode -> originalTweet);
					break;
				}
				printNode = printNode -> next;
			}	
		}		
	}

	fclose(file);
    return true;
}