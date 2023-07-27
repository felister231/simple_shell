#include "shell.h"

/**
 * printFmt_alias - Print an alias in the format: "alias='value'\n"
 * @first_node: Pointer to the list node containing the alias string
 *
 * Return: 0 on success, 1 if the node is NULL
 */
int printFmt_alias(list_t *first_node)
{
	char *pointer = NULL, *b = NULL;

	if (first_node)
	{
		pointer = _strchr(first_node->str, '=');
		for (b = first_node->str; b <= pointer; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(pointer + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - Handle aliases
 * @data: Pointer to the info_t struct containing alias information
 *
 * Return: 0 on success
 */

int shell_alias(data_info *data)
{
	int i = 0;
	char *pointer = NULL;
	list_t *first_node = NULL;

	if (data->argc == 1)
	{
		first_node = data->alias;
		while (first_node)
		{
			printFmt_alias(first_node);
			first_node = first_node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		pointer = _strchr(data->argv[i], '=');
		if (pointer)
			set_alias(data, data->argv[i]);
		else
			printFmt_alias(strNode_with(data->alias, data->argv[i], '='));
	}

	return (0);
}

/**
 * shell_history - Print the command history
 * @data: Pointer to the info_t struct containing command history
 *
 * Return: 0 on success
 */

int shell_history(data_info *data)
{
	print_list(data->history);
	return (0);
}

/**
 * unsetList_alias - Unset an alias from the alias list
 * @data: Pointer to the info_t struct containing alias list
 * @string: The alias string to unset
 *
 * Return: 0 on success, 1 if the alias is not found
 */

int unsetList_alias(data_info *data, char *string)
{
	char *pointer, d;
	int ret;

	pointer = _strchr(string, '=');
	if (!pointer)
		return (1);
	d = *pointer;
	*pointer = 0;
	ret = deleteNode_index(&(data->alias),
			getIndex_node(data->alias, strNode_with(data->alias, string, -1)));
	*pointer = d;
	return (ret);
}

/**
 * set_alias- Set an alias in the alias list
 * @data: Pointer to the info_t struct containing alias list
 * @string: The alias string to set
 *
 * Return: 0 on success, 1 if the alias is not valid or couldn't be set
 */

int set_alias(data_info *data, char *string)
{
	char *pointer;

	pointer = _strchr(string, '=');
	if (!pointer)
		return (1);
	if (!*++pointer)
		return (unsetList_alias(data, string));

	unsetList_alias(data, string);
	return (nodeAdd_end(&(data->alias), string, 0) == NULL);
}
