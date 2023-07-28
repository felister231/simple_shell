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



