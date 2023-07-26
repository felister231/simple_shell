#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(data_info *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * _atoi - Convert a string to an integer
 * @s: Pointer to the string to be converted
 *
 * The function converts the input string @s to an integer.
 * @s: Pointer to the string to be converted
 *
 * Return: The converted integer value
 */

int _atoi(char *a)
{
	int b, signal = 1, symbol = 0, output;
	unsigned int result = 0;

	for (b = 0;  a[b] != '\0' && symbol != 2; b++)
	{
		if (a[b] == '-')
			signal *= -1;

		if (a[b] >= '0' && a[b] <= '9')
		{
			symbol = 1;
			result *= 10;
			result += (a[b] - '0');
		}
		else if (symbol == 1)
			symbol = 2;
	}

	if (signal == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * is_delim - Check if a character is a delimiter
 * @c: The character to be checked
 * @delim: Pointer to a string containing delimiter characters
 *
 * The function checks if the character @c is present in the string @delim,
 * which contains a set of delimiter characters.
 *
 * @c: The character to be checked
 * @delim: Pointer to a string containing delimiter characters
 *
 * Return: 1 if @c is a delimiter, otherwise 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Check if a character is an alphabet letter
 * @c: The character to be checked
 *
 * The function checks if the character @c is an alphabet letter (a-z or A-Z).
 *
 * @c: The character to be checked
 *
 * Return: 1 if @c is an alphabet letter, otherwise 0
 */

int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}
