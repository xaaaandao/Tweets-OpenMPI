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
	Node *newNode = (Node*) malloc(sizeof(Node));
	strcpy(newNode -> tweet, tweet);
	newNode -> next = NULL;

	if (emptyList(list)){
		list -> first = newNode;
		list -> last = newNode;
	} else {
		list -> last -> next = newNode;
		list -> last = newNode;
	}
	
	list -> size++;
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
			printf("Tweet: %s \n", printNode -> tweet);
			printNode = printNode -> next;
		}
	}    
}