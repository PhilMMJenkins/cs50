// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table, maz size for word * max letter value (26)
const unsigned int N = 1170;

//dictionary count
unsigned int D = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int t = hash(word);
    node *cursor = table[t];
        
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        if (word[i] >= 65 && word[i] <= 90) //upper case
        {
            hash += word[i] - 64;
        }
        else if (word[i] >= 97 && word[i] <= 122) //lower case
        {
            hash += word[i] - 96;
        }
    }
    return hash;
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *ptr = fopen(dictionary, "r");
    if (ptr == NULL)
    {
        return false;
    }
    
    //read strings from the file one at a time into tmp char array
    char tmp[LENGTH + 1];
    
    while (fscanf(ptr, "%s", tmp) != EOF)
    {
        //create a new node for each word
        node *w = malloc(sizeof(node));
        if (w == NULL)
        {
            return false;
        }
        
        strcpy(w->word, tmp);
        w->next = NULL;
        
        //hash the word
        unsigned int t = hash(w->word);
        
        //insert the word into a linked list at that location
        if (table[t] == NULL)
        {
            table[t] = w;
            D++;
        }
        
        else if (table[t] != NULL)
        {
            w->next = table[t];
            table[t] = w;
            D++;
        }
    }
    fclose(ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return D;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *cursor = table[i];
            node *tmp = cursor;
            while (cursor != NULL)
            {
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
                
            }
        }
    }
    
    return true;
}