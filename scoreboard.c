#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "scoreboard.h"

/*
 * Finds and returns a pointer to the User in the linked list beginning with
 * head which has the name name_to_find. If such a User is not in the Linked
 * List, it will return NULL. Helper function to increment_score.
 */
User* find_user_with_name(User* head, char* name_to_find) {
	if (head == NULL) {
		return head;
	}
	User *current = head ;
	while (current != NULL) {
		if (strcmp(current->name, name_to_find) == 0) {
			return current;
		}
		current = (current)->next;
	}
	return NULL;
}

/* frees every element of the linked list */
void free_all(User* head) {
	if (head -> next == NULL) {
		free(head);
	}
	else {
		User *current = head->next;
		User *previous = head;
		while (current != NULL) {
			free(previous);
			previous = current;
			current = (current)->next;
		}
	}
}

User* get_user_at_index(User* head, int index) {
	if (head == NULL) {
		return NULL;
	}
	User *current = head;
	int count = 0;
	while (current != NULL) {
		if (count == index + 1) {
			return current;
		}
		current = (current)->next;
		count++;
	}
	return NULL;
}

int get_index_of_user_with_name(User* head, char* name_to_find) {
	if (head == NULL && head->name != name_to_find) {
		return -1;
	}
	User *current = head;
	int count = 0;
	while (current != NULL) {
		if (strcmp(current->name, name_to_find)) {
			return count;
		}
		current = (current)->next;
		count++;
	}
	return -1;
}

/*
 * Finds whether or not a an existing user is already in the list. Of they are,
 * returns 1. If not, returns 0.
 */
int user_is_in_list(User* head, char* name_to_find) {
	User *current = head;
	while (current != NULL) {
		if (strcmp(current->name, name_to_find) == 0) {
			return 1;
		}
		current = (current)->next;
	}
	return 0;
}

int get_length(User* head) {
	if (head == NULL) {
		return 0;
	}
	User *current = head;
	int count = 0;
	while (current != NULL) {
		count++;
		if (current->next == NULL) {
			return count;
		}
		current = (current)->next;
	}
	return 0;
}

/*
 * Helper function. Finds the last node in the linked list and returns it.
 * Returns NULL if called with an empty head, although such a case is not used
 * in the main function add_node.
 */
User* get_last_node(User *head) {
	if (head == NULL) {
		return head;
	}
	User *current = head;
	while (current != NULL) {
		if (current->next == NULL) {
			return current;
		}
		current = (current)->next;
	}
	return NULL;
}

void print_scoreboard(User *head) {
        fprintf(stdout, "\n");
        fprintf(stdout, "---- SCORE BOARD ---- \n");
	if (head -> next != NULL) {
		User *current = head -> next;
		while (current != NULL) {
			printf("\n");
			printf("Player name: %s \n", current->name);
			printf("High score: %d \n", current->max_score);
			printf("Games played: %d \n", current->total_games);
			printf("Total score: %d \n", current->total_score);
			printf("\n");
			printf("--------------------- \n");

			if (current->next == NULL) {
				break;
			}
			current = (current)->next;
		}
	}
}

void add_node(User *head, char* name, int max_score) {
	User *user_ptr;
	if (head != NULL) {
		 user_ptr = malloc(sizeof(struct user));
	}
	strcpy(user_ptr->name, name);
	user_ptr->max_score = max_score;
	user_ptr->total_games = 1;
	user_ptr->total_score = max_score;
	user_ptr->next = NULL;

	if (head == NULL) {
		head = user_ptr;
	}
	else {
		get_last_node(head)->next = user_ptr;
	}
}

void update_node_with_name(User *head, char* name, int current_score) {
	if (user_is_in_list(head, name) == 1) {
		User *user_ptr = find_user_with_name(head, name);
		if (current_score > (user_ptr->max_score)) {
			user_ptr->max_score = current_score;
		}
		user_ptr->total_games += 1;
		user_ptr->total_score += current_score;
	}
}
