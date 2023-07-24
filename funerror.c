#include "shell.h"

/**
 * remove_comments - Remove comments from the buffer
 * @buffer: Pointer to the buffer containing the input string
 *
 * This function removes comments from the input buffer. A comment is identified
 * by a '#' character that appears at the beginning of a line or after a space.
 * The function modifies the buffer in place by replacing the '#' character and
 * everything after it with a null terminator ('\0').
 */

void remove_comments(char *buffer)
{
	int j = 0;

	while (buffer[j] != '\0')
	{
		if (buffer[j] == '#' && (!j || buffer[j - 1] == ' '))
		{
			buffer[j] = '\0';
			break;
		}
		j++;
	}
}

/**
 * convert_number - Convert a number to a string representation in a given base
 * @num: The number to convert
 * @base: The base for the conversion (e.g., 2 for binary, 10 for decimal, etc.)
 * @flags: Flags to control the conversion behavior
 *
 * Return: A pointer to the string representation of the converted number
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * print_error - Print error message to standard error (stderr)
 * @info: Pointer to the info_t struct containing shell information
 * @estr: Error message to be printed
 *
 * This function prints an error message to standard error (stderr). It includes
 * the file name, line count, command name, and the specified error message.
 * Each part of the error message is separated by a colon and space (": ").
 *
 * @info: Pointer to the info_t struct containing shell information
 * @estr: Error message to be printed
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Print an integer to a file descriptor
 * @input: The integer to be printed
 * @fd: The file descriptor to which the integer is printed
 *
 * This function prints an integer to the specified file descriptor (fd). It
 * supports printing integers to either standard output (stdout) or standard
 * error (stderr) based on the provided file descriptor value. The function
 * returns the number of characters printed.
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * _erratoi - Convert a string to an integer
 * @s: The string to be converted
 *
 * This function converts a string to an integer. It handles positive integers
 * represented as strings and returns the corresponding integer value. The
 * function returns -1 if the input string is invalid or if the resulting
 * integer exceeds the maximum value representable by an integer (INT_MAX).
 *
 * @s: The string to be converted
 *
 * Return: The converted integer on success, or -1 on failure
 */

int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
