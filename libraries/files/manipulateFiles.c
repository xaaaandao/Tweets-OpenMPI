#include "manipulateFiles.h"

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