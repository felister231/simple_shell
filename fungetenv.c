#include "shell.h"

/**
 * update_Env - Set or update an environment variable
 * @info: Pointer to the info_t struct containing environment variables
 * @var: The name of the environment variable to set/update
 * @value: The value to be assigned to the environment variable
 *
 * Sets or updates an environment variable with the provided name and value.
 * Return: 0 on success, 1 if memory allocation fails
 */

int update_Env(data_info *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = str_Startwith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	nodeAdd_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * get_Enviroment_var - Get the environment variables as an array of strings
 * @info: Pointer to the info_t struct containing environment variables
 *
 * Return: Always returns 0 to indicate success
*/

char **get_Enviroment_var(data_info *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_list_to_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_Environ_var - Unset an environment variable
 * @info: Pointer to the info_t struct containing environment variables
 * @var: The name of the environment variable to unset
 *
 * Unsets the environment variable with the provided name from the environment
 * list (info->env). Returns 1 if the variable was unset, 0 if not found.
* Return: 1 if any changes were made to the environment list 0 otherwise.
 */

int unset_Environ_var(data_info *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = str_Startwith(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = deleteNode_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
