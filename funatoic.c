#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
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

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
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

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
