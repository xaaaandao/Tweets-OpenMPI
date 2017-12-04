#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generateTweets(char *theme){
	char command[] = "python searchTweets.py ";
	strcat(command, theme);
	system(command);
}