#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAXSIZE 35
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


int main (){//int argc, char* argv[]){
	char* theSecret = {"nomanom"};
	char theGuess[MAXSIZE];
	int size=(int)strlen(theSecret);
	int wordLen = size < MAXSIZE ? size : MAXSIZE;
	char knownStr[MAXSIZE];
	setTo_(knownStr, wordLen);
	int numGuess = 0;	

	while(true){
		getGuess(theGuess);
		// check guess regardless, need to modify to treat string and char different
		checkGuess(theSecret, knownStr, theGuess);
		printf("knownStr is %s\n", knownStr);
		if (*theGuess == *theSecret){
			printf("you win in %d guesses\n", numGuess);
			break;
		}
		numGuess++;
		if (numGuess < 7) {
			printGallows(numGuess);
		} else{
			printf("he died\n");
			break;
		}
	}
	// call openFile() if return == error --- exit with error message
	/*if (argc >= 1){
		int j = atoi(argv[1]);
		printGallows(j);
	}
	*/
	
}

int checkGuess(char* secretVal, char* knowVals, char* userGuess){
	int temp = strlen(secretVal)-1;
	for(; temp >=0; temp--){
		if(secretVal[temp] == userGuess[0]){
			knowVals[temp] = userGuess[0];
		}
	}
	return 0;
}

int getGuess(char* userGuess){
	printf("Enter a Guess:");
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
	printf("here");
	if(unitializedStr == NULL){// || sizeOfStr == NULL){
		return 1;
	}
	printf("didn't fail %d\n", sizeOfStr);
	int i;
	for(i = 0; i < sizeOfStr; i++){
		printf("size is %d is is %d\n", sizeOfStr, i);
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
	// input verification -- make sure theFile is not NULL
	srand(time(NULL));
	char tempLine[MAXSIZE];
	int count = 0;
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
