#include "shell.h"
/**
 * readInput - Function to read user input from standard input (stdin)
 * @input: Double pointer to a character representing the user input
 *
 * This function reads user input from the standard input (stdin) using the getline function.
 * It dynamically allocates memory to store the input and automatically tracks the size
 * of the allocated buffer. The user input is stored in the memory pointed by the "input" pointer.
 *
 * @input: Double pointer to a character to store the user input.
 *         The pointer will be updated to point to the allocated buffer containing the input.
 *
 * Return: The number of characters read (including the newline character), or -1 if an error occurs.
 *         If successful, the pointer "input" will be updated to point to the allocated buffer.
 */
int readInput(char **input)
{
    size_t bufsize = 0; /* Declare a variable to hold the size of the input buffer (number of characters read) */

    /*
     * Use the getline function to read the user input from stdin.
     * The function dynamically allocates memory for the input and stores it in the pointer "input."
     * The size of the allocated buffer is automatically tracked and stored in "bufsize."
     * The function returns the number of characters read, or -1 if an error occurs.
     */
    return getline(input, &bufsize, stdin);
}

