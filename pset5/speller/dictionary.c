// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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
const unsigned int N = 5000;

// Hash table
node *table[N];

unsigned int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // word string size
    int wordlen = strlen(word);

    // creates a string array with length equal to word + 1
    // for the null char
    char wordcpy[wordlen + 1];

    // copies all of the chars in the string
    for (int i = 0; i <= wordlen; i++)
        wordcpy[i] = tolower(word[i]);

    // Calculates the word's hash value
    int hash_value = hash(wordcpy);

    node *check_word = table[hash_value];

    // Creates the check_word node with the calculated hash_value
    // then uses the condition of the check_word pointer node being different than NULL
    // then continually changes the cursor to the next pointer.
    while (check_word != NULL)
    {
        // If the word is in the dictionary, return true
        if (strcasecmp(word, check_word->word) == 0)
        {
            return true;
        }
        check_word = check_word->next;
    }
    // If the word was not found, then returns false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // source: http://www.cse.yorku.ca/~oz/hash.html and https://gist.github.com/MohamedTaha98/ccdf734f13299efb73ff0b12f7ce429f
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opens dictionary, read only
    FILE *dict = fopen(dictionary, "r");

    // Checks for memory errors
    if (dict == NULL)
    {
        return false;
    }

    // Creates a buffer character array for the word with length equal to the max length size + 1
    char buffer[LENGTH + 1];

    // Uses fscanf to scan each word until it reaches the end of the file
    while (fscanf(dict, "%s", buffer) != EOF)
    {
        // Allocates memory to create a new node
        node *n = malloc(sizeof(node));
        // Checks if the program ran out of memory
        if (n == NULL)
        {
            return false;
        }

        // Copies the buffer character array into the node
        strcpy(n->word, buffer);

        // Sets the node pointer to NULL
        n->next = NULL;

        // Calls the hash function
        int hash_value = hash(n->word);

        word_count += 1;

        // Checks if the node already has a value
        if (table[hash_value] == NULL)
        {
            // Puts the node in the calculated position
            table[hash_value] = n;
        }
        // If the position already has a value
        else
        {
            // Points the new node to the head of the table
            n->next = table[hash_value];

            // Points the table array to the new node
            table[hash_value] = n;
        }
    }

    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // returns the ammount of words in the dictionary
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Goes through the entire table
    for (int i = 0; i < N; i++)
    {
        // Creates a cursor to go through the table in question
        node *cursor = table[i];
        // Repeats the loop while the cursor isn't NULL
        while (cursor != NULL)
        {
            // Creates a tmp pointer node to point at the data cursor is pointing at
            node *tmp = cursor;
            // Sets the cursor to the next pointer
            cursor = cursor->next;
            // Frees the current node being pointed at by tmp
            free(tmp);
        }
    }
    return true;
}