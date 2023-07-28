#include "shell.h"

/**
 * print_Errorstderr - Print error message to standard error (stderr)
 * @data: Pointer to the info_t struct containing shell information
 * @errorstr: Error message to be printed
 *
 * Return: void
 */


void print_Errorstderr(data_info *data, char *errorstr)
{
	_eputs(data->fname);
	_eputs(": ");
	print_Intdescriptor(data->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(data->argv[0]);
	_eputs(": ");
	_eputs(errorstr);
}

/**
 * print_Intdescriptor - Print an integer to a file descriptor
 * @number: The integer to be printed
 * @file_des: The file descriptor to which the integer is printed
 *
 * This function prints an integer to the specified file descriptor (fd). It
 * supports printing integers to either standard output (stdout) or standard
 * error (stderr) based on the provided file descriptor value. The function
 * Return: The number of characters printed.
 */

int print_Intdescriptor(int number, int file_des)
{
	int (*printChar)(char) = _putchar;
	int a, count = 0;
	unsigned int absolute, current;

	if (file_des == STDERR_FILENO)
		printChar = errorputchar;
	if (number < 0)
	{
		absolute = -number;
		printChar('-');
		count++;
	}
	else
		absolute = number;
	current = absolute;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (absolute / a)
		{
			printChar('0' + current / a);
			count++;
		}
		current %= a;
	}
	printChar('0' + current);
	count++;

	return (count);
}

/**
 * _erratoi - Convert a string to an integer
 * @string: The string to be converted
 *
 * This function converts a string to an integer. It handles positive integers
 * represented as strings and returns the corresponding integer value. The
 * function returns -1 if the input string is invalid or if the resulting
 * integer exceeds the maximum value representable by an integer (INT_MAX).
 * @string: The string to be converted
 *
 * Return: The converted integer on success, or -1 on failure
 */

int _erratoi(char *string)
{
	int a = 0;
	unsigned long int result = 0;

	if (*string == '+')
		string++;  /* TODO: why does this make main return 255? */
	for (a = 0;  string[a] != '\0'; a++)
	{
		if (string[a] >= '0' && string[a] <= '9')
		{
			result *= 10;
			result += (string[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
