#include "main.h"

/**
 * find_character_in_string - Finds the first occurrence of a char in a string
 * @s: The input string
 * @c: The character to find
 *
 * Return: Pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *find_character_in_string(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * concatenate_strings_n - Concatenates two strings up to 'n' chars from src
 * @dest: The destination string
 * @src: The source string
 * @n: The maximum number of characters to concatenate from src
 *
 * Return: Pointer to the destination string.
 */
char *concatenate_strings_n(char *dest, char *src, int n)
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

/**
 * copy_string_n - Copies 'n' characters from src to dest
 * @dest: The destination string
 * @src: The source string
 * @n: The number of characters to copy
 *
 * Return: Pointer to the destination string.
 */
char *copy_string_n(char *dest, char *src, int n)
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

