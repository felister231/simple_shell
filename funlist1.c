#include "shell.h"

/**
 * get_node_index - Get the index of a node in a linked list
 * @head_pointer: Pointer to the head of the linked list
 * @first_node: Pointer to the node whose index is to be found
 *
 * Returns the index of  given node in  linked list starting from the head.
 * Return: The index of the node in the list, or -1 if the node is not found
 */

ssize_t get_node_index(list_t *head_pointer, list_t *first_node)
{
	size_t j = 0;

	while (head_pointer)
	{
		if (head_pointer == first_node)
			return (j);
		head_pointer = head_pointer->next;
		j++;
	}
	return (-1);
}

/**
 * node_starts_with - Find a node with a string that starts with  given prefix
 * @first_node: Pointer to the head of the linked list
 * @affix: The prefix to search for at the beginning of the strings
 * @d: Optional character to check after the prefix, or -1 to skip this check
 *
 * Return: Pointer to  first node with a matching string, or NULL if not found
 */

list_t *node_starts_with(list_t *first_node, char *affix, char d)
{
	char *pointer = NULL;

	while (first_node)
	{
		pointer = starts_with(first_node->str, affix);
		if (pointer && ((d == -1) || (*pointer == d)))
			return (first_node);
		first_node = first_node->next;
	}
	return (NULL);
}


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
		_puts(convert_number(head->num, 10, 0));
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
 * list_to_strings - Convert a linked list to an array of strings
 * @pointer_head: Pointer to the head of the linked list
 *
 * Return: An array of strings containing the elements of the linked list
 *         or NULL if memory allocation fails
 */

char **list_to_strings(list_t *pointer_head)
{
	list_t *node = pointer_head;
	size_t i = list_len(pointer_head), j;
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
 * list_len - Get the number of elements in a linked list
 * @head: Pointer to the head of the linked list
 *
 * Return: The number of nodes in the linked list
 */

size_t list_len(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		head = head->next;
		j++;
	}
	return (j);
}
