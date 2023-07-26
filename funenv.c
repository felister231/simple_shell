#include "shell.h"

/**
 * enviro_list_pop - Populates the environment linked list with env vars.
 *
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */

int enviro_list_pop(data_info *data)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		nodeAdd_end(&node, environ[index], 0);
	data->env = node;
	return (0);
}

/**
 * _myenvironment - Prints the current environment.
 *
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _myenvironment(data_info *data)
{
	nodePrint_str(data->env);
	return (0);
}
/**
 * _getenviroment - Gets the value of an environment variable.
 *
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @name: The environment variable name.
 *
 * Return: The value of the environment variable if found.
 *         If the variable is not found, returns NULL.
 */

char *_getenviroment(data_info *data, const char *name)
{
	list_t *current_node = data->env;
	char *pointer;

	while (current_node)
	{
		pointer = str_Startwith(current_node->str, name);
		if (pointer && *pointer)
			return (pointer);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * unset_Environ_variroment - Remove an environment variable.
 *
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */

int unset_Environ_variroment(data_info *data)
{
	int a;

	if (data->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	} 
	for (a = 1; a <= data->argc; a++)
		unset_Environ_var(data, data->argv[a]);

	return (0);
}

/**
 * _mysetenviroment - Initializes  new environ var or modifies existing one.
 *
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: If the function is called with an incorrect number of arguments,
 *         it prints an error message and returns 1.
 *         If the environment variable is successfully set, it returns 0.
 *         On failure, it returns 1.
 */

int _mysetenviroment(data_info *data)
{
	if (data->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (update_Env(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}
