#include "shell.h"

/**
 * free_Datainfo - Free dynamically allocated memory in the info_t struct
 * @info: Pointer to the info_t struct to be freed
 * @all: Flag indicating if to free all resources(1) or only specific ones (0)
 */

void free_Datainfo(data_info *info, int all)
{
	freealloc(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeMem_list(&(info->env));
		if (info->history)
			freeMem_list(&(info->history));
		if (info->alias)
			freeMem_list(&(info->alias));
		freealloc(info->environ);
			info->environ = NULL;
		free_memory((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * clear_Datainfo - Clear/reset the fields in the info_t struct
 * @info: Pointer to the info_t struct to be cleared
 */

void clear_Datainfo(data_info *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_Datainfo - Parse the input command and prepare the info_t struct
 * @info: Pointer to the info_t struct to be prepared
 * @av: Array of strings containing the command-line arguments
 */

void set_Datainfo(data_info *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		cmdAlias_replace(info);
		variableReplace(info);
	}
}
