#include "manipulateString.h"

/**
* A função stringEquals(char* x, char* y) recebe duas strings, e será verificado
* se ambas strings são iguais ou não, se sim retorna true caso contrário false.
* @param x, é uma string que será verificaddo se é idêntica a string y.
* @param y, é uma string que será verificaddo se é idêntica a string x.
* @return true ou false, true caso sejem idênticas ou false caso não seja.
*/
bool stringEquals(char* x, char* y){
	/* Se o tamanho é diferente já retorna false */
	if(strlen(x) != strlen(y))
		return false;
	int i = 0;

	/* Pecorre a string */
	while(x[i] != '\0'){
		/* Se o valor for diferente já retorna false */
		if(x[i] != y[i]){
			return false;
		}
		i++;
	}

	/* Senão retorna verdade */
	return true;
}

/**
* A função loadWord(char* text, char array[][SIZESTRING]) recebe tweet e um vetor de string
* cada palavra do tweet é adicionada no vetor de string.
* @param text, é uma string que é um tweet na qual adicionado no vetor de string.
* @param array, é um vetor de string na qual receberá as palavras presente no tweet.
* @return é void não retorna nada.
*/
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

/**
* A função removeCharacter(char *word) recebe uma palavra que é uma palavra do tweet, 
* e irá ser verificado se tem alguns caracteres se sim remove elas, caso contrário não faz
* nada.
* @param word, é uma string que é uma palavra que está tweet na qual será verificado sua permissão.
* @return é void não retorna nada.
*/
void removeCharacter(char *word){
	/* Verifica se nas últimas posições são alguns desses caracteres se sim remove eles! */
	if((word[strlen(word) - 1] == ':') || (word[strlen(word) - 1] == ',') || (word[strlen(word) - 1] == '-'))
		word[strlen(word) - 1] = '\0';
	else if(word[strlen(word) - 1] == '.' && word[strlen(word) - 2] == '.')
		word[strlen(word) - 2] = '\0';
	else if(word[strlen(word) - 1] == '.' && word[strlen(word) - 2] == '.' && word[strlen(word) - 3] == '.')
		word[strlen(word) - 3] = '\0';
	else if(word[strlen(word) - 1] == '.' && word[strlen(word) - 2] == '.' && word[strlen(word) - 3] == '.' && word[strlen(word) - 4] == ',')
		word[strlen(word) - 4] = '\0';
	else if((word[strlen(word) - 1] == '.') || (word[strlen(word) - 1] == '!'))
		word[strlen(word) - 1] = '\0';
	else if((word[strlen(word) - 1] == '?') || (word[strlen(word) - 1] == '\n') || (word[strlen(word) - 1] == '\t'))
		word[strlen(word) - 1] = '\0';
}

/**
* A função allowWord(char *word) recebe uma palavra que é uma palavra do tweet, 
* e irá ser verificado se ela é permitida, se sim retorna true caso contrário
* retorna false.
* @param word, é uma string que é uma palavra que está tweet na qual será verificado sua permissão.
* @return true ou false, true caso seja permitida ou falso caso não seja permtido.
*/
bool allowWord(char *word){
	/* Retorna true ou false caso seja um desses caracteres ou palavras */
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
	if(stringEquals(word, "e&amp;p") || stringEquals(word, "\"/?-s\"") || stringEquals(word, "....") || stringEquals(word, ".cc")  || stringEquals(word, "&lt;&lt;"))
		return false;
	if(stringEquals(word, ";)") || stringEquals(word, ":/ ") || stringEquals(word, "^dg") || stringEquals(word, "&lt;p&gt;&amp;nbsp;&lt;/p&gt;&lt;p&gt;the")  || stringEquals(word, ",!!"))
		return false;
	if(stringEquals(word, "—") || stringEquals(word, "▸") || stringEquals(word, "👤") || stringEquals(word, "•") || stringEquals(word, "…"))
		return false;
	if((strstr(word, "http://t.co/") != NULL) || (strstr(word, "http://bit.ly/") != NULL))
		return false;
	return true;
}

/**
* A função filterWordsOfText(char *text) recebe uma string que é um tweet, 
* e irá remover alguns caracteres ou palavras indesejadas que podem estar
* presentes no tweet, e por fim retorna esse tweet sem esses caracteres 
* e palavras
* @param text, é uma string que é um tweet na qual será eliminado caracteres ou palavras.
* @return result, é uma string que é o tweet sem alguns caracteres ou palavras.
*/
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

	return result;
}

/**
* A função countWords(char *text) recebe uma string que é um tweet, 
* elimina os espaços vazios e a cada eliminição incrementa uma variável 
* que representa a quantidade de palavras presentes no texto.
* @param text, é uma string que será contada a quantidade de palavras;
* @return numberOfWord, é um inteiro com a quantidade de palavras.
*/
int countWords(char *text){
	char copyText[SIZESTRING];
	strcpy(copyText, text);

	/* Quebra o tweet pelos espaços */
    char *parserText = strtok(copyText, " ");
    int numberOfWords = 0;

    /* Quebra o tweet pelos espaços */
    while(parserText != NULL){
    	parserText = strtok(NULL, " ");
        numberOfWords++;
    }

    /* Retorna o número de palavras */
    return numberOfWords;
}

/**
* A função convertToLower(char *string) recebe uma string todos os caracteres que são
* maiuscúlo são convertidos para minuscúlo;
* @param string, é uma string que será convertida para caracteres minuscúlo;
* @return é void não retorna nada.
*/
void convertToLower(char *string){
	int i = 0;
	/* Percorre a string  */
    while(string[i] != '\0'){
    	/* Se for um caractere maiuscúlo converte para minuscúlo */
		if(string[i] != '-'){	
			if(string[i] > 64 && string[i] < 91)
				string[i] = string[i] + 32;	
		}
		i++;
	}
}
