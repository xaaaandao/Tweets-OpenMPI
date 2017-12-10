#include "libraries/tweets/generateTweets.h"
#include "libraries/string/manipulateString.h"
#include "libraries/files/manipulateFiles.h"
#include "libraries/list/manipulateList.h"
#include "libraries/jaccard/jaccard.h"

int main(int argc, char* argv[]){
	/* Só aceito se tiver três parâmetros */
	if(argc == 3){

		/* Converto a opção que foi passada por parâmetro */
		bool filetweet = false;
		char option[strlen(argv[1])];
		strcpy(option, argv[1]);
		convertToLower(option);
		
		/* Se o parâmetro é um -q, ou seja, significa que eu quero realizar uma pesquisa,
		*  ou seja, gerar um JSON com o assunto que foi escolhido
		*/
		if(strcmp(option, "-q\0") == 0){
			generateTweets(argv[2]);
			filetweet = true;
		}

		/* Se o parâmetro é -f significa que eu vou passar um arquivo no formato JSON,
		* verifica se é um arquivo que acabou de ser criado ou se não é.
		*/
		if(strcmp(option, "-f\0") == 0 || filetweet){

			/* Se o arquivo foi recentemente criado, é gerado um arquivo no nome 
			* output.json, ou seja, é ele que vai ser carregado. Caso não tenha sido
			* criado, então pega o que foi passado parâmetro
			*/
			if(filetweet == true)
				strcpy(argv[2], "output.json");
			
			/* Carrega o arquivo em uma lista */
			List *listOfTweets = parserJSON(argv[2]);

			/* Se for NULL significa que não é um arquivo JSON */
			if(listOfTweets == NULL){
				printf(ANSI_COLOR_RED "o arquivo deve ser um .json!\n" ANSI_COLOR_RESET);
				return 0;

			/* Caso contrário, é um JSON */
			} else {
				/* Se for NULL significa que tem algo de errado no arquivo */
				if(indexOfJaccard(listOfTweets, argv[2]) == NULL){
					printf(ANSI_COLOR_RED "erro no arquivo %s\n" ANSI_COLOR_RESET, argv[2]);
				} else {
					printf("Pode prosseguir\n");
				}
				//printf("s: %d\n", listOfTweets -> size);

				/* Apaga o arquivo que só contém os tweets, sem estar no formato de JSON */
				system("rm teste.txt");
			}

		/* Se não for nenhum dos parâmetros -q ou -f ERRO! */
		} else
			printf(ANSI_COLOR_RED "parâmetro errado!\nuse %s ou %s -q tema ou %s -f arquivo\n" ANSI_COLOR_RESET, argv[0], argv[0], argv[0]);

	/* Se a quantidade de parâmetros for diferente de três ERRO! */
	} else if(argc > 3 || argc < 3)
		printf(ANSI_COLOR_RED "use %s -q tema ou %s -f arquivo\n" ANSI_COLOR_RESET, argv[0], argv[0]);
	
	return 0;
}