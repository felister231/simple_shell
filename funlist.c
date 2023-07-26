#include "shell.h"

/**
 * freeMem_list - Free the memory occupied by a linked list and its nodes.
 * pointer_head: A pointer to the head node of the linked list.
 *
 * This function frees the memory occupied by a linked list and its nodes,
 * including the memory allocated for the string in each node.
 *
 * Return: None.
 */

void freeMem_list(list_t **pointer_head)
{
	list_t *first_node, *next_node, *head;

	if (!pointer_head || !*pointer_head)
		return;
	head = *pointer_head;
	first_node = head;
	while (first_node)
	{
		next_node = first_node->next;
		free(first_node->str);
		free(first_node);
		first_node = next_node;
	}
	*pointer_head = NULL;
}

/**
 * deleteNode_index - Delete a node at a specific index in a linked list.
 * @list_head: A pointer to the head node of the linked list.
 * @number: The index of the node to delete.
 *
 * This function deletes the node at the specified index in the linked list.
 * It frees the memory allocated for the string in the node and the memory
 * occupied by the node itself.
 *
 * Return: 1 if the node was successfully deleted, 0 otherwise.
 */


int deleteNode_index(list_t **list_head, unsigned int number)
{
	list_t *first_node, *prev_node;
	unsigned int i = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!number)
	{
		first_node = *list_head;
		*list_head = (*list_head)->next;
		free(first_node->str);
		free(first_node);
		return (1);
	}
	first_node = *list_head;
	while (first_node)
	{
		if (i == number)
		{
			prev_node->next = first_node->next;
			free(first_node->str);
			free(first_node);
			return (1);
		}
		i++;
		prev_node = first_node;
		first_node = first_node->next;
	}
	return (0);
}

/**
 * nodePrint_str - Print the strings of each node in a linked list.
 * @head: A pointer to the head node of the linked list.
 *
 * This function prints the strings stored in each node of the linked list.
 * If a node's string is NULL, it prints "(nil)" instead. Each string is
 * followed by a newline character.
 *
 * Return: The number of nodes in the linked list.
 */

size_t nodePrint_str(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * nodeAdd_end - Add a new node at the end of a linked list.
 * @head_pointer: A pointer to the pointer of the head node of the linked list.
 * @string: The string to be stored in the new node.
 * @number: An integer to be stored in the new node.
 *
 * Return: A pointer to new node, or NULL if function fails to create the node.
 */

list_t *nodeAdd_end(list_t **head_pointer, const char *string, int number)
{
	list_t *new_node, *node;

	if (!head_pointer)
		return (NULL);

	node = *head_pointer;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = number;
	if (string)
	{
		new_node->str = _strdup(string);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head_pointer = new_node;
	return (new_node);
}

/**
 * addStart_node - Add a new node at the beginning of a linked list.
 * @head_pointer: A pointer to the pointer of the head node of the linked list.
 * @string: The string to be stored in the new node.
 * @number: An integer to be stored in the new node.
 *
 * Return: A pointer to new node, or NULL if function fails to create the node.
 */


list_t *addStart_node(list_t **head_pointer, const char *string, int number)
{
	list_t *new_head;

	if (!head_pointer)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = number;
	if (string)
	{
		new_head->str = _strdup(string);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head_pointer;
	*head_pointer = new_head;
	return (new_head);
}
