#include "manipulateFiles.h"

void clearScreen(){
	system("clear");
}

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