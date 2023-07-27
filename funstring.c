#include "shell.h"

/**
 * _strcat - Concatenates two strings.
 * @destination: Pointer to the destination string.
 * @source: Pointer to the source string.
 *
 * This function appends the contents of the source string to the destination
 * string, overwriting the null-terminator of the destination string, and
 * adds a new null-terminator at the end. Both strings must be null-terminated.
 *
 * Return: Pointer to the concatenated string (same as destination).
 */

char *_strcat(char *destination, char *source)
{
	char *zet = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (zet);
}

/**
 * str_Startwith - Checks if a string starts with a specified prefix.
 * @stack: Pointer to the input string.
 * @edle: Pointer to the prefix to check.
 *
 * This function checks if the input string starts with the given prefix.
 * It returns a pointer to the position in the input string after the prefix,
 * if the prefix is found. Otherwise, it returns NULL.
 *
 * Return: Pointer to the position after the prefix or NULL if not found.
 */

char *str_Startwith(const char *stack, const char *edle)
{
	while (*edle)
		if (*edle++ != *stack++)
			return (NULL);
	return ((char *)stack);
}

/**
 * _strlen - Calculates the length of a string.
 * @string: Pointer to the input string.
 *
 * This function calculates the length of the input string by counting the
 * number of characters until the null-terminator is reached.
 *
 * Return: Length of the string (number of characters).
 */

int _strlen(char *string)
{
	int j = 0;

	if (!string)
		return (0);

	while (*string++)
		j++;
	return (j);
}

/**
 * _strcmp - Compares two strings.
 * @string1: Pointer to the first string.
 * @string2: Pointer to the second string.
 *
 * This function compares two strings character by character and returns
 * the difference of the ASCII values of the first non-matching characters,
 * or zero if the strings are equal. The comparison is case-sensitive.
 *
 * Return: The length of the string.
 */

int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}
