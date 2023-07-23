#include "main.h"

/**
 * remove_comments_from_string - Removes comments from a string
 * @buf: The input string to remove comments from
 *
 * Description: This function removes any comments from the input string.
 * A comment starts with '#' and continues until the end of the line.
 */
void remove_comments_from_string(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		/* If '#' is first char/ preceded by a space, remove the comment */
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}

/**
 * convert_number_to_string - Converts a number to a string representation
 * @num: The number to convert
 * @base: The base for the conversion (e.g., 10 for decimal)
 * @flags: Flags to control the conversion behavior
 *
 * Return: A pointer to the string representation of the number.
 *
 * Description: This function converts a number to its string representation
 * using the specified base. It also handles signed NOS if the CONVERT_UNSIGNED
 * flag is not set in the flags parameter.
 */
char *convert_number_to_string(long int num, int base, int flags)
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

	do

	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * print_d - Prints an integer to the specified file descriptor
 * @input: The integer to print
 * @fd: The file descriptor to print to
 *
 *  Return: The number of characters printed
 * Description: This prints an integer to specified file descriptor.
 * supports printing negative ints and allows selecting the file descriptor
 * to print to using the fd parameter.
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
	return (count);
}
