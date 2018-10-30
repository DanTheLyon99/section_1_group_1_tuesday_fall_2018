#include <stdio.h>
#include <string.h>
#include "word_checker.h"
#include <ctype.h>

/*
Author: Satjeevan Riar (1018052)
Date: 29th September 2018
Description: Returns the particular letter on the gameboard given the location
*/
char getLetter( int i, int j, struct RolledDice **gameBoard )
{
    return gameBoard[ i ][ j ].character;
}

/*
Author: Satjeevan Riar (1018052)
Date:
Description:
*/
int abidesRules( int i, int j, char *word, struct RolledDice **gameBoard, int subLength, int **visited )
{
    char currentLetter;
    char findLetter;
    int adjacentCell;
    int answer;
    int result;
    int newX;
    int newY;
    // right, digUpRight, up, digUpLeft, left, digDownLeft, down, digDownRight
    int allX[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
    int allY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    currentLetter = word[ subLength ];
    findLetter = word[subLength + 1];
    answer = ( subLength == ( strlen( word ) - 1 ) );
    result = 0;
    if( answer ){
        return 1;
    }
    for( adjacentCell = 0; adjacentCell < 8; adjacentCell++ ){
        int newX = i + allX[ adjacentCell ];
        int newY = j + allY[ adjacentCell ];
        if( ( newX >= 0 ) &&
        ( newX < 4 ) &&
        ( newY >= 0 ) &&
        ( newY < 4 ) &&
        toupper( findLetter ) == getLetter( newX, newY, gameBoard ) && !visited[ newX ][ newY ] ){
            visited[ newX ][ newY ] = 1;
            ++subLength;
            result = abidesRules( newX, newY, word, gameBoard, subLength, visited );
            if( result ){
                return 1;
            }
            else{
                --subLength;
            }
        }
    }
    return 0;
}

/*
Author: Satjeevan Riar (1018052)
Date:
Description:
*/
int wordChecker( struct RolledDice **gameBoard, char *word )
{
    int row;
    int letter;
    int column;
    int i;
    int m;
    int n;
    int **visited;
    visited = malloc( sizeof( int * ) * 4 );
    for( int i = 0; i < 4; i++ ){
        visited[ i ] = malloc( sizeof( int ) * 4 );
    }
    for( m = 0; m < 4; m++ ){
        for( n = 0; n < 4; n++ ){

            if( m == 0 && n == 0 ){
                visited[ m ][ n ] = 1;
            }
            else{
                visited[ m ][ n ] = 0;
            }
        }
    }
    for ( int row = 0; row < 4; row++ ) {
        for ( int column = 0; column < 4; column++ ) {
            if( abidesRules( row, column, word, gameBoard, 0, visited ) ){
                for( int i = 0; i < 4; i++ ){
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
Date:
Description:
*/
char testGetLetter( int i, int j, char **boggle )
{
    return boggle[ i ][ j ];
}

/*
Author: Satjeevan Riar (1018052)
Date:
Description:
*/
int testAbideRules( int i, int j, char *word, char **gameBoard, int subLength, int **visited )
{
    // use subLength as index to see what letter to find
    char currentLetter;
    char findLetter;
    int answer;
    int adjacentCell;
    int newX;
    int newY;
    int result;
    int allX[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
    int allY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    currentLetter = word[ subLength ];
    answer = ( subLength == ( strlen( word ) - 1 ) );
    result = 0;
    if( answer ){
        return 1;
    }
    if( toupper( currentLetter ) == 'Q' &&
    toupper( word[ subLength + 2 ] ) == testGetLetter( i, j, gameBoard ) ){
        findLetter = word[ subLength + 3 ];
        subLength = subLength + 2;
        currentLetter = word[ subLength ];
    }
    else{
        findLetter = word[ subLength + 1 ];
    }
    for( adjacentCell = 0; adjacentCell < 8; adjacentCell++ ){
        int newX = i + allX[ adjacentCell ];
        int newY = j + allY[ adjacentCell ];
        if( ( newX >= 0 ) &&
        ( newX < 4 ) &&
        ( newY >= 0 ) &&
        ( newY < 4 ) &&
        toupper( findLetter ) == testGetLetter( newX, newY, gameBoard ) && !visited[ newX ][ newY ]){
            visited[ newX ][ newY ] = 1;
            ++subLength;
            result = testAbideRules( newX, newY, word, gameBoard, subLength, visited );
            if( result ){
                return 1;
            }
            else{
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
int test_word_checker( char **boggle, char *word ){
    
    int row;
    int letter;
    int column;
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
Description:
*/
int hc_word_checker(char boggle[ ][ 4 ], char *word){
    
    int row;
    int letter;
    int column;
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
            
            if ( hc_abides_rules( row, column, word, boggle, 0, visited ) )
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
Date:
Description:
*/
int hc_abides_rules( int i, int j, char *word, char boggle[][ 4 ], int subLength, int **visited )
{
    
    int adjacentCell;
    int allX[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
    int allY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    int newX;
    int newY;
    char findLetter;
    char currentLetter = word[ subLength ];
    int answer = ( subLength == ( strlen( word ) - 1 ) );
    
    if ( subLength == ( strlen( word ) - 1 ) )
    {
    
        return 1;
    
    }
    
    if ( toupper( currentLetter ) == 'Q' && toupper( word[ subLength + 2 ] ) == hc_get_letter( i, j, boggle ) )
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
        toupper( findLetter ) == hc_get_letter( newX, newY, boggle ) &&
        !visited[ newX ][ newY ])
        {
            
            visited[newX][newY] = 1;
            ++subLength;
            result = hc_abides_rules( newX, newY, word, boggle, subLength, visited );
            
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
Date:
Description:
*/
char hc_get_letter( int i, int j, char boggle[][ 4 ] ){
    
    return boggle[ i ][ j ];

}
