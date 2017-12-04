#include "jaccard.h"

int countIntersectionTweets(char *firstTweet, char *secondTweet){
	return 0;
}


int countAllWords(char *firstTweet, char *secondTweet){
	char *parserFirstTweet = strtok(firstTweet, " ");
    int countFirstTweet = 0;

    while(parserFirstTweet != NULL){
        parserFirstTweet = strtok(NULL, " ");
        countFirstTweet++;
    }

	char *parserSecondTweet = strtok(secondTweet, " ");
    int countSecondTweet = 0;

    while(parserSecondTweet != NULL){
        parserSecondTweet = strtok(NULL, " ");
        countSecondTweet++;
    }

    return countFirstTweet + countSecondTweet;
}

void indexOfJaccard(List* listOfTweets){
	Node *nodeFirst, *nodeSecond;
	nodeFirst = listOfTweets -> first;
	nodeSecond = listOfTweets -> first;
	while (nodeFirst != NULL){ 
		while(nodeSecond != NULL){
			/* Ou seja, as string não são iguais */
			if(stringEquals(nodeFirst -> tweet, nodeSecond -> tweet) != 0){
				int intersectionTweets = countIntersectionTweets(nodeFirst -> tweet, nodeSecond -> tweet);
				int unionTweets = countAllWords(nodeFirst -> tweet, nodeSecond -> tweet);
			}
			nodeSecond = nodeSecond -> next;
		}
		nodeFirst = nodeFirst -> next;
	}
}