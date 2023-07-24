#include "shell.h"

/**
 * _setenv - Set or update an environment variable
 * @info: Pointer to the info_t struct containing environment variables
 * @var: The name of the environment variable to set/update
 * @value: The value to be assigned to the environment variable
 *
 * Sets or updates an environment variable with the provided name and value.
 * Return: 0 on success, 1 if memory allocation fails
 */

int _setenv(info_t *info, char *var, char *value)
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
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * get_environ - Get the environment variables as an array of strings
 * @info: Pointer to the info_t struct containing environment variables
 *
 * Returns the environment variables as an array of strings.
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Unset an environment variable
 * @info: Pointer to the info_t struct containing environment variables
 * @var: The name of the environment variable to unset
 *
 * Unsets the environment variable with the provided name from the environment
 * list (info->env). Returns 1 if the variable was unset, 0 if not found.
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
