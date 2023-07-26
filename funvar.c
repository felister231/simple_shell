#include "shell.h"

/**
 * strContent_replace - Replace the content of string pointer with new string
 * @old: Pointer to the old string pointer
 * @new: New string to be assigned to the old string pointer
 *
 * Return: Always returns 1
 */

int strContent_replace(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * variableReplace - Replace variables in argv with corresponding values from env
 * @info: Pointer to the info_t struct containing command and env information
 *
 * Return: Always returns 0
 */

int variableReplace(data_info *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			strContent_replace(&(info->argv[i]),
				_strdup(convert_Numstr(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			strContent_replace(&(info->argv[i]),
				_strdup(convert_Numstr(getpid(), 10, 0)));
			continue;
		}
		node = strNode_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			strContent_replace(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		strContent_replace(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * cmdAlias_replace - Replace the command with its alias if found in list
 * @info: Pointer to the info_t struct containing command and alias information
 *
 * Return: 1 if the replacement is successful, 0 if no matching alias is found.
 */

int cmdAlias_replace(data_info *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = strNode_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * bufferUpdate_check - Check the status of command buffer and update it accordingly
 * @info: Pointer to the info_t struct containing command and status info
 * @buf: Buffer containing the command chain
 * @p: Pointer to the current index in the buffer
 * @i: Current index to be checked in the buffer
 * @len: Length of the buffer
 */

void bufferUpdate_check(data_info *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * chainCmd - Check if current command is type CMD_OR, CMD_AND, or CMD_CHAIN
 * @info: Pointer to the info_t struct containing command buffer type info
 * @buf: Buffer containing the command chain
 * @p: Pointer to the current index in the buffer
 *
 * Return: 1 if a valid command chain is found, 0 otherwise.
 */
int chainCmd(data_info *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
