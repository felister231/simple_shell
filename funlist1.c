#include "shell.h"

/**
 * get_node_index - Get the index of a node in a linked list
 * @head: Pointer to the head of the linked list
 * @node: Pointer to the node whose index is to be found
 *
 * Returns the index of  given node in  linked list starting from the head.
 * Return: The index of the node in the list, or -1 if the node is not found
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * node_starts_with - Find a node with a string that starts with  given prefix
 * @node: Pointer to the head of the linked list
 * @prefix: The prefix to search for at the beginning of the strings
 * @c: Optional character to check after the prefix, or -1 to skip this check
 *
 * Return: Pointer to  first node with a matching string, or NULL if not found
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 * print_list - Print the elements of a linked list
 * @h: Pointer to the head of the linked list
 *
 * Return: The number of nodes in the list
 */

size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - Convert a linked list to an array of strings
 * @head: Pointer to the head of the linked list
 *
 * Return: An array of strings containing the elements of the linked list
 *         or NULL if memory allocation fails
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
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
 * list_len - Get the number of elements in a linked list
 * @h: Pointer to the head of the linked list
 *
 * Return: The number of nodes in the linked list
 */

size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
