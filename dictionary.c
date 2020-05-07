/**\file dictionary.c
 * Implementation of dictionary for project 2. This file contains the implementation
 * of the dictionary specified in the requirements for project 2.
 *
 * \author Kate Wood <kate.wood@hotmail.co.uk>
 *
 * \version Attempt 1
 *
 * \date 20/01/2017
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

Dictionary *create_dictionary(void)
{
    // Allocate memory for dictionary structure
    Dictionary *dict = (Dictionary *)calloc(1, sizeof(Dictionary));

    // Check memory
    if(!dict) {
        return NULL;
    }
    return dict;
}

void free_dictionary(Dictionary *dict)
{
    int i;
    for (i=0; i< 26; ++i) {
        while(dict -> head[i]) {
            Node *oldhead = dict -> head[i];   // Copy of the head pointer so don't loose it's location in memory
            dict -> head[i] = oldhead -> next; // Assign next node to head pointer to unlink the head item
            free(oldhead);                     // free the old head
        }
    }
    free(dict);                      // Free dictionary memory
}
int add_word(Dictionary *dict, char *word)
{
    // Find which list to search in from first letter
    int i = toupper (word[0]) - 65;  // change first letter of word to upper case and -65 to get index 0-25 for A-Z

    // Call find word function to check if word already exists in Dictionary
    if (find_word(dict, word)){
        return 0;
    }

    // If word is not found in dictionary - reaches the end of the list, add word.
    // Allocate memory to create node
    Node *newnode = (Node *)malloc(sizeof(Node));

    // Check if there is enough memory
    if(!newnode) {
        // If not, print an error and exit
        fputs("malloc failed in add word function\n", stderr);
		exit(1);
    }

    // Copy word into memory
    strcpy(newnode->word, word);

    // Add node to list
     newnode -> next = dict -> head[i];
     dict -> head[i] = newnode;
     return 1;
}

int find_word(Dictionary *dict, char *word)
{

    int i = toupper (word[0]) - 65;

    // Store pointer to head of list
    Node* n = dict->head[i];

    // Search through sub dictionary list to see if word input by user exists
    // While not end of sub dictionary
    while (n != NULL) {
        if (strcmp(n -> word, word) == 0) { // See if word is in sub dictionary.
            return 1;
        }
        n = n->next;
    }
    return 0;
}

void print_dictionary(Dictionary *dict)
{
    int i;

    for (i=0; i< 26; ++i) {
        Node* n = dict->head[i];    // Copy head pointer
        while (n != NULL) {         // Print word
            printf("%s", n -> word);
            n = n->next;
        }
     }
}