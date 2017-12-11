#include "generateTweets.h"

void generateTweets(char *theme){
	char command[] = "python searchTweets.py ";
	strcat(command, theme);
	system(command);
}