#include "shell.h"

/**
 * _putchar - Writes a character to the standard output (stdout).
 *
 * @c: The character to be written.
 *
 * Return: On success, returns 1. On failure, returns -1.
 */

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _puts - Writes a string to the standard output (stdout).
 *
 * @str: The string to be written.
 *
 * Return: None (void).
 */

void _puts(char *string)
{
	int j = 0;

	if (!string)
		return;
	while (string[j] != '\0')
	{
		_putchar(string[j]);
		j++;
	}
}

/**
 * _strdup - Duplicates a string.
 *
 * @str: The string to be duplicated.
 *
 * Return: On success, returns a pointer to the duplicated string.
 *         On failure or if str is NULL, returns NULL.
 */

char *_strdup(const char *string)
{
	int size = 0;
	char *zet;

	if (string == NULL)
		return (NULL);
	while (*string++)
		size++;
	zet = malloc(sizeof(char) * (size + 1));
	if (!zet)
		return (NULL);
	for (size++; size--;)
		zet[size] = *--string;
	return (zet);
}

<<<<<<< HEAD
/**
 * _strcpy - Copies a string pointed to by src to the buffer pointed to by dest.
 *
 * @dest: The buffer where the string is to be copied.
 * @src: The string to be copied.
 *
 * Return: The pointer to the destination buffer (dest).
 */
char *_strcpy(char *dest, char *src)
=======

char *_strcpy(char *destination, char *source)
>>>>>>> b2872033e64b528e39fa27000b1de076e47112f4
{
	int j = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[j])
	{
		destination[j] = source[j];
		j++;
	}
	destination[j] = 0;
	return (destination);
}
