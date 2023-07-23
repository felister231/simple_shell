#include "main.h"

/**
 * free_info - Frees the memory allocated for info_t struct members.
 * @info: Pointer to the info_t struct.
 * @all: Flag to indicate if all elements should be freed.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv); /* Free the argv array */
	info->argv = NULL;
	info->path = NULL; /* Clear the path pointer */
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg); /* Free the arg string if cmd_buf is empty */
		if (info->env)
			free_list(&(info->env)); /* Free the environment list */
		if (info->history)
			free_list(&(info->history)); /* Free the history list */
		if (info->alias)
			free_list(&(info->alias)); /* Free the alias list */
		ffree(info->environ); /* Free the environ array */
		info->environ = NULL;
		bfree((void **)info->cmd_buf); /* Free the cmd_buf array */
		if (info->readfd > 2)
			close(info->readfd); /* Close the readfd file descriptor */
		_putchar(BUF_FLUSH); /* Flush the output buffer */
	}
}

/**
 * set_info - Sets up the info_t struct with provided arguments.
 * @info: Pointer to the info_t struct.
 * @av: Array of strings containing command-line arguments.
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0]; /* Set the fname with the first argument */
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t"); /* Tokenize arg and store in argv */
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2); /* Allocate memory for argv */
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg); /* Duplicate arg into argv[0] */
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			; /* Count the number of elements in argv to get argc */
		info->argc = i;

		replace_alias(info); /* Replace aliases in argv with their values */
		replace_vars(info); /* Replace variables in argv with their values */
	}
}

/**
 * clear_info - Clears the elements of the info_t struct.
 * @info: Pointer to the info_t struct.
 */
void clear_info(info_t *info)
{
	info->arg = NULL; /* Clear the arg pointer */
	info->argv = NULL; /* Clear the argv pointer */
	info->path = NULL; /* Clear the path pointer */
	info->argc = 0; /* Reset argc to 0 */
}

