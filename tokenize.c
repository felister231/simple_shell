#include "shell.h"

/**
 * tokenizeInput - Function to tokenize the input string
 * @input: Pointer to the input string to be tokenized
 * @tokens: Array of pointers to store the tokens
 * @numTokens: Pointer to an integer to store the number of tokens
 *
 * This function tokenizes the input string based on delimiters " \t\n".
 * It uses the strtok function to split the input into separate tokens.
 *
 * @input: Pointer to the input string that will be tokenized.
 * @tokens: Array of pointers to store the tokens after tokenization.
 *          The function updates this array with pointers to the individual tokens.
 * @numTokens: Pointer to an integer to store the number of tokens found.
 *             The function updates this integer with the total number of tokens.
 *             If no tokens are found, this will be set to 0.
 */
void tokenizeInput(char *input, char **tokens, int *numTokens)
{
    char *token = strtok(input, " \t\n"); /* Get the first token using strtok */

    int i = 0;

    /* Loop through the input string to extract tokens using strtok */
    while (token != NULL)
    {
        tokens[i] = token; /* Store the current token in the tokens array */
        i++; /* Increment the index for the next token */
        token = strtok(NULL, " \t\n"); /* Get the next token */
    }

    tokens[i] = NULL; /* Set the last element of the tokens array to NULL to mark the end */
    *numTokens = i; /* Update the numTokens with the total number of tokens found */
}

