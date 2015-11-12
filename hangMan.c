#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAXSIZE 35
#define MAXFILE 150
/*
 *program uses two strings to track game. One stores the value fo the secret wor
 *the other string will store the current guessed word including _ _ .
 *At each turn every character in the secret string will be compared to the guess
 *if there is a match, the curGuessString[i] = secretString[i]
 *if there is no match, the draw hangman method will be called
 *the numGuesses is only incremented with incorrect guesses. 
 *
 */
int printGallows(int);
int getGuess(char*);
int checkGuess(char*, char*, char*);
int setTo_(char*, int);
int getLine(FILE*, char*);
int getFilePath(char*);


int main (){//int argc, char* argv[]){
	char theSecret[MAXSIZE];
	char theGuess[MAXSIZE];
	char knownStr[MAXSIZE];
	char filePath[MAXFILE];
	int numGuess = 0;
	FILE* filePointer = NULL;
	/*char* homePath = getenv("HOME");
	char filePath[MAXFILE];
	strcpy(filePath,homePath);
	strcat(filePath,"/words");
	printf("filePath is %s\n", filePath);
		
	fiilePointer = fopen("/home/sbartholomew/words", "r");
*/
	getFilePath(filePath);
	filePointer = fopen(filePath, "r");
	if (filePointer == NULL){
		printf("ERROR: words file does not exist in home directory\n");
		exit(0);
	}
	getLine(filePointer, theSecret);
	int size=(int)strlen(theSecret)-1;
	int wordLen = size < MAXSIZE ? size : MAXSIZE;
	setTo_(knownStr, wordLen);
	while(true){
		printf("%d  %s: ",numGuess, knownStr);
		getGuess(theGuess);
		// check guess regardless, need to modify to treat string and char different
		if(!checkGuess(theSecret, knownStr, theGuess)){
			numGuess++;
		}

		if (!strcmp(theGuess,theSecret) || !strcmp(knownStr, theSecret)){
			printf("You win! You had %d misses\n", numGuess);
			break;
		}
		if (numGuess < 7) {
			printGallows(numGuess);
		} else{
			printf("  %s\n", theSecret);
			printf("You lose\n");
			break;
		}
	}
	fclose(filePointer);





	
	
}

int getFilePath(char* filePath){
	char* homePath = getenv("HOME");
        strcpy(filePath,homePath);
        strcat(filePath,"/words");
        printf("filePath is %s\n", filePath);
       	return 0;
}

int checkGuess(char* secretVal, char* knowVals, char* userGuess){
	int temp = strlen(secretVal)-1;
	int count = 0;
	for(; temp >=0; temp--){
		if(secretVal[temp] == userGuess[0]){
			knowVals[temp] = userGuess[0];
			count++;
		}
	}
	return count;
}

int getGuess(char* userGuess){
	//printf("Enter a Guess:");
	char temp[MAXSIZE];
	fgets(temp,(MAXSIZE), stdin);
	if(((int)strlen(temp)) == MAXSIZE-1){
		int i = '0';
		while((i = fgetc(stdin)) != EOF && i != '\n'){
			//No body to loop
		}
		return 1;
		//goto youSuckTryAgain 
	}
	strncpy(userGuess, temp, MAXSIZE);
	return 0;
}


int setTo_(char* unitializedStr, int sizeOfStr){
	if(unitializedStr == NULL){
		return 1;
	}
	int i;
	for(i = 0; i < sizeOfStr; i++){
		unitializedStr[i] = '_';
	}
	unitializedStr[i] = '\0';
	return 0;
}


/*
 *Method to  open a file and choose a random line from the file as the word
 *takes parameter char* and copies chosen line to char* using strncpy 
 *if file DNE return error code
 */

/*
 *print hangMan(numInvalidGuess, *currentGuessString)
 *big series of case statements and ascii art to "draw" the hangman.
 *
 */
int printGallows(int numGuess){// char* guessString){
	switch(numGuess){
		case 0: 
		        printf(" ___________\n");
		        printf(" |         }\n");
		        printf(" |         \n");
		        printf(" |         \n");
		        printf(" |         \n");
		        printf("_|______________\n");
		break;     	 
    		case 1:
			printf(" ___________\n");
		        printf(" |         }\n");
		        printf(" |         0\n");
			printf(" |         \n");
			printf(" |         \n");
        		printf("_|______________\n");     
		break;
		case 2:
                        printf(" ___________\n");
                        printf(" |         }\n");
                        printf(" |         0\n");
                        printf(" |         | \n");
                        printf(" |         \n");
                        printf("_|______________\n");
                break;
		case 3:
                        printf(" ___________\n");
                        printf(" |         }\n");
                        printf(" |        \\0\n");
                        printf(" |         | \n");
                        printf(" |         \n");
                        printf("_|______________\n");
                break;
		case 4:
                        printf(" ___________\n");
                        printf(" |         }\n");
                        printf(" |        \\0/\n");
                        printf(" |         | \n");
                        printf(" |         \n");
                        printf("_|______________\n");
                break;
		case 5:
                        printf(" ___________\n");
                        printf(" |         }\n");
                        printf(" |        \\0/\n");
                        printf(" |         | \n");
                        printf(" |        / \n");
                        printf("_|______________\n");
                break;
		case 6:
                        printf(" ___________\n");
                        printf(" |         }\n");
                        printf(" |        \\0/ \n");
                        printf(" |         |\n");
                        printf(" |        / \\ \n");
                        printf("_|______________\n");
                break;
	}
	return 1;    
}

int getLine(FILE *theFile, char* keepLine ){
	srand(time(NULL));
	char tempLine[MAXSIZE];
	int count = 0;
	if(theFile ==NULL){
		printf("didn't open the file");
		return 1;
	}
	while (fgets(tempLine, MAXSIZE, theFile) != NULL){
		// need to ensure that fgets cleared the line buffer
		// nest all in if (strnlen(tempLine)<MAXSIZE) 
		count ++;
		// need to check and see if tempLine is a valid line.
		if ((rand() % count == 0)){
			strcpy(keepLine, tempLine);
		}
	}
	return 0;
}
