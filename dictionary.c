#include <string.h>
#include <stdio.h>
#include "dictionary.h"

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Form hash value for string word. This produces a starting value
                in the dictionary array.*/
unsigned hash( const char * word )
{
    unsigned hashValue;
    
    for ( hashValue = 0; *word != '\0'; word++ )
    {
        
        hashValue = *word + 31 * hashValue;
        
    }
    
    return hashValue;
}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Search linked list for given key. If found, return the DNode
                pointer. If not, return NULL.*/
DNode * lookup ( DNode ** dictionary, int hashSize, const char * key )
{
    DNode * nodePointer;
    unsigned int hashValue = hash( key );
    
    for ( nodePointer = dictionary [ hashValue % hashSize ];
          nodePointer != NULL;
		  nodePointer = nodePointer->next )
    {
        
        if ( strcmp ( key, nodePointer->key ) == 0 )
        {
            
            return nodePointer;
            
        }
    
    }
    return NULL;
}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Inserts a new DNode into the linked list if the key does not
                already exist and if the node and key are both not NULL.*/
DNode * insert ( DNode ** dictionary, int hashSize, const char * key )
{
    unsigned int hashValue;
    DNode * nodePointer;
    
    if ( ( nodePointer = lookup ( dictionary, hashSize, key ) ) == NULL )
    {
        
        nodePointer = ( DNode * ) malloc ( sizeof ( *nodePointer ) );
        
        if ( nodePointer == NULL ||
             ( nodePointer->key = copyString ( key ) ) == NULL )
        {
            
            return NULL;
            
        }
        
        hashValue = hash ( key ) % hashSize;
        nodePointer->next = dictionary [ hashValue ];
        dictionary [ hashValue ] = nodePointer;
    
    }
    
    return nodePointer;
}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Frees every element of the linked list.*/
void freeDictionary ( DNode ** dictionary, int hashSize )
{
    int counter;
    
    for ( counter = 0; counter < hashSize; counter++ )
    {
        
        if ( dictionary [ counter ] != NULL )
        {   
            
            DNode * head = dictionary [ counter ];
            DNode * current = head;
            
            while (current != NULL)
            {
                
                DNode * tempNode = current;
                current = current->next;
                free ( tempNode );
            
            }
            
            dictionary[ counter ] = NULL;
            
        }
    
    }

}

/* Author: Carlo Pagcanlungan
   Date: 10/09/2018
   Description: Makes and returns a duplicate of the given string.*/
char * copyString ( const char * originalString )
{
    char * copiedString;
    int length = strlen ( originalString );
	copiedString = ( char * ) malloc ( length + 1 );
	
    if ( copiedString != NULL )
    {
        
        strncpy ( copiedString, originalString, length );
    }
	
    copiedString [ length ] = '\0';
	return copiedString;
}
