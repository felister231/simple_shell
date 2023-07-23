#include "main.h"

/**
 * populate_environment_list - Populates environ list from'environ' variable
 * @info: Pointer to the parameter struct containing environment info
 *
 * Return: 0 on success, or appropriate error code
 */
int populate_environment_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * unset_environment_variable - Unsets environment variables
 * @info: Pointer to the parameter struct containing environment info
 *
 * Return: 0 on success, or appropriate error code
 */
int unset_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i < info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * set_environment_variable - Sets or updates an environment variable
 * @info: Pointer to the parameter struct containing environment info
 *
 * Return: 0 on success, or appropriate error code
 */
int set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _find_environment_variable - Finds an environment variable by name
 * @info: Pointer to the parameter struct containing environment info
 * @name: The name of the environment variable to find
 *
 * Return: Pointer to value of environment variable, or NULL if not found
 */
char *_find_environment_variable(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * print_environment - Prints the current environment variables
 * @info: Pointer to the parameter struct containing environment info
 *
 * Return: 0 on success
 */
int print_environment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

