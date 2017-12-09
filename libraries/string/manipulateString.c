#include "manipulateString.h"

bool stringEquals(char* x, char* y){
	if(strlen(x) != strlen(y))
		return false;
	int i = 0;
	while(x[i] != '\0'){
		if(x[i] != y[i]){
			return false;
		}
		i++;
	}
	return true;
}

void loadWord(char* text, char array[][SIZESTRING]){
	/* Faz uma cópia da string para que possa ser alterada */
	char copyText[SIZESTRING];
	strcpy(copyText, text);

	/* Quebra o texto em espaço */
	char *parserText = strtok(copyText, " ");
	int i = 0;

	while(parserText != NULL){
		/* Deixa tudo minuscúlo e cópia para o vetor de String*/
		convertToLower(parserText);
    	strcpy(array[i], parserText);
    	parserText = strtok(NULL, " ");
    	i++;
    }
}

void removeCharacter(char *word){
	if(word[strlen(word) - 1] == ':')
		word[strlen(word) - 1] = '\0';
	else if(word[strlen(word) - 1] == ',')
		word[strlen(word) - 1] = '\0';
	else if(word[strlen(word) - 1] == '-')
		word[strlen(word) - 1] = '\0';
	else if(word[strlen(word) - 1] == '.' && word[strlen(word) - 2] == '.')
		word[strlen(word) - 2] = '\0';
	else if(word[strlen(word) - 1] == '.' && word[strlen(word) - 2] == '.' && word[strlen(word) - 3] == '.')
		word[strlen(word) - 3] = '\0';
	else if(word[strlen(word) - 1] == '.' && word[strlen(word) - 2] == '.' && word[strlen(word) - 3] == '.' && word[strlen(word) - 4] == ',')
		word[strlen(word) - 4] = '\0';
	else if(word[strlen(word) - 1] == '.')
		word[strlen(word) - 1] = '\0';
	else if(word[strlen(word) - 1] == '!')
		word[strlen(word) - 1] = '\0';
	else if(word[strlen(word) - 1] == '?')
		word[strlen(word) - 1] = '\0';
	else if(word[strlen(word) - 1] == '\n')
		word[strlen(word) - 1] = '\0';
	else if(word[strlen(word) - 1] == '\t')
		word[strlen(word) - 1] = '\0';
}

bool allowWord(char *word){
	removeCharacter(word);
	if(stringEquals(word, "rt") || word[0] == '@' || word[0] == '#' || word[0] == '-' || word[0] == '|' || word[0] == '/')
		return false;
	if(word[0] == '\n' || word[0] == '\t')
		return false;
	if(word[0] == '1' || word[0] == '2' || word[0] == '3' || word[0] == '4' || word[0] == '5')
		return false;
	if(word[0] == '6' || word[0] == '7' || word[0] == '8' || word[0] == '9' || word[0] == '0')
		return false;
	if(stringEquals(word, "&amp") || stringEquals(word, "&amp;") || stringEquals(word, "-&amp") || stringEquals(word, "-&amp;"))
		return false;
	if(stringEquals(word, "&gt") || stringEquals(word, "&gt;") || stringEquals(word, "-&gt") || stringEquals(word, "-&gt;"))
		return false;
	if(stringEquals(word, "&lt") || stringEquals(word, "&lt;") || stringEquals(word, "-&lt") || stringEquals(word, "-&lt;")  || stringEquals(word, "&lt;="))
		return false;
	if((strstr(word, "http://t.co/") != NULL) || (strstr(word, "http://bit.ly/") != NULL))
		return false;
	return true;
}

char *filterWordsOfText(char *text){
	/* Texto filtrado à partir do texto final */
	char *result = (char*) malloc(sizeof(char) * SIZESTRING);
	/* Prévia da palavra filtrada */
	char word[SIZESTRING];
	
	/* Faz uma cópia da string para que possa ser alterada */
	char newText[strlen(text)];
	strcpy(newText, text);

	/* Conto a quantidade de palavras presente no texto, adiciono num vetor de String */
	int numberOfWords = countWords(newText);
	char wordsOfText[numberOfWords][SIZESTRING];
	loadWord(newText, wordsOfText);

	/* Percorro esse vetor de String */
	int i;
	for(i = 0; i < numberOfWords; i++){

		/*
		* Se for diferente de NULL significa que eu devo copiar a string para string final
		* Removemos links, @menções e hashtag
		*/
		if(allowWord(wordsOfText[i])){
			strcat(result, wordsOfText[i]);
			strcat(result, " ");
		}
	}
	printf("\no: %s\n", text);
	printf("f: %s\n", result);
	return result;
}

int countWords(char *text){
	char copyText[SIZESTRING];
	strcpy(copyText, text);

	char *parserText = strtok(copyText, " ");
    int numberOfWords = 0;

    while(parserText != NULL){
    	parserText = strtok(NULL, " ");
        numberOfWords++;
    }

    return numberOfWords;
}

void convertToLower(char *string){
	int i = 0;
	while(string[i] != '\0'){
		if(string[i] != '-'){	
			if(string[i] > 64 && string[i] < 91)
				string[i] = string[i] + 32;	
		}
		i++;
	}
}
