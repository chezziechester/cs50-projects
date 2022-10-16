// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 738;

// Hash table
node *table[N];

//Count for number of words in dictionary
unsigned int count = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    //store lowercase word
    char lowerWord[strlen(word)];
    for (int i = 0; i < strlen(word) + 1; i++)
    {
        lowerWord[i] = tolower(word[i]);
    }

    //if the string begins with both alphabetical characters
    if (lowerWord[1] >= 97 && lowerWord[1] <= 122)
    {
        //subtract by value of 'a' + 'a'
        return (lowerWord[0] + lowerWord[1]) - 194;
    }
    //if the second character is an apostrophe
    else if (lowerWord[1] == 39)
    {
        //lowest case, 'a' + '\'' = 136, 566 + 136 = 702
        return 566 + (lowerWord[0] + lowerWord[1]);
    }
    //if the second character is blank
    else
    {
        //store blanks in second part
        return 676 + (lowerWord[0] - 97);
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //create temporary node to iterate through linked list
    node *tmp;
    tmp = table[hash(word)];

    while (tmp)
    {
        //checks if the word is a match in the dictionary
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //read the dictionary
    FILE *inptr = fopen(dictionary, "r");

    //create a buffer to hold the string
    char *stringBuffer = malloc(sizeof(char) * LENGTH);

    while (true)
    {
        //simultaneously reads from file into buffer while checking for end of file
        if (fscanf(inptr, "%s", stringBuffer) == EOF)
        {
            free(stringBuffer);
            fclose(inptr);
            return true;
        }

        //create new node for string
        node *n = malloc(sizeof(node));
        strcpy(n->word, stringBuffer);
        n->next = NULL;

        //create index for the string by hashing
        int key = hash(stringBuffer);

        //if no current entries, then set entry to new node
        if (!table[key])
        {
            count++;
            table[key] = n;
        }
        //if no second entry, set second entry to new node
        else if (table[key]->next == NULL)
        {
            count++;
            table[key]->next = n;
        }
        //if second entry exists, insert node in the front
        else
        {
            //new node points to the second entry
            n->next = table[key]->next;
            //head points to new node
            table[key]->next = n;
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *n;
    node *tmp;

    for (int i = 0; i < N; i++)
    {
        //set tmp to head
        tmp = table[i];

        //if no entry, then skip
        if (tmp)
        {
            //point the cursor to the next node
            n = tmp->next;

            //free the current node
            free(tmp);

            while (n)
            {
                //point temp to current node
                tmp = n;

                //point cursor to next node
                n = tmp->next;

                //free current node
                free(tmp);
            }
        }
    }
    return true;
}

/* Explanation: The only time when this program is allocating new memory is
ONLY in load(). Otherwise, in the other functions, new nodes can be
created (without allocating storage) and pointed to already existing
nodes. Then in unload(), we free all of the memory in the dictionary. */