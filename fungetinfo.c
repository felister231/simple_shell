#include "shell.h"

/**
 * free_Datainfo - Free dynamically allocated memory in the info_t struct
 * @data: Pointer to the info_t struct to be freed
 * @free_all: Flag indicating if to free all resources(1) or specific ones (0)
 */

void free_Datainfo(data_info *data, int free_all)
{
	freealloc(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (free_all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			freeMem_list(&(data->env));
		if (data->history)
			freeMem_list(&(data->history));
		if (data->alias)
			freeMem_list(&(data->alias));
		freealloc(data->environ);
		data->environ = NULL;
		free_memory((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * clear_Datainfo - Clear/reset the fields in the info_t struct
 * @data: Pointer to the info_t struct to be cleared
 */

void clear_Datainfo(data_info *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * set_Datainfo - Parse the input command and prepare the info_t struct
 * @data: Pointer to the info_t struct to be prepared
 * @argv: Array of strings containing the command-line arguments
 */


void set_Datainfo(data_info *data, char **argv)
{
	int number = 0;

	data->fname = argv[0];
	if (data->arg)
	{
		data->argv = strtow(data->arg, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (number = 0; data->argv && data->argv[number]; number++)
			;
		data->argc = number;

		cmdAlias_replace(data);
		variableReplace(data);
	}
}
