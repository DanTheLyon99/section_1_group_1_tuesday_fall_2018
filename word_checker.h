#include <string.h>
#include "board_generator.h"
#include <stdlib.h>

/* Author: Daniel Lyon 
   Date: 29/10/2018
   Description: Contains all function protocols
   for the word_checker.c program
*/

int wordChecker( struct rolledDice **gameBoard, char *word );
int abidesRules( int i, int j, char *word, struct rolledDice** gameBoard, int subLen, int **visited );

/* returns the gameboard character at the specefied index */
char getLetter( int i, int j, struct rolledDice **gameBoard );

int testWordChecker( char **boggle, char *word );
int testAbidesRules( int i, int j, char *word, char **gameBoard, int subLen, int **visited );
char testGetLetter( int i, int j, char **boggle );

int HCWordChecker( char boggle[ ][ 4 ], char *word );
char HCGetLetter( int i, int j, char boggle[ ][ 4 ] );
int HCAbidesRules( int i, int j, char *word, char boggle[ ][ 4 ], int subLen, int **visited );



