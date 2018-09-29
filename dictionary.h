#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#define BIG_HASH_SIZE 20000
#define SMALL_HASH_SIZE 100

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
