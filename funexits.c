#include "shell.h"

/**
 * _strchr - Locate the first occurrence of a character in a string
 * @string: Pointer to the string to search
 * @x: The character to locate
 * Return: Ptr to the first occurrence of `c`, or NULL if not found.
 */

char *_strchr(char *string, char x)
{
	do {
		if (*string == x)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

/**
 * _strncpy - Copy at most 'n' characters from the 'source' string to the
 *            'destination' string. If 'source' is shorter than 'n' characters,
 *            the destination is null-padded to a length of 'n'.
 * @destination: Pointer to the buffer where the copied string will be stored.
 * @source: Pointer to the string to be copied.
 * @n: The maximum number of characters to copy from 'source'.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *d = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (d);
}


/**
 * _strncat - Concatenate two strings up to n bytes
 * @destination: Pointer to the destination buffer
 * @source: Pointer to the source string
 * @a: Number of bytes o concatenate
 * Return: A pointer to the destination buffer @dest.
 */

char *_strncat(char *destination, char *source, int a)
{
	int x, y;
	char *string = destination;

	x = 0;
	y = 0;
	while (destination[x] != '\0')
		x++;
	while (source[y] != '\0' && y < a)
	{
		destination[x] = source[y];
		x++;
		y++;
	}
	if (y < a)
		destination[x] = '\0';
	return (string);
}
