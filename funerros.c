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
		errorputchar(str[i]);
		i++;
	}
}

/**
 * putstrfd - Writes a string to the specified file descriptor.
 *
 * @str: The string to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written to the file descriptor.
 *         If the input string is NULL, it returns 0.
 */
int putstrfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_Filedescriptor(*str++, fd);
	}
	return (i);
}

/**
 * errorputchar - Writes a character to the standard error (stderr).
 *
 * @c: The character to be written to stderr.
 *
 * Return: Always 1.
 */
int errorputchar(char c)
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
 * put_Filedescriptor - Writes a character to the specified file descriptor.
 *
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: Always 1.
 */

int put_Filedescriptor(char c, int fd)
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

