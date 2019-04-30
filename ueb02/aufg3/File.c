#include<stdio.h>
#include <sys/stat.h>

int main(int numberOfArguments, char* arguments[]) {
	int i;
	printf("Anzahl Argumente: %d\n", numberOfArguments);	
	for(i=0; i < numberOfArguments; i++) {
		printf("arg[%d]: %s\n", i, arguments[i]);
	}
	return 0;
}
