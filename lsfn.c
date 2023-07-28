#include"shell.h"

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
 * freeMem_list - Free the memory occupied by a linked list and its nodes.
 * @pointer_head: A pointer to the head node of the linked list.
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
