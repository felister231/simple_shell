#include "shell.h"
/**
 * executeCommand - Function to execute a command with its arguments
 * @tokens: Array of pointers containing the command and its arguments
 *
 * This function executes the command specified by the tokens array and its arguments.
 * It first forks a child process using the fork system call and then uses execvp to
 * replace the child process with the desired command. The parent process waits for
 * the child to finish its execution before returning.
 *
 * @tokens: Array of pointers containing the command and its arguments.
 *          The first element of the array should be the command to be executed,
 *          followed by its arguments (with a NULL pointer at the end of the array).
 *          For example, {"ls", "-l", NULL}.
 */
void executeCommand(char **tokens)
{
    pid_t pid = fork(); /* Fork to create a child process */

    if (pid < 0)
    {
        printf("Fork failed.\n"); /* Forking error occurred */
        return;
    }
    else if (pid == 0)
    {

        /* Execute the command specified by tokens using execvp */
        if (execvp(tokens[0], tokens) < 0)
        {
            printf("Command execution failed.\n"); /* execvp returned an error */
            exit(1); /* Exit the child process with an error status */
        }
    }
    else
    {

        /* Wait for the child process to finish its execution */
        wait(NULL);
        return;
    }
}

