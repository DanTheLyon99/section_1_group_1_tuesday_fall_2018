#include <stdio.h>
#include <string.h>
#include "word_checker.h"
#include <ctype.h>

/*
Author: Satjeevan Riar (1018052)
Date: 29th September 2018
Description: Returns the particular letter on the gameboard given the location
*/
char getLetter( int i, int j, RolledDice **gameBoard )
{

    return gameBoard[ i ][ j ].character;

}

/*
Author: Satjeevan Riar (1018052)
Date: 29th September 2018
Description: Checks if the rules of the boggle game have been been broken or followed correctly
and returns 1 or 0 to indicate this
*/
int abidesRules( int i, int j, char *word, RolledDice **gameBoard, int subLength, int **visited )
{

    char findLetter;
    int adjacentCell;
    int answer;
    int result;

    // right, digUpRight, up, digUpLeft, left, digDownLeft, down, digDownRight
    int allX[ ] = { 0, -1, -1, -1, 0, 1, 1, 1 };
    int allY[ ] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    findLetter = word[ subLength + 1 ];
    answer = ( subLength == ( strlen( word ) - 1 ) );
    result = 0;
    if( answer )
    {

        return 1;

    }

    for( adjacentCell = 0; adjacentCell < 8; adjacentCell++ )
    {

        int newX = i + allX[ adjacentCell ];
        int newY = j + allY[ adjacentCell ];

        if( ( newX >= 0 ) &&
        ( newX < 4 ) &&
        ( newY >= 0 ) &&
        ( newY < 4 ) &&
        toupper( findLetter ) == getLetter( newX, newY, gameBoard ) && !visited[ newX ][ newY ] )
        {

            visited[ newX ][ newY ] = 1;
            ++subLength;
            result = abidesRules( newX, newY, word, gameBoard, subLength, visited );
            if( result )
            {

                return 1;

            }
            else
            {
                --subLength;
            }
        }
    }

    return 0;

}

/*
Author: Satjeevan Riar (1018052)
Date: 29th September 2018
Description: Checks for matching word entered by the user and if it is correct
by using the abidesrules function above
*/
int wordChecker( RolledDice **gameBoard, char *word )
{
    int m;
    int n;
    int **visited;

    visited = malloc( sizeof( int * ) * 4 );
    for( int i = 0; i < 4; i++ )
    {
        visited[ i ] = malloc( sizeof( int ) * 4 );
    }

    for( m = 0; m < 4; m++ )
    {
        for( n = 0; n < 4; n++ )
        {

            if( m == 0 && n == 0 )
            {
                visited[ m ][ n ] = 1;
            }
            else
            {
                visited[ m ][ n ] = 0;
            }
        }
    }
    for ( int row = 0; row < 4; row++ )
    {
        for ( int column = 0; column < 4; column++ )
        {

            if( abidesRules( row, column, word, gameBoard, 0, visited ) )
            {
                for( int i = 0; i < 4; i++ )
                {
                    free( visited[ i ] );
                }

                return 1;

            }
        }
    }

    free( visited[ 0 ] );
    free( visited[ 1 ] );
    free( visited[ 2 ] );
    free( visited[ 3 ] );

    return 0;

}

/*
Author: Satjeevan Riar (1018052)
Date: 29th September 2018
Description: Tests that the correct letter is recieved by the program using this function
*/
char testGetLetter( int i, int j, char **boggle )
{
    return boggle[ i ][ j ];
}

/*
Author: Satjeevan Riar (1018052)
Date: 29th September 2018
Description: Checks if the rules of the boggle game have been been broken or followed correctly
and returns 1 or 0 to indicate this
*/
int testAbideRules( int i, int j, char *word, char **gameBoard, int subLength, int **visited )
{
    // use subLength as index to see what letter to find
    char currentLetter;
    char findLetter;
    int answer;
    int adjacentCell;
    int result;

    int allX[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
    int allY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    currentLetter = word[ subLength ];
    answer = ( subLength == ( strlen( word ) - 1 ) );
    result = 0;
    if( answer )
    {

        return 1;

    }

    if( toupper( currentLetter ) == 'Q' &&
    toupper( word[ subLength + 2 ] ) == testGetLetter( i, j, gameBoard ) )
    {
        findLetter = word[ subLength + 3 ];
        subLength = subLength + 2;
        currentLetter = word[ subLength ];
    }
    else
    {
        findLetter = word[ subLength + 1 ];
    }

    for( adjacentCell = 0; adjacentCell < 8; adjacentCell++ )
    {
        int newX = i + allX[ adjacentCell ];
        int newY = j + allY[ adjacentCell ];

        if( ( newX >= 0 ) &&
        ( newX < 4 ) &&
        ( newY >= 0 ) &&
        ( newY < 4 ) &&

        toupper( findLetter ) == testGetLetter( newX, newY, gameBoard ) && !visited[ newX ][ newY ])
        {
            visited[ newX ][ newY ] = 1;
            ++subLength;
            result = testAbideRules( newX, newY, word, gameBoard, subLength, visited );
            if( result )
            {

                return 1;

            }
            else
            {
                --subLength;
            }
        }
    }

    return 0;

}

/*
Author: Jing Xuan Long (1022621)
Date: 29th September 2018
Description: Checks for matching word
*/
int testWordChecker( char **boggle, char *word )
{

    int m;
    int n;
    int ** visited;

    visited = malloc( sizeof( int * ) * 4 );
    visited[ 0 ] = malloc( sizeof( int ) * 4 );
    visited[ 1 ] = malloc( sizeof( int ) * 4 );
    visited[ 2 ] = malloc( sizeof( int ) * 4 );
    visited[ 3 ] = malloc( sizeof( int ) * 4 );

    for ( m = 0; m < 4; m++ )
    {

        for ( n = 0; n < 4; n++ )
        {

            if ( m == 0 && n == 0 )
            {

                visited[ m ][ n ] = 1;

            }
            else
            {

                visited[ m ][ n ] = 0;

            }

        }

    }

    for ( int row = 0; row < 4; row++ )
    {

        for ( int column = 0; column < 4; column++ )
        {

            if ( testAbideRules( row, column, word, boggle, 0, visited ) )
            {

                free( visited[ 0 ] );
                free( visited[ 1 ] );
                free( visited[ 2 ] );
                free( visited[ 3 ] );

                return 1;

            }

        }

    }

    free( visited[ 0 ] );
    free( visited[ 1 ] );
    free( visited[ 2 ] );
    free( visited[ 3 ] );

    return 0;

}

/*
Author: Jing Xuan Long (1022621)
Date: 29th September 2018
Description: Checks for matching word
*/
int HCWordChecker(char boggle[ ][ 4 ], char *word)
{

    int m;
    int n;
    int ** visited;

    visited = malloc( sizeof( int * ) * 4 );
    visited[ 0 ] = malloc( sizeof( int ) * 4 );
    visited[ 1 ] = malloc( sizeof( int ) * 4 );
    visited[ 2 ] = malloc( sizeof( int ) * 4 );
    visited[ 3 ] = malloc( sizeof( int ) * 4 );

    for ( m = 0; m < 4; m++ )
    {

        for ( n = 0; n < 4; n++ )
        {

            if ( m == 0 && n == 0 )
            {

                visited[ m ][ n ] = 1;

            }
            else
            {

                visited[ m ][ n ] = 0;

            }

        }

    }

    for ( int row = 0; row < 4; row++ )
    {

        for ( int column = 0; column < 4; column++ )
        {

            if ( HCAbidesRules( row, column, word, boggle, 0, visited ) )
            {

                free( visited[ 0 ] );
                free( visited[ 1 ] );
                free( visited[ 2 ] );
                free( visited[ 3 ] );

                return 1;

            }

        }

    }

    free( visited[ 0 ] );
    free( visited[ 1 ] );
    free( visited[ 2 ] );
    free( visited[ 3 ] );

    return 0;

}

/*
Author: Jing Xuan Long (1022621)
Date: 29th September 2018
Description: Checks if word matches criteria
*/
int HCAbidesRules( int i, int j, char *word, char boggle[][ 4 ], int subLength, int **visited )
{

    int adjacentCell;
    int allX[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
    int allY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

    char findLetter;
    char currentLetter = word[ subLength ];

    if ( subLength == ( strlen( word ) - 1 ) )
    {

        return 1;

    }

    if ( toupper( currentLetter ) == 'Q' && toupper( word[ subLength + 2 ] ) == HCGetLetter( i, j, boggle ) )
    {

        findLetter = word[ subLength + 3 ];
        subLength++;
        subLength++;
        currentLetter = word[ subLength ];

    }
    else
    {

        findLetter = word[ subLength + 1 ];

    }

    int result = 0;

    for ( adjacentCell = 0; adjacentCell < 8; adjacentCell++ )
    {

        int newX = i + allX[ adjacentCell ];
        int newY = j + allY[ adjacentCell ];

        if ( ( newX >= 0 ) &&
        ( newX < 4 ) &&
        ( newY >=0 ) &&
        ( newY < 4 ) &&
        toupper( findLetter ) == HCGetLetter( newX, newY, boggle ) &&
        !visited[ newX ][ newY ])
        {

            visited[newX][newY] = 1;
            ++subLength;
            result = HCAbidesRules( newX, newY, word, boggle, subLength, visited );

            if ( result )
            {

                return 1;

            }
            else
            {

                --subLength;

            }

        }

    }

    return 0;

}

/*
Author: Jing Xuan Long (1022621)
Date: 29th September 2018
Description: Gets letter
*/
char HCGetLetter( int i, int j, char boggle[][ 4 ] )
{

    return boggle[ i ][ j ];

}
