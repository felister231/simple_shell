#include "shell.h"

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
