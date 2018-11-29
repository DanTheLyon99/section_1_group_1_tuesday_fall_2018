#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct presetDice
{
    char *configurations;
    int position;
} PresetDice;

/*The rolled dice which do not keep their values between games*/
typedef struct rolledDice
{
    char character;
    int position;
} RolledDice;

void rollButNotShuffleDice( RolledDice * gameDice, PresetDice * inputArrayOfDice );
void shuffleRolledDicePositions( RolledDice * gameDice );
void rollDice( RolledDice ** gameBoard, PresetDice * inputArrayOfDice );
void initializePresetDice( PresetDice * inputArrayOfDice );

/* Functions */
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

void rollButNotShuffleDice( RolledDice * gameDice, PresetDice * inputArrayOfDice )
{
    srand( time( NULL ) );

    int index = 0;
    int face = 0;

    /* Randomize the seed */

    for ( index = 0; index < 16; index++ )
    {

        face = rand( ) % 6;
        gameDice[ index ].character = inputArrayOfDice[ index ].configurations[ face ];
    }

}

void shuffleRolledDicePositions( RolledDice * gameDice )
{
    srand( time( NULL ) );

    /* newGameDice is a temporary array to hold the shuffled dice */
    RolledDice newGameDice[ 16 ];
    int index = 0;
    int randomIndex = 0;

    for ( index = 0; index < 16; index++ )
    {
        /* Randomize the seed */

        /* Loop until an row is generated such that the corresponding die
        has not been shuffled yet */
        while(gameDice[randomIndex].position==-1)
        {
            randomIndex = (int) (rand( ) % 16);
        }

        newGameDice[ index ] = gameDice[ randomIndex ];
        gameDice[ randomIndex ].position = -1;



    }
    for (index=0;index<16;index++){

        gameDice[index]=newGameDice[index];
        gameDice[index].position= index+1;

    }
}

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

            gameBoard[ row ][ column ] = adjustedDiceArray[  row * 4 + column ];

        }

    }

}

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

    char *converttoupper( char **upper )
    {
        /*Local variables*/
        char *upperDeref = *upper;

        /*Loops through the string*/

        for(int i = 0; upperDeref[i]; i++)
        {

            /*Converts the char to upper case by calling the toupper function*/
            upperDeref[i] = toupper(upperDeref[i]);
        }
        printf("\n");

        /*Return the new String*/
        return upperDeref;
    }


    void incrementTotalScore( int *userScore, char *word ){

        /*Local variables*/
        int wordLen = strlen(word);

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


    /* Main Program */
    int main () {

        char *upperTestOne = NULL;
        char *upperTestTwo = strdup ("liam neeson");
        char *upperTestThree = strdup ("ß");
        char *upperTestFour = strdup ("");

        int userScore = 0;

        /* null test case will crash program*/

        /* printf("Before Function Call: %s\n",upperTestOne);*/
        /* upperTestOne = converttoupper(&upperTestOne);*/
        /* printf("After Function Call: %s\n",upperTestOne);*/

        printf("Before Function Call: %s\n",upperTestTwo);
        upperTestTwo = converttoupper(&upperTestTwo);
        printf("After Function Call: %s\n\n",upperTestTwo);

        printf("Before Function Call: %s\n",upperTestThree);
        upperTestThree = converttoupper(&upperTestThree);
        printf("After Function Call: %s\n\n",upperTestThree);

        printf("Before Function Call: %s\n",upperTestFour);
        upperTestFour = converttoupper(&upperTestFour);
        printf("After Function Call: %s\n\n",upperTestFour);


        printf("incrementTotalScore tests:\n\n");

        printf("String: 'abc' Expected Value: 1\nBefore Function Call: %d\n", userScore);
        incrementTotalScore(&userScore, "abc");
        printf("After Function Call: %d\n\n", userScore);
        userScore=0;

        printf("String: 'abcd' Expected Value: 1\nBefore Function Call: %d\n", userScore);
        incrementTotalScore(&userScore, "abcd");
        printf("After Function Call: %d\n\n", userScore);
        userScore=0;

        printf("String: 'abcde' Expected Value: 2\nBefore Function Call: %d\n", userScore);
        incrementTotalScore(&userScore, "abcde");
        printf("After Function Call: %d\n\n", userScore);
        userScore=0;

        printf("String: 'abcdef' Expected Value: 3\nBefore Function Call: %d\n", userScore);
        printf("After Function Call: %d\n\n", userScore);
        incrementTotalScore(&userScore, "abcdef");
        userScore=0;

        printf("String: 'abcdefg' Expected Value: 5\nBefore Function Call: %d\n", userScore);
        incrementTotalScore(&userScore, "abcdefg");
        printf("After Function Call: %d\n\n", userScore);
        userScore=0;

        printf("String: 'abcdefgh' Expected Value: 11\nBefore Function Call: %d\n", userScore);
        incrementTotalScore(&userScore, "abcdefgh");
        printf("After Function Call: %d\n\n", userScore);
        userScore=0;

        printf("String: 'abcdefghij' Expected Value: 7\nBefore Function Call: %d\n", userScore);
        incrementTotalScore(&userScore, "abcdefghij");
        printf("After Function Call: %d\n\n", userScore);
        userScore=0;

        printf("String: 'ab' Expected Value: 0\nBefore Function Call: %d\n", userScore);
        incrementTotalScore(&userScore, "ab");
        printf("After Function Call: %d\n\n", userScore);
        userScore=0;

        PresetDice globalDice[16];
        RolledDice *gameBoard[4];

        initializePresetDice(globalDice);
        rollDice(gameBoard, globalDice);

        printGameBoard(gameBoard);


        freeAndResetBoard(gameBoard, globalDice);


        initializePresetDice(globalDice);
        rollDice(gameBoard, globalDice);
        printGameBoard(gameBoard);



        return 0;
    }
