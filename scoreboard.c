#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "scoreboard.h"

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Finds and returns a pointer to the User in the linked list
                beginning with head which has the name name_to_find. If such a
                User is not in the Linked List, it will return NULL. Helper
                function to increment_score.*/
User * findUserWithName ( User * head, char * nameToFind )
{
    User * current = head;

    if ( head == NULL )
    {

        return current;

    }

    while ( current != NULL )
    {

        if ( strcmp ( current->name, nameToFind ) == 0 )
        {

            return current;

        }

        current = ( current )->next;

    }

    return NULL;
}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Frees every element of the linked list.*/
void freeAll ( User * head )
{
    if ( head->next == NULL )
    {

        free( head );

    }
    else
    {

        User * current = head->next;
        User * previous = head;

        while ( current != NULL )
        {

            free ( previous );
            previous = current;
            current = ( current )->next;

        }

    }

}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Finds and returns a pointer to the User in the linked list
                beginning with head at the given index. If such a User is not
                in the Linked List, it will return NULL.*/
User * getUserAtIndex ( User * head, int index )
{
    User * current = head;
    int count = 0;

    if ( head == NULL )
    {

        return current;

    }

    while ( current != NULL )
    {

        if ( count == index + 1 )
        {

            return current;

        }

        current = ( current )->next;
        count++;

    }

    return NULL;
}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Finds and returns the index of the User in the linked list
                beginning with head which has the name name_to_find. If such a
                User is not in the Linked List, it will return -1.*/
int getIndexOfUserWithName ( User * head, char * nameToFind )
{
    User * current = head;
    int count = 0;

    if ( head == NULL && head->name != nameToFind )
    {

        return -1;

    }

    while ( current != NULL )
    {

        if ( strcmp ( current->name, nameToFind ) )
        {

            return count;

        }

        current = ( current )->next;
        count++;

    }

    return -1;
}

 /* Author: Carlo Pagcanlungan
    Date: 10/09/2018
    Description: Finds whether or not an existing user is already in the list.
                 If they are, returns 1. If not, returns 0.*/
int userIsInList ( User * head, char * nameToFind )
{
    User * current = head;

    while ( current != NULL )
    {

        if ( strcmp ( current->name, nameToFind ) == 0 )
        {

            return 1;

        }

        current = ( current )->next;

    }

    return 0;
}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Finds and returns the length of the linked list.*/
int getLength ( User * head )
{
    User * current = head;
    int count = 0;

    if ( head == NULL )
    {

        return count;

    }

    while (current != NULL)
    {

        count++;

        if ( current->next == NULL )
        {

            return count;

        }

        current = (current)->next;

    }

    return 0;
}

 /* Author: Carlo Pagcanlungan
    Date: 10/09/2018
    Description: Helper function. Finds the last node in the linked list and
                 returns it. Returns NULL if called with an empty head,
                 although such a case is not used in the main function
                 add_node.*/
User * getLastNode ( User * head )
{
    User * current = head;

    if ( head == NULL )
    {

        return current;

    }

    while ( current != NULL )
    {

        if ( current->next == NULL )
        {

            return current;

        }

        current = (current)->next;

    }

    return NULL;
}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Displays a visual table of the scoreboard.*/
void printScoreboard ( User * head )
{
    fprintf ( stdout, "\n" );
    fprintf ( stdout, "---- SCORE BOARD ---- \n" );

    if ( head->next != NULL ) {

        User * current = head->next;

        while ( current != NULL ) {

            printf ( "\n" );
            printf ( "Player name: %s \n", current->name );
            printf ( "High score: %d \n", current->maxScore );
            printf ( "Games played: %d \n", current->totalGames );
            printf ( "Total score: %d \n", current->totalScore );
            printf ( "\n" );
            printf ( "--------------------- \n" );

            if ( current->next == NULL )
            {

                break;

            }

            current = ( current )->next;

        }

    }

}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Adds a User pointer node onto the linked list.*/
void addNode ( User * head, char * name, int maxScore ) {
	  User * userPointer;
	  if ( head != NULL ) {
		    userPointer = malloc ( sizeof ( struct user ) );
	  }
	  strcpy ( userPointer->name, name );
	  userPointer->maxScore = maxScore;
	  userPointer->totalGames = 1;
	  userPointer->totalScore = maxScore;
	  userPointer->next = NULL;

	  if (head == NULL) {
		    head = userPointer;
	  }
	  else {
		    getLastNode ( head )->next = userPointer;
	  }
}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: If a User pointer in the linked list has the given name, then
                the values of the User is changed and updated.*/
void updateNodeWithName ( User * head, char * name, int currentScore ) {
	  if (userIsInList ( head, name ) == 1 ) {
		    User * userPointer = findUserWithName ( head, name );
		    if ( currentScore > ( userPointer->maxScore ) ) {
			      userPointer->maxScore = currentScore;
		    }
		    userPointer->totalGames += 1;
		    userPointer->totalScore += currentScore;
	  }
}
