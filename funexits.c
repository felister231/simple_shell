#include "shell.h"

/**
 * _strchr - Locate the first occurrence of a character in a string
 * @s: Pointer to the string to search
 * @c: The character to locate
 * Return: Ptr to the first occurrence of `c`, or NULL if not found.
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * _strncpy - Copy a string up to n bytes
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source string
 * @n: Number of bytes to copy
 * Return: A pointer to the destination buffer @dest.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenate two strings up to n bytes
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source string
 * @n: Number of bytes to concatenate
 * Return: A pointer to the destination buffer @dest.
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
