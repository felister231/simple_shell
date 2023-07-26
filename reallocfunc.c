#include "shell.h"

/**
 * _realloc - Reallocate memory for a block of memory.
 * @pointer: Pointer to the memory block to reallocate.
 * @oldSize: Size of the current memory block.
 * @newSize: New size to reallocate.
 *
 * Return: Pointer to the reallocated memory block, or NULL on failure.
 */
void *_realloc(void *pointer, unsigned int oldSize, unsigned int newSize)
{
	char *ptr;

	if (!pointer)
		return (malloc(newSize));
	if (!newSize)
		return (free(pointer), NULL);
	if (newSize == oldSize)
		return (pointer);

	ptr = malloc(newSize);
	if (!ptr)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		ptr[oldSize] = ((char *)pointer)[oldSize];
	free(pointer);
	return (ptr);
}



/**
 * _memset - Fill memory with a constant byte
 * @string: Pointer to the memory area to be filled
 * @byte: The value to be set (as byte)
 * @number: The number of bytes to be filled
 *
 * Fill the memory area pointed to by 's' with the constant byte 'b'. The 'n'
 * parameter determines the number of bytes to be filled. Returns a pointer to
 * the memory area 's'.
 *
 * @string: Pointer to the memory area to be filled
 * @byte: The value to be set (as byte)
 * @number: The number of bytes to be filled
 *
 * Return: Pointer to the memory area 'string'
 */

char *_memset(char *string, char byte, unsigned int number)
{
	unsigned int j;

	for (j = 0; j < number; j++)
		string[j] = byte;
	return (string);
}

/**
 * freealloc - Free a dynamically allocated array of strings
 * @pp: Pointer to the array of strings to be freed
 *
 * Frees the dynamically allocated memory for each string in the array, as well
 * as the array itself. It is the responsibility of the caller to ensure that
 * 'pp' is a valid pointer to a dynamically allocated array of strings.
 *
 * @pp: Pointer to the array of strings to be freed
 */


void freealloc(char **pointer)
{
	char **j = pointer;

	if (!pointer)
		return;
	while (*pointer)
		free(*pointer++);
	free(j);
}
