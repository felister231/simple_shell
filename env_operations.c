#include "main.h"


/**
 * set_environment_variable - Set or update an environment variable
 * @info: Pointer to the parameter struct containing environment info
 * @variable: The environment variable to be set
 * @value: The value to assign to the environment variable
 *
 * Return: 0 on success, 1 on mem alloc failure, or -1 if variable is NULL
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	if (!variable || !value)
		return (-1);

	char *buf = malloc(_strlen(variable) + _strlen(value) + 2);

	if (!buf)
	{
		fprintf(stderr, "Memory allocation error in set_env_variable.\n");
		return (1);
	}

	/* Construct the environment variable string in the format "variable=value" */
	_strcpy(buf, variable);
	_strcat(buf, "=");
	_strcat(buf, value);
	/* Traverse the environment list to find if the variable already exists */
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			/* If the variable already exists, update its value and return */
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	/* If the var does not exist, add it to the end of the environment list */
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * unset_environment_variable - Unset an environment variable
 * @info: Pointer to the parameter struct containing environment info
 * @variable: The environment variable to be unset
 *
 * Return: 0 on success or -1 if variable is NULL
 */
int unset_environment_variable(info_t *info, char *variable)
{
	/* Check if the variable is NULL */
	if (!variable)
		return (-1);

	/* Traverse the environment list to find the variable to unset */
	list_t *node = info->env;
	char *p;
	size_t i = 0;

	while (node)
	{
		/* Check if the node's string starts with the given variable */
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			/* If found, delete the node at the current index and update the list */
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env; /* start again from the beginning after deletion */
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

