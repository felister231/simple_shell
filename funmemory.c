#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @pointer: Address of the pointer to be freed.
 *
 * Return: 1 if the pointer was freed, otherwise 0.
 */


int bfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
