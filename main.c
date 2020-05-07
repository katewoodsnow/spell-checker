/** \file wood_project2.c
 *  Submission for project 2.
 *
 *  This code identifies correctly spelt or incorrectly spelt words
 *  provided on the command line by comparing them against a dictionary of words.
 *
 *  \author Kate Wood <kate.wood@hotmail.co.uk>
 *
 *  \version Attempt 1
 *
 *  \date 20/01/2017
 */


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"


/** Function to remove newline from the word to terminate the
 *  string due to fgets() returns a pointer to the string.
 * \param string -filename
 * \return Remove newline from the string
 */
static char *chomp(char *string)
{
    int size = strlen(string);
    int pos;

    // move back down the string from the end, as there may be a CR, CR+LF or LF there...
    for(pos = (size - 1); pos >= 0; --pos) {
        // If the character is a CR or LF, replace it with null
        if(string[pos] == 0xD || string[pos] == 0xA) {
            string[pos] = 0;
        } else {
            return string;
        }
    }
    return string;
}

/** Function to remove trailing S from word if word not found in dictionary.
 * \param word word to remove the s from
 * \return remove s from word
 */
static int removeS(char *word)
{
    int len = strlen(word);

    if(word[len-1] == 's') {
        word[len-1] = 0;
        return 1;
    }
    return 0;
}

/** Function to change word to lower case.
 *  \param word word to be changed
 */
static void changeToLowerCase(char *word)
{
    int i;
    //convert word to be searched to lower case
    for(i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
}

int main(int argc, char **argv)
{
    char word [45];
    FILE *fp;
    int found;
    int i;

    // Create dictionary
    Dictionary *dict = create_dictionary();

    if(!dict) {
        fputs("Dictionary creation failed. Aborting.\n", stderr);
        exit(1);
    }

    // Open the file to read */
    fp = fopen("words.txt", "r");

    // Check for errors when opening the file and return information to the user
    if (!fp){
        fprintf(stderr, "file '%s' failed to open\n", "words.txt");
        perror("Error");
        getchar();
        exit(1);
    }

    // Read input file, adding each word to the dictionary. */
    while (fgets(word, sizeof(word), fp)){
        chomp(word);
        changeToLowerCase(word);
        add_word(dict, word);
    }

    // Check words
    for(i = 1; i < argc; ++i) {
        // Set input word to lower case so dictionary match works.
        changeToLowerCase(argv[i]);
        found = find_word(dict, argv[i]);

        if (found){
            printf("%s is OK\n", argv[i]);
        }
        else {
            // Check if word ends in s, if so remove it
            if (removeS(argv[i])){
                found = find_word(dict, argv[i]);
                if(found){
                    printf("Singular of %ss is OK\n", argv[i]);
                }
                else {
                    printf("%ss is not OK\n", argv[i]);
                }
            }
            else{
                printf("%s is not OK\n", argv[i]);
            }
        }
    }

    /* Print dictionary function left out of main as question stipulates to output the result of the word
     * being checked rather than the dictionary. Printed dictionary to check add word when writing the program.
     */
    // print_dictionary(dict);
    getchar();

    free_dictionary(dict);

    return 0;
}