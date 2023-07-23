#include "main.h"

/**
 * is_interactive - Checks if the shell is running interactively
 * @info: Pointer to the parameter struct containing environment info
 *
 * Return: 1 if STDIN is a terminal/ readfd is not greater than 2, 0 otherwise
 */
int is_interactive(info_t *info)
{
	/* Returns true if STDIN is a terminal and readfd is not greater than 2 */
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * convert_string_to_integer - Converts a string to an integer
 * @s: The input string
 *
 * Return: The converted integer value
 */
int convert_string_to_integer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		/* Checks for a negative sign and updates the sign variable */
		if (s[i] == '-')
			sign *= -1;

		/* Converts numeric characters to an integer */
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	/* Handles the sign and returns the result as an integer */
	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * is_alphabetic - Checks if a character is alphabetic
 * @c: The character to check
 *
 * Return: 1 if the character is a lowercase or uppercase letter, 0 otherwise
 */
int is_alphabetic(int c)
{
	/* Returns true if the character is a lowercase or uppercase letter */
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_character_delimiter - Check if a char is in the provided delimiter string
 * @c: The character to check
 * @delim: The delimiter string to search
 *
 * Return: 1 if the character is found in the delimiter string, 0 otherwise
 */
int is_character_delimiter(char c, char *delim)
{
	/* Loops through the delimiter string & returns true if the char is found */
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

