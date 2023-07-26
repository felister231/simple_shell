#include "shell.h"

/**
 * enviro_list_pop - Populates the environment linked list with env vars.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */

int enviro_list_pop(data_info *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		nodeAdd_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * _myenvironment - Prints the current environment.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _myenvironment(data_info *info)
{
	nodePrint_str(info->env);
	return (0);
}
/**
 * _getenviroment - Gets the value of an environment variable.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @name: The environment variable name.
 *
 * Return: The value of the environment variable if found.
 *         If the variable is not found, returns NULL.
 */

char *_getenviroment(data_info *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = str_Startwith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * unset_Environ_variroment - Remove an environment variable.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */

int unset_Environ_variroment(data_info *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_Environ_var(info, info->argv[i]);

	return (0);
}

/**
 * _mysetenviroment - Initializes a new environ variable or modifies an existing one.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: If the function is called with an incorrect number of arguments,
 *         it prints an error message and returns 1.
 *         If the environment variable is successfully set, it returns 0.
 *         On failure, it returns 1.
 */

int _mysetenviroment(data_info *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (update_Env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
