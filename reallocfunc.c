#include "shell.h"

/**
 * _realloc - Reallocate memory block with a different size
 * @ptr: Pointer to the previously allocated memory block
 * @old_size: The size of the old memory block
 * @new_size: The size of the new memory block
 *
 * Return: Pointer to the reallocated memory block, or NULL on failure
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * _memset - Fill memory with a constant byte
 * @s: Pointer to the memory area to be filled
 * @b: The value to be set (as byte)
 * @n: The number of bytes to be filled
 *
 * Fill the memory area pointed to by 's' with the constant byte 'b'. The 'n'
 * parameter determines the number of bytes to be filled. Returns a pointer to
 * the memory area 's'.
 *
 * @s: Pointer to the memory area to be filled
 * @b: The value to be set (as byte)
 * @n: The number of bytes to be filled
 *
 * Return: Pointer to the memory area 's'
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Free a dynamically allocated array of strings
 * @pp: Pointer to the array of strings to be freed
 *
 * Frees the dynamically allocated memory for each string in the array, as well
 * as the array itself. It is the responsibility of the caller to ensure that
 * 'pp' is a valid pointer to a dynamically allocated array of strings.
 *
 * @pp: Pointer to the array of strings to be freed
 */


void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
