
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#define BIG_HASH_SIZE 20000
#define SMALL_HASH_SIZE 100

/* Author: Daniel Lyon 
   Date: 29/10/2018
   Description: Contains all function protocols, constants
   and structs for the dictionary.c program
*/

/*This is a dictionary node which stores a key
  used to lookup and store data in the dictionary*/
typedef struct dNode 
{
    char* key;
    struct dNode *next;
} DNode;

/*makes a copy of the input string*/
char * copyString( const char * );

/*form hash value for string s
  this produces a starting value in the dictionary array*/
unsigned hash( const char *s );

/*uses the hashvalue to find if the pointer is the same as the key*/
DNode * lookup( DNode ** dictionary, int hashSize, const char *key );

/*inserts data into the DNode*/
DNode * insert( DNode ** dictionary, int hashSize, const char * key );

/*Frees all the data that was stored in the DNode struct*/
void freeDictionary( DNode ** dictionary, int hashSize );

#endif
