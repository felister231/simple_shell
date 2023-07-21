#include "shell.h"

/**
 * handleBuiltInCommands - Function to handle built-in commands in the shell
 * @tokens: Array of pointers containing the command and its arguments
 *
 * This function checks the first token (command) in the tokens array and performs
 * specific actions for each built-in command: exit, cd, help, and hello.
 * For the exit command, it prints "Goodbye!" and returns 1 to signal the shell to exit.
 * For the cd command, it changes the current working directory using chdir and returns 1.
 * For the help command, it prints a list of supported commands and returns 1.
 * For the hello command, it prints a greeting message and returns 1.
 * If the input command is not a built-in command, the function returns 0.
 *
 * @tokens: Array of pointers containing the command and its arguments.
 *          The first element of the array should be the command to be executed,
 *          followed by its arguments (with a NULL pointer at the end of the array).
 *          For example, {"exit", NULL}.
 *
 * Return: 1 if a built-in command is handled, 0 otherwise.
 */
int handleBuiltInCommands(char **tokens)
{
    if (strcmp(tokens[0], "exit") == 0)
    {
        printf("Goodbye!\n"); /* Print a goodbye message */
        return 1; /* Return 1 to signal the shell to exit */
    }
    else if (strcmp(tokens[0], "cd") == 0)
    {
        if (chdir(tokens[1]) != 0)
            printf("Directory not found.\n"); /* Print an error message if chdir fails */
        return 1; /* Return 1 to indicate that the cd command is handled */
    }
    else if (strcmp(tokens[0], "help") == 0)
    {
        printf("List of commands supported:\n"); /* Print a list of supported commands */
        printf("- exit\n");
        printf("- cd <directory>\n");
        printf("- help\n");
        return 1; /* Return 1 to indicate that the help command is handled */
    }
    else if (strcmp(tokens[0], "hello") == 0)
    {
        printf("Hello! This is a simple shell.\n"); /* Print a greeting message */
        return 1; /* Return 1 to indicate that the hello command is handled */
    }

    return 0; /* Return 0 to indicate that the input command is not a built-in command */
}
