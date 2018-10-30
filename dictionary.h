
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#define BIG_HASH_SIZE 20000
#define SMALL_HASH_SIZE 100

/* Author: Daniel Lyon 
   Date: 10/09/2018
   Description: Contains all function protocols, constants
   and structs for the dictionary.c program
*/

/*This is a dictionary node which stores a key
used to lookup and store data in the dictionary */
typedef struct d_node {
	char* key;
    struct d_node *next;
}DNode;


char * copystr (const char *);
unsigned hash(const char *s);

DNode * lookup (DNode ** dictionary, int hash_size, const char *key);

DNode * insert (DNode ** dictionary, int hash_size, const char * key);

void free_dictionary (DNode ** dictionary, int hash_size);

#endif
