#include "shell.h"
/**
 * _eputs - Writes a string to the standard error (stderr).
 *
 * @string: The string to be written to stderr.
 *
 * Return: None (void).
 */

void _eputs(char *string)
{
	int a = 0;

	if (!string)
		return;
	while (string[a] != '\0')
	{
		errorputchar(string[a]);
		a++;
	}
}

/**
 * putstrfd - Writes a string to the specified file descriptor.
 *
 * @string: The string to be written.
 * @file_des: The file descriptor to write to.
 *
 * Return: The number of characters written to the file descriptor.
 *         If the input string is NULL, it returns 0.
 */
int putstrfd(char *string, int file_des)
{
	int a = 0;

	if (!string)
		return (0);
	while (*string)
	{
		a += put_Filedescriptor(*string++, file_des);
	}
	return (a);
}

/**
 * errorputchar - Writes a character to the standard error (stderr).
 *
 * @letter: The character to be written to stderr.
 *
 * Return: Always 1.
 */
int errorputchar(char letter)
{
	static int number;
	static char buffer[WRITE_BUF_SIZE];

	if (letter == BUF_FLUSH || number >= WRITE_BUF_SIZE)
	{
		write(2, buffer, number);
		number = 0;
	}
	if (letter != BUF_FLUSH)
		buffer[number++] = letter;
	return (1);
}

/**
 * put_Filedescriptor - Writes a character to the specified file descriptor.
 *
 * @letter: The character to be written.
 * @file_des: The file descriptor to write to.
 *
 * Return: Always 1.
 */

int put_Filedescriptor(char letter, int file_des)
{
	static int number;
	static char buffer[WRITE_BUF_SIZE];

	if (letter == BUF_FLUSH || number >= WRITE_BUF_SIZE)
	{
		write(file_des, buffer, number);
		number = 0;
	}
	if (letter != BUF_FLUSH)
		buffer[number++] = letter;
	return (1);
}

