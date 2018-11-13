#include "board_generator.h"

int alreadyShuffled( RolledDice die );

/* Author: William Crocket
   Date: 09/27/2018
   Description: Initializes the dice in the list of pre-set dice.
   Call once at program start. */
void initializePresetDice( PresetDice * inputArrayOfDice )
{

    int index = 0;

    for ( index = 0; index < 16; index++ )
    {

        inputArrayOfDice[ index ].position = 0;

    }

    /* initializes individual potential chars for each dice */
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
   Description: Rolls the dice to be used at the start of each game.
   Puts the rolled dice in game_dice. Does not shuffle the dice.
   Helper function. */
void rollButNotShuffleDice( RolledDice * gameDice, PresetDice * inputArrayOfDice )
{

    int index = 0;
    int face = 0;

    /* Randomize the seed */
    srand( time( NULL ) );

    for ( index = 0; index < 16; index++ )
    {

        face = rand( ) % 6;
        gameDice[ index ].character = inputArrayOfDice[ index ].configurations[ face ];

    }

}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Shuffles an array of rolled dice. Helper function. */
void shuffleRolledDicePositions( RolledDice * gameDice )
{

    /* newGameDice is a temporary array to hold the shuffled dice */
    RolledDice newGameDice[ 16 ];
    int index = 0;
    int randomIndex = 0;

    for ( index = 0; index < 16; index++ )
    {

        /* Randomize the seed */
        srand( time( NULL ) );

        /* Loop until an row is generated such that the corresponding die
           has not been shuffled yet */
        while( gameDice[ randomIndex ].position == -1 )
        {

            randomIndex = ( int ) ( rand( ) % 16 );
        }

        newGameDice[ index ] = gameDice[ randomIndex ];
        gameDice[ randomIndex ].position = -1;

    }

    /* This loop copies all of the shuffled dice from the temporary newGameDice
       array back to the original gameDice array */
    for ( index = 0; index < 16; index++ )
    {

        gameDice[ index ] = newGameDice[ index ];
        gameDice[ index ].position = index + 1;

    }

}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Returns 1 if the given die has already been shuffled
   into the game board.
   Helper function. */
int alreadyShuffled( RolledDice die )
{

    if ( die.position )
    {

        return 1;

    }
    else
    {

        return 0;

    }

}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Rolls the dice to be used at the start of the game and
   shuffles them, putting the dice into the 2D array gameBoard.
   Call once at the start of every game. */
void rollDice( RolledDice ** gameBoard, PresetDice * inputArrayOfDice )
{

    /* temporary array of structs to contain adjusted 1D array of dice. */
    RolledDice adjustedDiceArray[ 16 ];
    int row = 0;
    int column = 0;

    gameBoard[ 0 ] = malloc( sizeof( RolledDice ) * 4 );
    gameBoard[ 1 ] = malloc( sizeof( RolledDice ) * 4 );
    gameBoard[ 2 ] = malloc( sizeof( RolledDice ) * 4 );
    gameBoard[ 3 ] = malloc( sizeof( RolledDice ) * 4 );

    rollButNotShuffleDice( adjustedDiceArray, inputArrayOfDice );

    shuffleRolledDicePositions( adjustedDiceArray );

    for ( row = 0;  row < 4; row++ )
    {

        for ( column = 0; column < 4; column++ )
        {

            gameBoard[ row ][ column ] = adjustedDiceArray[ ( row * 4 ) + column ];

        }

    }

}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Prints a visualization of the input array of rolledDice. */
void printGameBoard( RolledDice ** gameBoard )
{

    int row = 0;
    int column = 0;

    for ( row = 0; row < 4; row++ )
    {

        for ( column = 0; column < 4; column++ )
        {

            if ( column != 3 )
            {

                printf( "%c \t", gameBoard[ row ][ column ].character );

            }
            else
            {

                printf( "%c \n", gameBoard[ row ][ column ].character );

            }

        }

    }

}

/* Author: William Crocket
   Date: 09/27/2018
   Description: Converts board from a string version to 2D array.
   Used in test mode */
void convertToBoard( char * letters, char *** board )
{

    int row = 0;
    int column = 0;
    int positionInString = 0;

    /* Allocate space for boggle board on heap in order to access it in main. */
    *board = malloc( sizeof( char * ) * 4 );
    char ** boardDeref = *board;
    boardDeref[ 0 ] = malloc( sizeof( char ) * 4 );
    boardDeref[ 1 ] = malloc( sizeof( char ) * 4 );
    boardDeref[ 2 ] = malloc( sizeof( char ) * 4 );
    boardDeref[ 3 ] = malloc( sizeof( char ) * 4 );

    for ( row = 0; row < 4; row++ )
    {

        for ( column = 0; column < 4; column++ )
        {

            boardDeref[ row ][ column ] = letters[ positionInString ];
            positionInString++;

        }

    }

}
