#include "shell.h"

/**
 * strNode_with - Find a node with a string that starts with  given prefix
 * @first_node: Pointer to the head of the linked list
 * @affix: The prefix to search for at the beginning of the strings
 * @d: Optional character to check after the prefix, or -1 to skip this check
 *
 * Return: Pointer to  first node with a matching string, or NULL if not found
 */

list_t *strNode_with(list_t *first_node, char *affix, char d)
{
	char *pointer = NULL;

	while (first_node)
	{
		pointer = str_Startwith(first_node->str, affix);
		if (pointer && ((d == -1) || (*pointer == d)))
			return (first_node);
		first_node = first_node->next;
	}
	return (NULL);
}

/**
 * getIndex_node - Get the index of a node in a linked list
 * @head_pointer: Pointer to the head of the linked list
 * @first_node: Pointer to the node whose index is to be found
 *
 * Returns the index of  given node in  linked list starting from the head.
 * Return: The index of the node in the list, or -1 if the node is not found
 */

ssize_t getIndex_node(list_t *head_pointer, list_t *first_node)
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
