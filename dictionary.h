
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

//This is a dictionary node which stores a key
//used to lookup and store data in the dictionary 
typedef struct d_node {
	char* key;
    struct d_node *next;
}DNode;

//makes a copy of the input string
char * copystr (const char *);
//form hash value for string s
//this produces a starting value in the dictionary array
unsigned hash(const char *s);
//uses the hashvalue to find if the pointer is the same as the key
DNode * lookup (DNode ** dictionary, int hash_size, const char *key);
//inserts data into the DNode
DNode * insert (DNode ** dictionary, int hash_size, const char * key);
//Frees all the data that was stored in the DNode struct
void free_dictionary (DNode ** dictionary, int hash_size);

#endif
