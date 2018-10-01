#include "board_generator.h"

int alreadyShuffled( RolledDice die );

/* Author: William Crocket
   Date: 09/27/2018
   Description: Initializes the dice in the list of pre-set dice. Call once at program start.
*/
void initializePresetDice( PresetDice* inputArrayOfDice )
{
	int i = 0;

	for ( i = 0; i < 16; i++ ) {
		inputArrayOfDice[ i ].position = 0;
	}

	// initializes individual potential chars for each dice
	inputArrayOfDice[ 0 ].configurations = "RIFOBX";
	inputArrayOfDice[ 1 ].configurations = "IFEHEY";
	inputArrayOfDice[ 2 ].configurations = "DENOWS";
	inputArrayOfDice[ 3 ].configurations = "UTOKND";
	inputArrayOfDice[ 4 ].configurations = "HMSRAO";
	inputArrayOfDice[ 5 ].configurations = "LUPETS";
	inputArrayOfDice[ 6 ].configurations = "ACITOA";
	inputArrayOfDice[ 7 ].configurations = "YLGKUE";
	inputArrayOfDice[ 8 ].configurations = "QBMJOA";
	inputArrayOfDice[ 9 ].configurations = "EHISPN";
	inputArrayOfDice[ 10 ].configurations = "VETIGN";
	inputArrayOfDice[ 11 ].configurations = "BALIYT";
	inputArrayOfDice[ 12 ].configurations = "EZAVND";
	inputArrayOfDice[ 13 ].configurations = "RALESC";
	inputArrayOfDice[ 14 ].configurations = "UWILRG";
	inputArrayOfDice[ 15 ].configurations = "PACEMD";
}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Rolls the dice to be used at the start of each game. Puts the rolled dice in
   game_dice. Does not shuffle the dice. Helper function.
*/
void rollButNotShuffleDice( RolledDice* gameDice, PresetDice* inputArrayOfDice )
{
	int i = 0;
	int face = 0;

	/* Randomize the seed */
	srand( time( NULL ) );

	for ( i = 0; i < 16; i++ ) {
		face = rand() % 6;
		gameDice[ i ].character = inputArrayOfDice[ i ].configurations[ face ];
	}
}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Shuffles an array of rolled dice. Helper function.
*/
void shuffleRolledDicePositions( RolledDice* gameDice )
{
	/* newGameDice is a temporary array to hold the shuffled dice */
	RolledDice newGameDice[ 16 ];
	int i = 0;
    int randomIndex = 0;

	for ( i = 0; i < 16; i++ ) {

		/* Randomize the seed */
		srand( time( NULL ) );

		/* Loop until an index is generated such that the corresponding die
		   has not been shuffled yet */
		do {
			randomIndex = rand() % 16;
		} while ( alreadyShuffled( gameDice[ randomIndex ] ) );

		newGameDice[ i ] = gameDice[ randomIndex ];
		gameDice[ randomIndex ].position = 1;
	}
    
	/* This loop copies all of the shuffled dice from the temporary newGameDice array
	   back to the original gameDice array */
	for ( i = 0; i < 16; i++ ) {
		gameDice[ i ] = newGameDice[ i ];
		gameDice[ i ].position = i + 1;
	}
}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Returns 1 if the given die has already been shuffled into the game board.
   Helper function.
*/
int alreadyShuffled( RolledDice die )
{
	if ( die.position ) {
		return 1;
	}
	else {
		return 0;
	}
}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Rolls the dice to be used at the start of the game and shuffles them, putting
   the dice into the 2D array gameBoard. Call once at the start of every game.
*/
void rollDice( RolledDice** gameBoard, PresetDice* inputArrayOfDice )
{
	// temporary array of structs to contain adjusted 1D array of dice.
	RolledDice adjustedDiceArray[ 16 ];
	int i = 0;
	int j = 0;

	gameBoard[ 0 ] = malloc( sizeof( RolledDice ) * 4 );
	gameBoard[ 1 ] = malloc( sizeof( RolledDice ) * 4 );
	gameBoard[ 2 ] = malloc( sizeof( RolledDice ) * 4 );
	gameBoard[ 3 ] = malloc( sizeof( RolledDice ) * 4 );

	rollButNotShuffleDice( adjustedDiceArray, inputArrayOfDice );
	shuffleRolledDicePositions( adjustedDiceArray );

	for ( i = 0; i < 4; i++ ) {
		for ( j = 0; j < 4; j++ ) {
			gameBoard[ i ][ j ] = adjustedDiceArray[ ( i * 4 ) + j ];
		}
	}
}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Prints a visualization of the input array of rolled_dice.
*/
void printGameBoard( RolledDice** gameBoard )
{
	int i = 0;
	int j = 0;

	for ( i = 0; i < 4; i++ ) {
		for ( j = 0; j < 4; j++ ) {
			if ( j != 3 ) {
				printf( "%c \t", gameBoard[ i ][ j ].character );
			}
			else {
				printf( "%c \n", gameBoard[ i ][ j ].character );
			}
		}
	}
}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Converts board from a string version to 2D array. Used in test mode
*/
void convertToBoard( char* letters, char*** board )
{
	int i = 0;
	int j = 0;
	int t = 0;

	/* allocate space for boggle board on heap in order to access it in main. */
	*board = malloc( sizeof( char * ) * 4 );
	char** board_deref = *board;

	board_deref[ 0 ] = malloc( sizeof( char ) * 4 );
	board_deref[ 1 ] = malloc( sizeof( char ) * 4 );
	board_deref[ 2 ] = malloc( sizeof( char ) * 4 );
	board_deref[ 3 ] = malloc( sizeof( char ) * 4 );

	for ( i = 0; i < 4; i++ ) {
		for ( j = 0; j < 4; j++ ) {
			board_deref[ i ][ j ] = letters[ t ];
			t++;
		}
	}
}