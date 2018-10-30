#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdlib.h>

/* Author: Daniel Lyon 
   Date: 10/09/2018
   Description: Contains all function protocols
   for the scoreboard.c program and the user struct
*/

//This is a user node to keep track of all the user's data
typedef struct user{
	char name[100];
	int max_score;
	int total_games;
	int total_score;
	struct user *next;

} User;

User* find_user_with_name(User* head, char* name_to_find);

User* get_user_at_index(User* head, int index);

int get_index_of_user_with_name(User* head, char* name_to_find);

int get_length(User* head);

User* get_last_node(User *head);

void print_scoreboard(User *head);

void free_all(User* head);
void add_node(User *head, char* name, int max_score);

int user_is_in_list(User* head, char* name_to_find);

void update_node_with_name(User *head, char* name, int current_score);

#endif
