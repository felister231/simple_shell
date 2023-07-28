#include "shell.h"

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
