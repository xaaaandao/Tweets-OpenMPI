#include "manipulateList.h"

void cleanList(List *list){
    Node *temporary, *current;
    current = list -> first;
    while(current != NULL){
    	temporary = current -> next;
    	free(current);
    	current = temporary;
    }
    free(list);
}

void initializeList(List *list){
	list -> first = NULL;
	list -> last = NULL;
	list -> size = 0;
}

bool emptyList(List *list){
	if(list -> first == NULL)
		return true;
	return false;
}  

void insertTweetList(List *list, char* tweet){
	static int id = 1;
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode -> id = id;
	strcpy(newNode -> originalTweet, tweet);
	strcpy(newNode -> cleanTweet, filterWordsOfText(newNode -> originalTweet));
	newNode -> countWordOriginalTweet = countWords(newNode -> originalTweet);
	newNode -> countWordCleanTweet = countWords(newNode -> cleanTweet);

	newNode -> next = NULL;

	if (emptyList(list)){
		list -> first = newNode;
		list -> last = newNode;
	} else {
		list -> last -> next = newNode;
		list -> last = newNode;
	}

	list -> size++;
	id++;
}
 
int sizeList(List *list){
	return (list -> size);
}

void printList(List *list){
	if (emptyList(list)){
		printf(ANSI_COLOR_RED "Empty list!" ANSI_COLOR_RESET "\n");
	} else {
		Node *printNode;
		printNode = list -> first;
		while (printNode != NULL){ 
			printf("ID: %d \n", printNode -> id);
			printf("Tweet original: %s \n", printNode -> originalTweet);
			printf("Quantidade de palavras tweet original: %d\n", printNode -> countWordOriginalTweet);
			printf("Tweet filtrado: %s \n", printNode -> cleanTweet);
			printf("Quantidade de palavras tweet filtrado: %d\n\n", printNode -> countWordCleanTweet);
			printNode = printNode -> next;
		}
	}    
}

void cleanListSimiliarity(ListSimiliarity *list){
    NodeSimiliarity *temporary, *current;
    current = list -> first;
    while(current != NULL){
    	temporary = current -> next;
    	free(current);
    	current = temporary;
    }
    free(list);
}

void initializeListSimiliarity(ListSimiliarity *list){
	list -> first = NULL;
	list -> last = NULL;
	list -> size = 0;
}

bool emptyListSimiliarity(ListSimiliarity *list){
	if(list -> first == NULL)
		return true;
	return false;
}  

void insertTweetListSimiliarity(ListSimiliarity *list, int firstId, char* firstTweet, int secondId, char* secondTweet, int valueIntersection, int valueUnion, int valueSimiliarity){
	NodeSimiliarity *newNode = (NodeSimiliarity*) malloc(sizeof(NodeSimiliarity));
	newNode -> firstId = firstId;
	strcpy(newNode -> firstTweet, firstTweet);
	newNode -> secondId = secondId;
	strcpy(newNode -> secondTweet, secondTweet);
	newNode -> valueIntersection = valueIntersection;
	newNode -> valueUnion = valueUnion;
	newNode -> valueSimiliarity = valueSimiliarity;
	newNode -> next = NULL;

	if (emptyListSimiliarity(list)){
		list -> first = newNode;
		list -> last = newNode;
	} else {
		list -> last -> next = newNode;
		list -> last = newNode;
	}

	list -> size++;
}
 
int sizeListSimiliarity(ListSimiliarity *list){
	return (list -> size);
}

void printListSimiliarity(ListSimiliarity *list){
	if (emptyListSimiliarity(list)){
		printf(ANSI_COLOR_RED "Empty list!" ANSI_COLOR_RESET "\n");
	} else {
		NodeSimiliarity *printNode;
		printNode = list -> first;
		while (printNode != NULL){
			printf("First Id: %d\n", printNode -> firstId);
			printf("First Tweet: %s\n", printNode -> firstTweet);
			printf("Second Id: %d\n", printNode -> secondId);
			printf("Second Tweet: %s\n\n", printNode -> secondTweet);
			printNode = printNode -> next;
		}
	}    
}
