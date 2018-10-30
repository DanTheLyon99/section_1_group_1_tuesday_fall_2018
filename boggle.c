#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include "board_generator.h"
#include "word_checker.h"
#include "scoreboard.h"

#define MAX_LINE 100

/**
 - set up board,
 - set up dictionary,
 **/
/*Author: Aaron McNeil
  Date: October 1, 2018
	Description: Increments the total score based on the word length*/
void incrementTotalScore(
    int *userScore,
		char *word);

/*Author: Aaron McNeil
  Date: October 1, 2018
  Description: Clears the game baord*/
void freeAndResetBoard(
   RolledDice** gameBoard,
   PresetDice* inputArrayOfDice)
{

    for ( int i = 0; i < 4; i++)
    {
    	/*Frees all the gameBoard Structs*/
	    free(gameBoard[i]);
    }

    /*Rolls dice*/
    rollDice(gameBoard, inputArrayOfDice);
}

/*Author: Aaron McNeil
  Date: October 1, 2018
  Description: Converts a String to all upper case using a double pointer*/
char *converttoupper(
    char **upper)
{
    /*Local variables*/
    char *upperDeref = *upper;

    /*Loops through the string*/
    for(int i = 0; upperDeref[i]; i++)
	{

    	/*Converts the char to upper case by calling the toupper function*/
	    upperDeref[i] = toupper(upperDeref[i]);
    }

	/*Return the new String*/
  	return upperDeref;
}

/*Author: Aaron McNeil
  Date: October 1, 2018
	Description: Converts a String to all upper case using an array*/
char *converttoupper2(
    char (*upper)[])
{
	  /*Local variables*/
    char *upperDeref = *upper;


	  for(int i = 0; upperDeref[i]; i++)
	  {

		  /*Converts the char to upper case by calling the toupper function*/
	      upperDeref[i] = toupper(upperDeref[i]);
	  }


	  return upperDeref;
}

/*Author: Aaron McNeil
  Date: October 1, 2018
	Description: Increments the total score based on the word length*/
void incrementTotalScore(
    int *userScore,
		char *word){

	 /*Local variables*/
   	 int wordLen = strlen(word);


	 fprintf(stdout, "word_len: %d\n", wordLen );

     /*Determine how much to increment the score based on the word length*/
	if(wordLen == 3 || wordLen == 4)
    {

		 *userScore+=1;

	}
    else if(wordLen == 5)
    {

		*userScore+=2;

	}
    else if(wordLen == 6)
    {

		*userScore+=3;

	}
    else if(wordLen == 7)
    {

		*userScore+=5;

	}
    else if(wordLen >= 8)
    {

		*userScore+=11;

	}

}


int main (int argc, char ** argv) {

    /*Variables*/
	int i, testPoints = 0;
    char inputWord[100];
	char originalInputWord[100];

	FILE *inputFP;
	char line [MAX_LINE];
	char *fileName =" ";

  /*variables*/
  FILE *testFileFp;
  char testLine [MAX_LINE];

  char **testBoard;
  int fileLineCounter = 1;
  int j;
  int begin = 0;


 	const char * DICTNAME = "EnglishWords.txt";
	DNode* checkEnglish;
	DNode* checkSubmitted;
	static DNode* englishDictionary [BIG_HASH_SIZE];
	static DNode* guessedWords [SMALL_HASH_SIZE];

	int currentScore = 0;
	int turnCount = 0;

	User* head = NULL;
	head = (User*)malloc(sizeof(User));

	PresetDice globalDice[16];
	RolledDice *gameBoard[4];

	FILE *outputFP;

    /*Check if the file can be opened*/
	if(!(inputFP = fopen ( DICTNAME , "r" )))
	{

        /*File can no be opened*/
        fprintf(stderr,"Could not open file \"%s\" for reading dictionary words\n", DICTNAME);

        return 1;
    }

    /*Loop through the file until the program reaches the end*/
	  while( fgets (line, MAX_LINE, inputFP)!=NULL )
	  {

            /*Add the 'null' character to the end of the word*/
		    line[strcspn(line, "\r\n")] = '\0';  //trim new line characters

			/*Convert word to upper case and add it to the dictionary*/
		    insert (englishDictionary, BIG_HASH_SIZE, converttoupper2(&line));

	  }

          /*Close the file*/
	  fclose (inputFP);


	  if (argc == 1)
	  {

	  	/*Start the game in normal mode*/
		fprintf(stdout, "playing in normal mode\n\n");

		system("clear");

		initializePresetDice(globalDice);

		rollDice(gameBoard, globalDice);

        /*Loop until turnCount is less than '0'*/
		while (turnCount >= 0)
	    {

			/*Save the original input word*/
			strcpy(originalInputWord, inputWord);

            /*Convert String to upper case*/
			converttoupper2(&inputWord);

            /*New variables*/
			char inputName[100];

            /*Check if the user wants to quit the game*/
            if (strcmp(originalInputWord, "q") == 0) {
       				// "q" is the input, print scoreboard and exit game
       				printScoreboard(head);
       				break;
       			}
       			// "n" is the input, adds user to/changes user in linked list and
       			// resets game
       			if (strcmp(originalInputWord, "n") == 0) {

       				printScoreboard(head);
       				fprintf(stdout, "Your current score: %d \n", currentScore);
       				fprintf(stdout, "What is your name? \n");
       				scanf("%s", inputName);

       				if (userIsInList(head, inputName) == 0){
       					addNode(head, inputName, currentScore);
       				}
       				else {
       					updateNodeWithName(head, inputName, currentScore);
       				}

       				currentScore = 0;

       				strcpy(inputWord, "");
              fprintf(stdout,"test\n");
       				freeAndResetBoard(gameBoard, globalDice);
       				turnCount = 0;
       				system("clear");
       				continue;
       			}

       			printGameBoard(gameBoard);

       			checkEnglish = lookup (englishDictionary, BIG_HASH_SIZE, inputWord);

       			if (checkEnglish != NULL) {
       				checkSubmitted = lookup (guessedWords, SMALL_HASH_SIZE, inputWord);

       				if (checkSubmitted == NULL) {
       					if(strlen(inputWord) > 2){
       						if(wordChecker(gameBoard, inputWord)){
       							insert (guessedWords, SMALL_HASH_SIZE, inputWord);
       							incrementTotalScore(&currentScore, inputWord);
       							fprintf (stdout, "Correct! You current score is now: %d \n", currentScore);

       						}else{
       							fprintf (stderr, "The submitted word: \'%s\'' does not abide game rules. Try again!\n", originalInputWord);
       						}
       					}else{
       						fprintf (stderr, "The submitted word: \'%s\'' must be at least 3 letters long. Try again!\n", originalInputWord);
       					}

       				}else{
       					fprintf (stderr, "You have already submitted the word: \'%s\'' Try again!\n", originalInputWord);
       				}

       		 	}else if (turnCount > 0){
       		 		fprintf (stderr, "Incorrect word: \'%s\' is not in the English Dictionary. Try again!\n", originalInputWord);
       			}
       			fprintf(stdout, "Submit a word you found:\n");
       	       	scanf("%s", inputWord);
       	        turnCount++;
       	        system("clear");
          		}
    /*freeing game board*/
    for( int i = 0; i < 4; i++){

        free(gameBoard[i]);
    }

        freeAll(head);
	  }

    /*in test mode with file*/
    else if (argc == 2) {

        fprintf(stdout, "playing in test mode with file: %s\n", fileName);



		/*read first line which is the board*/
		if(!(testFileFp = fopen ( fileName , "r" ))){

        fprintf(stderr,"Could not open test file \'%s\' for reading\n", fileName);
        return 1;

		}
    else if(!(outputFP = fopen("result.txt", "w"))){

        fprintf(stderr,"Could not open result file \'%s\' for writing\n", "result.txt");
        return 1;
		}

		while(fgets (testLine, MAX_LINE, testFileFp)!=NULL){
      /*trim new line characters*/
			testLine[strcspn(testLine, "\r\n")] = '\0';

    if(fileLineCounter == 1){
		    convertToBoard(testLine, &testBoard);

		/*for testing*/
    for (i = 0; i < 4; i++) {
       for (j = 0; j < 4; j++) {
			      if (j != 3){

                /*ptinting test board*/
                fprintf(stdout, "%c \t", testBoard[i][j]);
						}
              else{

                  /*printing test board*/
                  fprintf(stdout, "%c \n", testBoard[i][j]);

							}
        }
    }

    }

    else if(fileLineCounter >= 2){

        /*testing using checkEnglish*/
        for(char *p = strtok(testLine,","); p != NULL; p = strtok(NULL, ",")){

            checkEnglish = lookup (englishDictionary, BIG_HASH_SIZE, converttoupper(&p));

				    if(checkEnglish != NULL){

                checkSubmitted = lookup (guessedWords, SMALL_HASH_SIZE, p);

					  if(checkSubmitted == NULL){

                /*telling you correct then telling you the score*/
						if(testWordChecker(testBoard, p)){

                insert (guessedWords, SMALL_HASH_SIZE, p);
                incrementTotalScore(&testPoints, p);
                fprintf(stdout,"Correct! You total score is now: %d \n",testPoints );

						}
            else{

            if(begin == 0){

                fprintf(outputFP, "%s", p );
                begin++;
						}
            else{
								fprintf(outputFP, ",%s", p );
						}

                /*if and elses tell you if the submitted word is unable*/
								fprintf(stderr,"The submitted word: \'%s\'' does not abide game rules. Try again!\n", p);
						}

						}
            else{

            if(begin == 0){

                fprintf(outputFP, "%s", p );
								begin++;
						}

            else{

                fprintf(outputFP, ",%s", p );
						}
                /*if and elses tells you if you have submitted the word*/
                fprintf(stderr,"You have already submitted the word: \'%s\'' Try again!\n", p);
						}


				 	  }
            else{

            if(begin == 0){

                fprintf(outputFP, "%s", p );
						    begin++;
						}

            else{
							fprintf(outputFP, ",%s", p );
						}
            /*if and elses tell you the word is incorrect*/
				 		fprintf(stderr,"Incorrect word: \'%s\'' is not in the English Dictionary. Try again!\n", p);
					  }
        }
      }

        fileLineCounter++;
		}

    fprintf(outputFP, "\n");

    fprintf(outputFP, "%d\n", testPoints);
    /*close the testFileFp*/
		fclose (testFileFp);

		for ( i = 0; i < 4; i++) {
        free(testBoard[i]);
		}

    /*free testBoard*/
    free(testBoard);

    /*close outputFP*/
		fclose(outputFP);

  }

    freeDictionary(englishDictionary, BIG_HASH_SIZE);
    freeDictionary(guessedWords, SMALL_HASH_SIZE);

    return 0;
}
    /*************************END OF Zachery Abbas's CODE****************************/
