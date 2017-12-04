#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "libraries/tweets/generateTweets.h"
#include "libraries/string/manipulateString.h"
#include "libraries/files/readFile.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

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
			if(filetweet == true){
				strcpy(argv[2], "output.txt");
			}
			readFile(argv[2]);	
		} else {
			printf(ANSI_COLOR_RED "parâmetro errado!\n");
			printf("use %s ou %s -q tema ou %s -f arquivo\n" ANSI_COLOR_RESET, argv[0], argv[0], argv[0]);
		}
	} else if(argc > 3){
		printf(ANSI_COLOR_RED "use %s -q tema ou %s -f arquivo\n" ANSI_COLOR_RESET, argv[0], argv[0]);
		return 0;
	}

	return 0;
}