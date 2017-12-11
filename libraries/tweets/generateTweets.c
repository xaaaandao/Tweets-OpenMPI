#include "generateTweets.h"

/**
* Autor: Alexandre Yuji Kajihara
* Descrição: Definimos as funções e implementamos elas para que possa
* ser feito a geração de um JSON, contendo tweets do tema escolhido pelo usuário.
* Data de criaçãoo: 11/12/2017
* Data de atualização: 11/12/2017
**/

/**
* A função lgenerateTweets(char *theme) recebe uma string que é o tema 
* que ele deseja pesquisa no Twitter, executamos isso através do arquivo python
* que está no mesmo diretório com o tema escolhido pelo usuário, e depois copiamos 
* aonde está o main para que possa ser processado.
* @param theme, é uma string na qual será pesquisado tweets com o assunto escolhido pelo usuário.
* @return é void não retorna nada.
*/
void generateTweets(char *word){
	char command[] = "python searchTweets.py ";
	strcat(command, word);
	system(command);
	system("cp output.json ../");
}