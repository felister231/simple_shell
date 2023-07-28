#include "shell.h"

/**
 * remove_Bufcomments - Remove comments from the buffer
 * @buf: Pointer to the buffer containing the input string
 *
 * This function removes comments from  input buffer. A comment is identified
 * by a '#' character that appears at the beginning of a line or after a space.
 * The function modifies the buffer in place by replacing the '#' character and
 * everything after it with a null terminator ('\0').
 */


void remove_Bufcomments(char *buf)
{
	int index = 0;

	while (buf[index] != '\0')
	{
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
		index++;
	}
}


/**
 * convert_Numstr - Convert a number to a string representation in a given base
 * @number: The number to convert
 * @c_base: The base for conversion (e.g., 2 for binary, 10 for decimal, etc.)
 * @c_flags: Flags to control the conversion behavior
 *
 * Return: A pointer to the string representation of the converted number
 */

char *convert_Numstr(long int number, int c_base, int c_flags)
{
	static char *Array;
	static char buf[50];
	char sign = 0;
	char *pointer;
	unsigned long a = number;

	if (!(c_flags & CONVERT_UNSIGNED) && number < 0)
	{
		a = -number;
		sign = '-';
	}

	Array = c_flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buf[49];
	*pointer = '\0';

	do

	{
		*--pointer = Array[a % c_base];
		a /= c_base;
	} while (a != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}
