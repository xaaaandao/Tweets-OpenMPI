#include "libraries/tweets/generateTweets.h"
#include "libraries/string/manipulateString.h"
#include "libraries/files/manipulateFiles.h"
#include "libraries/list/manipulateList.h"
#include "libraries/jaccard/jaccard.h"

int main(int argc, char* argv[]){
	if(argc == 3){
		bool filetweet = false;
		char option[strlen(argv[1])];
		strcpy(option, argv[1]);
		convertToLower(option);
		if(stringEquals(option, "-q\0") == 0){
			generateTweets(argv[2]);
			filetweet = true;
		}
		if(stringEquals(option, "-f\0") == 0 || filetweet){
			if(filetweet == true)
				strcpy(argv[2], "output.json");
			List *listOfTweets = parserJSON(argv[2]);
			if(listOfTweets == NULL){
				printf(ANSI_COLOR_RED "o arquivo deve ser um .json!\n" ANSI_COLOR_RESET);
				return 0;
			} else {
				printf(ANSI_COLOR_GREEN "carregando o arquivo ...\n" ANSI_COLOR_GREEN);
				indexOfJaccard(listOfTweets);
			}

		} else
			printf(ANSI_COLOR_RED "parâmetro errado!\nuse %s ou %s -q tema ou %s -f arquivo\n" ANSI_COLOR_RESET, argv[0], argv[0], argv[0]);

	} else if(argc > 3 || argc < 3)
		printf(ANSI_COLOR_RED "use %s -q tema ou %s -f arquivo\n" ANSI_COLOR_RESET, argv[0], argv[0]);
	
	return 0;
}