#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#define MAXSIZE 36
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
int getFilePath(char*, char*);
int getStats(FILE*, char*);

int main (int argc, char* argv[]){
	char theSecret[MAXSIZE], theGuess[MAXSIZE], knownStr[MAXSIZE], temp[MAXSIZE], filePath[MAXFILE], statsPath[MAXFILE], theStats[MAXFILE];
	strcpy(temp, "words");
	int numGuess = 0;
	FILE *filePointer = NULL, *statsPointer = NULL;
	if(argc == 2){
		getFilePath(filePath, argv[1]);
	} else{
		getFilePath(filePath, temp);
	}
	filePointer = fopen(filePath, "r");
	int games, wins, losses;
	float average;
	strcpy(temp, ".hangman");
	getFilePath(statsPath, temp);
	statsPointer = fopen(statsPath, "a+");
	getStats(statsPointer, theStats);
	char* remainder;
	games = strtol(theStats, &remainder,10);
	strcpy(theStats, remainder);
	wins = strtol(theStats, &remainder,10);
	strcpy(theStats, remainder);
	losses = games - wins;
	average = strtof(theStats, &remainder);
	char winString[5], losString[7];
	wins == 1 ? strcpy(winString, "Win") : strcpy(winString, "Wins");
	losses == 1 ? strcpy(losString, "Loss") : strcpy(losString, "Losses");
	printf("Game %d  %s: %d %s: %d Average:%.1f\n", games, winString, wins, losString, losses, average); 
	if (!filePointer || !statsPointer){
                printf("ERROR: file does not exist in home directory\n");
                exit(0);
        }
	getLine(filePointer, theSecret);
	int size=(int)strlen(theSecret)-1;
	int wordLen = size < MAXSIZE ? size : MAXSIZE;
	setTo_(knownStr, wordLen);
	while(true){
		printf("%d  %s: ",numGuess, knownStr);
		getGuess(theGuess);

		int check = checkGuess(theSecret, knownStr, theGuess);
		if(!check){
			numGuess++;
		}else if (check == 1){
			char misses[7];
			numGuess == 1 ? strcpy(misses, "miss") : strcpy(misses, "misses");
			printf("   %s\n", theSecret);
			printf("You win! You had %d %s.\n", numGuess, misses);
			wins++;
			games++;
			average = (average*(games-1) + numGuess)/games;
			break;
		}
		printGallows(numGuess);
		if( numGuess == 6){
			printf("  %s\n", theSecret);
			printf("You lose\n");
			losses++;
			games++;
			average = (average*(games-1) + numGuess)/games;
			break;
		}
	}
	fprintf(statsPointer, "\n%d %d %f", games, wins, average);
	fclose(filePointer);
	fclose(statsPointer);
}

int getFilePath(char* filePath, char* fileName){
	char* homePath = getenv("HOME");
        strcpy(filePath,homePath);
        if(!fileName || !filePath){
		return 1;
	}
	strcat(filePath, "/");
	strcat(filePath, fileName);
        printf("filePath is %s\n", filePath);
       	return 0;
}

int checkGuess(char* secretVal, char* knowVals, char* userGuess){
	if(userGuess[0] == '\n'){
		return 0;
	}
	int i = strlen(secretVal)-1;
	int temp;
	int count = 0;
	if(!strcmp(secretVal, userGuess)){
		return 1;
	}
	else if(strlen(userGuess) < 3){
		for(temp = i; temp >=0; temp--){
			if(secretVal[temp] == userGuess[0]){
				knowVals[temp] = userGuess[0];
				count++;
			}
		}
	}
	if(count>0){
		for(temp = i-1; temp >=0; --temp){
			if(knowVals[temp] != secretVal[temp]){
				break;
			}
		}
		printf("%d\n", temp);
		if(temp == -1){
			return 1;
		}
		return 2;
	}
	return 0;
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
	int i = strlen(temp);
        for(; i>= 0; i--){
        	temp[i] = tolower(temp[i]);
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
 *print hangMan(numInvalidGuess, *currentGuessString)
 *big series of case statements and ascii art to "draw" the hangman.
 *
 */
int printGallows(int numGuess){
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


/*
 *Method to  open a file and choose a random line from the file as the word
 *takes parameter char* and copies chosen line to char* using strncpy 
 *if file DNE return error code
 */


int getLine(FILE *theFile, char* keepLine){
	srand(time(NULL));
	char tempLine[MAXSIZE];
	int count = 0;
	if(theFile ==NULL){
		printf("ERROR: File does not exist!\n");
		return 1;
	}
	while (fgets(tempLine, MAXSIZE, theFile) != NULL){
		bool isValid = true;
		count ++;
		if ((rand() % count == 0)){
			int i = strlen(tempLine);
			for(; i>= 0; i--){
				tempLine[i] = tolower(tempLine[i]);
				if(tempLine[i] == ' '){
					isValid = false;
					count--;
				}
			}
			if(isValid){
				strcpy(keepLine, tempLine);
			}
		}
	}
	return 0;
}


int getStats(FILE *theFile, char* keepLine){
        char tempLine[MAXSIZE];
        if(theFile ==NULL){
                printf("ERROR: File does not exist!\n");
                return 1;
        }
        while (fgets(tempLine, MAXSIZE, theFile) != NULL){
		strcpy(keepLine, tempLine);
	}
	return 0;
}


