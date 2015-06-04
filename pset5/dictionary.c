/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.  Lightnin' fast!  
 * Disclaimer: Implemented portion of hash idea from this site: 
 * http://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
 * Received some guidance from online research of reference.cs50 site.
 * Seems to all be working correctly - run time between .06 and .08 seconds.
 * Also doesn't seem to have collisions... I hope that's true!
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

// set hash table max size - lower size, faster run time
#define SIZE 150000

// create linked list nodes with room for null character
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// create hash table and discover size of dictionary
node* hasht[SIZE] = {NULL};
int dict_size = 0;

// create hashing function
int hash(const char* word)
{
    unsigned int hash = 0;
    int j;
    // make sure the element we're on isn't '\0'
    for (int i = 0; word[i] != '\0'; i++)
    {
        // check if the word meets our typical alpha constraints
        if (isalpha(word[i]))
        {
            j = word[i] - 'a' + 2;
        }
        // otherwise, utilize hash with bitmove
        else
        {
            j = 27;
        }
        hash = ((hash << 2) + j) % SIZE;
    }
    return hash;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // convert word to lower case, thereby becoming case insensitive
    char mklower[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        mklower[i] = tolower(word[i]);
    }
    mklower[len] = '\0';
    // hash the word to create its index
    int index = hash(mklower);
    // if the index is empty, return false
    if (hasht[index] == NULL)
    {
        return false;
    }
    // use cursor to traverse nodes
    node* cursor = hasht[index];
    // if index is not empty, traverse and compare strings
    while (cursor != NULL)
    {
        if (strcmp(mklower, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the designated dictionary file pointer
    FILE* fp = fopen(dictionary, "r");
    // filter for errors
    if (fp == NULL)
    {
        printf("The dictionary failed to load correctly.");
        return false;
    }
    // generate array
    char word[LENGTH + 1];
    // if not at end of file, scan in and store each word
    while (fscanf(fp, "%s\n", word) != EOF)
    {
        dict_size++;
        node* word_store = malloc(sizeof(node));
        strcpy(word_store->word, word);
        // hash word to appropriate index
        int index = hash(word);
        // if index is impty, perform insert
        if (hasht[index] == NULL)
        {
            hasht[index] = word_store;
            word_store->next = NULL;
        }
        // if index is in use, perform append
        else
        {
            word_store->next = hasht[index];
            hasht[index] = word_store;
        }
    }
    // close the dictionary file
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dict_size > 0)
    {
        return dict_size;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    int index = 0;
    // check every word until you hit the end of the file
    while (index < SIZE)
    {
        if (hasht[index] == NULL)
        {
            index++;
        }
        // free memory whenever applicable situation is encountered
        else
        {
            while (hasht[index] != NULL)
            {
                node* cursor = hasht[index];
                hasht[index] = cursor->next;
                free(cursor);
            }
            index++;
        }
    }
    return true;
}
