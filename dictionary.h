/** \file dictionary.h
 *  Interface for spell checker for project 2. This file contains the prototypes for the
 *  dictionary module.
 *
 *  \author kate.wood <kate.wood@hotmail.co.uk>
 *
 *  \version attempt 1
 *
 *  \date 20/01/2017
 */

#ifndef _DICTIONARY_H
#define _DICTIONARY_H 1

/** An internal structure type representing a node in the linked list.
 */
typedef struct node{
    char word[45];      // Word to be stored in structure
    struct node *next;  // Pointer to next node in list
}Node;

/** A structure representing a dictionary containing an array of nodes to store a list for each letter of the
 *  alphabet
 */

typedef struct {
    Node *head[26];     // Pointer to 26 linked lists, one for each letter
}Dictionary;

/**Allocate a new Dictionary structure and perform any initialisation tasks required to set the dictionary up.
 */

Dictionary *create_dictionary(void);

/** Release the memory used by a dictionary and any internal storage it may have associated with it.
 *  \param release A pointer to the dictionary to free
 */

void free_dictionary(Dictionary *dict);


/** Adds the provided word to the dictionary, provided that the word does not already exist in the dictionary. This function
 *  should check whether the word pointed to by 'word' already exists in 'dict'. If it does not, the word should be added to the
 *  storage inside dict.
 *  \param char *word pointer to the 'word' to be added to the dictionary
 *  \param Dictionary *dict the dictionary in which to add the word.
 *  \return true If the word is added to 'dict.' False if the word is not added
 */
int add_word(Dictionary *dict, char *word);

/** Searches the dictionary in an attempt to find the word
 *  \param char *word pointer to the 'word' to be found in the dictionary
 *  \param Dictionary *dict the dictionary in which to search for the word.
 *  \return True if the word is found, false if it is not.
 */
int find_word(Dictionary *dict, char *word);

/** Prints the contents of the dictionary with one word on each line
 * \param Dictionary *dict the dictionary in which print
 */
void print_dictionary(Dictionary *dict);

#endif