#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdlib.h>

/* Author: Daniel Lyon 
   Date: 10/09/2018
   Description: Contains all function protocols
   for the scoreboard.c program and the user struct
*/

//This is a user node to keep track of all the user's data in the list
typedef struct user{
	char name[100];
	int max_score;
	int total_games;
	int total_score;
	struct user *next;

} User;

 // Finds and returns a pointer to the User in the linked list beginning with
 // head which has the name name_to_find. If such a User is not in the Linked
 // List, it will return NULL. Helper function to increment_score.
User* find_user_with_name(User* head, char* name_to_find);
//returns the value of the user at the index if the head is not NULL
User* get_user_at_index(User* head, int index);
//returns the value of the user using a name pointer if the head is not NULL
int get_index_of_user_with_name(User* head, char* name_to_find);
//returns the length of the user list
int get_length(User* head);
 // Helper function. Finds the last node in the linked list and returns it.
 //Returns NULL if called with an empty head, although such a case is not used
 // in the main function add_node.
User* get_last_node(User *head);
//prints the values in the user struct to display a scoreboard
void print_scoreboard(User *head);
// frees every element of the linked list 
void free_all(User* head);
//ads a node to the linked list
void add_node(User *head, char* name, int max_score);

 // Finds whether or not a an existing user is already in the list. Of they are,
 // returns 1. If not, returns 0.
int user_is_in_list(User* head, char* name_to_find);
//adds value to the user score based on the name pointer
void update_node_with_name(User *head, char* name, int current_score);

#endif
