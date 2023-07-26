#include "shell.h"

/**
 * update_Env - Set or update an environment variable
 * @data: Pointer to the info_t struct containing environment variables
 * @variable: The name of the environment variable to set/update
 * @value: The value to be assigned to the environment variable
 *
 * Sets or updates an environment variable with the provided name and value.
 * Return: 0 on success, 1 if memory allocation fails
 */

int update_Env(data_info *data, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *current_node;
	char *pointer;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	current_node = data->env;
	while (current_node)
	{
		pointer = str_Startwith(current_node->str, variable);
		if (pointer && *pointer == '=')
		{
			free(current_node->str);
			current_node->str = buffer;
			data->env_changed = 1;
			return (0);
		}
		current_node = current_node->next;
	}
	nodeAdd_end(&(data->env), buffer, 0);
	free(buffer);
	data->env_changed = 1;
	return (0);
}

/**
 * get_Enviroment_var - Get the environment variables as an array of strings
 * @data: Pointer to the info_t struct containing environment variables
 *
 * Return: Always returns 0 to indicate success
 */

char **get_Enviroment_var(data_info *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = convert_list_to_str(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * unset_Environ_var - Unset an environment variable
 * @data: Pointer to the info_t struct containing environment variables
 * @variable: The name of the environment variable to unset
 *
 * Unsets the environment variable with the provided name from the environment
 * list (info->env). Returns 1 if the variable was unset, 0 if not found.
 * Return: 1 if any changes were made to the environment list 0 otherwise.
 */

int unset_Environ_var(data_info *data, char *variable)
{
	list_t *current_node = data->env;
	size_t index = 0;
	char *pointer;

	if (!current_node || !variable)
		return (0);

	while (current_node)
	{
		pointer = str_Startwith(current_node->str, variable);
		if (pointer && *pointer == '=')
		{
			data->env_changed = deleteNode_index(&(data->env), index);
			index = 0;
			current_node = data->env;
			continue;
		}
		current_node = current_node->next;
		index++;
	}
	return (data->env_changed);
}
