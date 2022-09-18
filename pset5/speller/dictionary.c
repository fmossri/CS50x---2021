make// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"



// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void free_node(node *n);

// Number of buckets in hash table
const unsigned int N = 17575;

// Hash table
node *table[N];

//Words counter
int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //hashes the word
    int index = hash(word);
    //goes to the index linked list
    node *n = table[index];

    //searches inside the linked list for the word; iterates trough the list until the word is found and returns true; if its not, returns false
    while (n != NULL)
    {
        //uses strcasecmp to avoid case differences
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        else
        {
            n = n->next;
        }
    }
    return false;
}

// Hashes word to a number, using the three first characters, lowercasing them if needed. goes from aaa on 0 to zzz on 17575
unsigned int hash(const char *word)
{
    //
    int hash_number;
    char lower[3];

    //special case for one letter words
    if (strlen(word) == 1)
    {
        lower[0] = tolower(word[0]);
        hash_number = (lower[0] - 97) * 676;
    }

    //special case for 2 letter words
    else if (strlen(word) == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            lower[i] = tolower(word[i]);
        }
        hash_number = ((lower[0] - 97) * 676) + ((lower[1] - 97) * 26);
    }

    //hashes bigger than 2 letter words
    else
    {
        for (int i = 0; i < 3; i++)
        {
            lower[i] = tolower(word[i]);
        }
        hash_number = ((lower[0] - 97) * 676) + ((lower[1] - 97) * 26) + (lower[2] - 97);
    }
    return hash_number;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //opens file and checks for NULL
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    //sets an array of size LENGTH + 1 to temporarily store each word at a time;
    char new_word[LENGTH + 1];

    //searches for a string in a properly prepared dictionary file, and copies into new_word;
    while (fscanf(file, "%s", new_word) != EOF)
    {
        //allocates sizeof(node) bytes into a node for each word;
        node *n = malloc(sizeof(node));
        //checks for memory space
        if (n == NULL)
        {
            printf("Not enough memory\n");
            fclose(file);
            return false;
        }
        //copies the word from new_word into the node;
        strcpy(n->word, new_word);

        //sets the node's pointer to NULL;
        n->next = NULL;

        //hashes the word stored into the node;
        int index = hash(n->word);

        //checks wether the node's word is the first word at table[index];
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        //if the node's word isn't the first word stored into the linked list, sets the node's pointer to the previously stored word, and then replaces the old node for the new one;
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        //adds 1 to the counter for each new word;
        counter++;

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //sets the counter to the table size
    counter = N - 1;

    //iterates trough the hash table's linked lists and recursively frees all nodes, starting from the last;
    while (counter > 0)
    {
        //if there's no linked list at the table[index], skips it and subtracts 1 from counter;
        if (table[counter] == NULL)
        {
            counter--;
        }
        //if there's only one node in the linked list, frees it and subtracts from counter;
        else if (table[counter]->next == NULL)
        {
            free(table[counter]);
            counter--;
        }

        //if there's more than one node inside the linked list, calls free_node recursive function to free them all; subtracts from counter;
        else
        {
            free_node(table[counter]->next);
            free(table[counter]);
            counter--;
        }
    }
    return true;
}

//simple recursive function to free all nodes;
void free_node(node *n)
{
    //if its the last one, frees it;
    if (n->next == NULL)
    {
        free(n);
    }
    //if not, calls the function to the next node;
    else
    {
        free_node(n->next);
        free(n);
    }
}