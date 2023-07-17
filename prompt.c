#include "shell.h"

/**
 * prompt_user - A function that ask user for input
 * Return: returns the value
 */
char *prompt_user()
{
	ssize_t text;
	char *input = NULL;
	size_t number = 0;

	/* this line is prompting the user for a command and takes input from ouput */
	printf("$ ");
	text = getline(&input, &number, stdin);
	/* if the input empty return null */
	if (text == -1)
	{
		free(input);
		return (NULL);
	}
	/* removing trailing spaces */
	input[strcspn(input, "\n")] = '\0';
	return (input);

}
