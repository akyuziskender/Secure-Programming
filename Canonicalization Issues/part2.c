#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

char *strlow(char *str) {
	unsigned char *p = (unsigned char *)str;

	while (*p) {
		*p = tolower((unsigned char)*p);
		p++;
	}

	return str;
}

void readFile(const char *filename) {
	printf("Reading the file : %s\n", filename);
	FILE *filepointer;
	int c;
	filepointer = fopen(filename, "r");

	if (filepointer == NULL) {
		printf("Error: %s\n", strerror(errno));
		return;
	}

	while ((c = fgetc(filepointer)) != EOF) {
		printf("%c", (char)c);
	}

	fclose(filepointer);
	return;
}

int checkFile(const char *protectedfile, char *fn) {
	int validFile = 0;
	int inputlength = strlen(fn), protectedlength = strlen(protectedfile), i = 0;
	char *temp1, *temp2;
	temp1 = (char*)malloc((protectedlength + 1) * sizeof(char));	// allocating memory
	temp2 = (char*)malloc((protectedlength + 1) * sizeof(char));	// allocating memory

	strcpy(temp1, fn + inputlength - protectedlength);	// getting the last characters with the same size as protected file
	strcpy(temp2, protectedfile);	// copying string to a temp
	strlow(temp1);	// makin all characters lower case
	strlow(temp2);	// makin all characters lower case
	if (strcmp(temp1, temp2) == 0)	// comparing two strings
		validFile = 0;	// since they are the same, prevent user reaching the protected file
	else
		validFile = 1;	// it is okay, user can read the file
	free(temp1);	// freeing memory
	free(temp2);	// freeing memory
	return validFile;
}

void main(int argc, char *argv[]) {
	const char protectedfile[] = "mysecretfile.txt";

	char *fn = argv[1];

	if (checkFile(protectedfile, fn)) {
		readFile(fn);
	}
	else {
		printf("Access to the file specified is not permitted!\n");
		return;
	}
	return;
}
