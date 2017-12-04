#include <stdio.h>
#include "manipulateString.h"

void convertToLower(char *string){
	int i = 0;
	while(string[i] != '\0'){
		if(string[i] != '-'){	
			if(string[i] > 64 && string[i] < 91)
				string[i] = string[i] + 32;	
		}
		i++;
	}
}

int stringEquals(char* x, char* y){
	int i = 0, result, equal = 1;
	while(equal && x[i] != '\0' && y[i] != '\0'){
		if(x[i] != y[i])
			equal = 0;
		i++;
	}
	if(x[i - 1] == '\0' && y[i - 1] == '\0')
		result = 0;	
	else
		result = x[i - 1] - y[i - 1];	
	return result;
}