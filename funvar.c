#include "shell.h"

/**
 * strContent_replace - Replace the content of string pointer with new string
 * @oldString: Pointer to the old string pointer
 * @newString: New string to be assigned to the old string pointer
 *
 * Return: Always returns 1
 */

int strContent_replace(char **oldString, char *newString)
{
	free(*oldString);
	*oldString = newString;
	return (1);
}

/**
 * variableReplace - Replace vars in argv with corresponding values from env
 * @data: Pointer to the info_t struct containing command and env information
 *
 * Return: Always returns 0
 */

int variableReplace(data_info *data)
{
	int a = 0;
	list_t *current_node;

	for (a = 0; data->argv[a]; a++)
	{
		if (data->argv[a][0] != '$' || !data->argv[a][1])
			continue;

		if (!_strcmp(data->argv[a], "$?"))
		{
			strContent_replace(&(data->argv[a]),
					_strdup(convert_Numstr(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[a], "$$"))
		{
			strContent_replace(&(data->argv[a]),
					_strdup(convert_Numstr(getpid(), 10, 0)));
			continue;
		}
		current_node = strNode_with(data->env, &data->argv[a][1], '=');
		if (current_node)
		{
			strContent_replace(&(data->argv[a]),
					_strdup(_strchr(current_node->str, '=') + 1));
			continue;
		}
		strContent_replace(&data->argv[a], _strdup(""));
	}
	return (0);
}

/**
 * cmdAlias_replace - Replace the command with its alias if found in list
 * @data: Pointer to the info_t struct containing command and alias information
 *
 * Return: 1 if the replacement is successful, 0 if no matching alias is found.
 */

int cmdAlias_replace(data_info *data)
{
	int index;
	list_t *current_node;
	char *pointer;

	for (index = 0; index < 10; index++)
	{
		current_node = strNode_with(data->alias, data->argv[0], '=');
		if (!current_node)
			return (0);
		free(data->argv[0]);
		pointer = _strchr(current_node->str, '=');
		if (!pointer)
			return (0);
		pointer = _strdup(pointer + 1);
		if (!pointer)
			return (0);
		data->argv[0] = pointer;
	}
	return (1);
}

/**
 * bufferUpdate_check - Check the status of command buffer and update it
 * @data: Pointer to the info_t struct containing command and status info
 * @buffer: Buffer containing the command chain
 * @pointer: Pointer to the current index in the buffer
 * @index: Current index to be checked in the buffer
 * @length: Length of the buffer
 */


void bufferUpdate_check(data_info *data, char *buffer, size_t *pointer,
	size_t index, size_t length)
{
	size_t j = *pointer;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buffer[index] = 0;
			j = length;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buffer[index] = 0;
			j = length;
		}
	}

	*pointer = j;
}

/**
 * chainCmd - Check if current command is type CMD_OR, CMD_AND, or CMD_CHAIN
 * @data: Pointer to the info_t struct containing command buffer type info
 * @buffer: Buffer containing the command chain
 * @pointer: Pointer to the current index in the buffer
 *
 * Return: 1 if a valid command chain is found, 0 otherwise.
 */

int chainCmd(data_info *data, char *buffer, size_t *pointer)
{
	size_t j = *pointer;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*pointer = j;
	return (1);
}
