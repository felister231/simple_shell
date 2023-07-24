#include "shell.h"

/**
 * free_list - Free the memory occupied by a linked list and its nodes.
 * @head_ptr: A pointer to the head node of the linked list.
 *
 * This function frees the memory occupied by a linked list and its nodes,
 * including the memory allocated for the string in each node.
 *
 * Return: None.
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * delete_node_at_index - Delete a node at a specific index in a linked list.
 * @head: A pointer to the head node of the linked list.
 * @index: The index of the node to delete.
 *
 * This function deletes the node at the specified index in the linked list.
 * It frees the memory allocated for the string in the node and the memory
 * occupied by the node itself.
 *
 * Return: 1 if the node was successfully deleted, 0 otherwise.
 */


int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * print_list_str - Print the strings of each node in a linked list.
 * @h: A pointer to the head node of the linked list.
 *
 * This function prints the strings stored in each node of the linked list.
 * If a node's string is NULL, it prints "(nil)" instead. Each string is
 * followed by a newline character.
 *
 * Return: The number of nodes in the linked list.
 */

size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * add_node_end - Add a new node at the end of a linked list.
 * @head: A pointer to the pointer of the head node of the linked list.
 * @str: The string to be stored in the new node.
 * @num: An integer to be stored in the new node.
 *
 * Return: A pointer to new node, or NULL if function fails to create the node.
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
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
		*head = new_node;
	return (new_node);
}

/**
 * add_node - Add a new node at the beginning of a linked list.
 * @head: A pointer to the pointer of the head node of the linked list.
 * @str: The string to be stored in the new node.
 * @num: An integer to be stored in the new node.
 *
 * Return: A pointer to new node, or NULL if function fails to create the node.
 */


list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}
