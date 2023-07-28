#include "shell.h"

/**
 * print_list - Print the elements of a linked list
 * @head: Pointer to the head of the linked list
 *
 * Return: The number of nodes in the list
 */

size_t print_list(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(convert_Numstr(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * convert_list_to_str - Convert a linked list to an array of strings
 * @pointer_head: Pointer to the head of the linked list
 *
 * Return: An array of strings containing the elements of the linked list
 *         or NULL if memory allocation fails
 */

char **convert_list_to_str(list_t *pointer_head)
{
	list_t *node = pointer_head;
	size_t i = getList_len(pointer_head), j;
	char **strs;
	char *str;

	if (!pointer_head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * getList_len - Get the number of elements in a linked list
 * @head: Pointer to the head of the linked list
 *
 * Return: The number of nodes in the linked list
 */

size_t getList_len(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		head = head->next;
		j++;
	}
	return (j);
}
