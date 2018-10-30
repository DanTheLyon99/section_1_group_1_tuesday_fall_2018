#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdlib.h>

/* Author: Daniel Lyon 
   Date: 29/10/2018
   Description: Contains all function protocols
   for the scoreboard.c program and the user struct
*/

/*This is a user node to keep track of all the user's data in the list*/
typedef struct user
{
	char name[ 100 ];
	int maxScore;
	int totalGames;
	int totalScore;
	struct user *next;
} User;

 /* Finds and returns a pointer to the User in the linked list beginning with
    head which has the name nameToFind. If such a User is not in the Linked
    List, it will return NULL. Helper function to incrementScore*/
User* findUserWithName( User* head, char* nameToFind );

/*returns the value of the user at the index if the head is not NULL*/
User* getUserAtIndex( User* head, int index );

/*returns the value of the user using a name pointer if the head is not NULL*/
int getIndexOfUserWithName( User* head, char* nameToFind );

/*returns the length of the user list*/
int getLength( User* head );

 /* Helper function. Finds the last node in the linked list and returns it.
    Returns NULL if called with an empty head, although such a case is not used
    in the main function addNode*/
User* getLastNode( User *head );

/*prints the values in the user struct to display a scoreboard*/
void printScoreboard( User *head );

/*frees every element of the linked list*/
void freeAll( User* head );

/*ads a node to the linked list*/
void addNode( User *head, char* name, int maxScore );

 /*Finds whether or not a an existing user is already in the list. Of they are,
   returns 1. If not, returns 0*/
int userIsInList( User* head, char* nameToFind );

/*adds value to the user score based on the name pointer*/
void updateNodeWithName( User *head, char* name, int currentScore );

#endif
