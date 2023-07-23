#include "main.h"

/**
 * is_interactive - Checks if the shell is running in interactive mode.
 * @info: A pointer to the info_t struct containing shell information.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int is_interactive(info_t *info)
{
	int interactive_mode = isatty(STDIN_FILENO) && info->readfd <= 2;

	return (interactive_mode);
}

/**
 * convert_string_to_integer - Converts a string to an integer.
 * @s: The input string to convert.
 *
 * Return: The converted integer value.
 */
int convert_string_to_integer(char *s)
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
 * is_alphabetic - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_character_delimiter - Checks if a char is present in a delimiter string.
 * @c: The character to check.
 * @delim: The delimiter string to search.
 *
 * Return: 1 if the character is found in the delimiter string, 0 otherwise.
 */
int is_character_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}

	return (0);
}
