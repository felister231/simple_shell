#include "shell.h"
/**
 * _eputs - Writes a string to the standard error (stderr).
 *
 * @str: The string to be written to stderr.
 *
 * Return: None (void).
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _putsfd - Writes a string to the specified file descriptor.
 *
 * @str: The string to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written to the file descriptor.
 *         If the input string is NULL, it returns 0.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

/**
 * _eputchar - Writes a character to the standard error (stderr).
 *
 * @c: The character to be written to stderr.
 *
 * Return: Always 1.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Writes a character to the specified file descriptor.
 *
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: Always 1.
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

