#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

int main (){//int argc, char* argv[]){
	char* theSecret = {"nomnom"};
	char theGuess[MAXSIZE];
	int numGuess = 0;
	while(true){
		getGuess(theGuess);
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
