#include "generateTweets.h"

/**
* A função lgenerateTweets(char *theme) recebe uma string que é o tema 
* que ele deseja pesquisa no Twitter, executamos isso através do arquivo python
* que está no mesmo diretório com o tema escolhido pelo usuário, e depois copiamos 
* aonde está o main para que possa ser processado.
* @param theme, é uma string na qual será pesquisado tweets com o assunto escolhido pelo usuário.
* @return é void não retorna nada.
*/
void generateTweets(char *theme){
	char command[] = "python searchTweets.py ";
	strcat(command, theme);
	system(command);
	system("cp output.json ../");
}