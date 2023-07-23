#include "shell.h"

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}


void _puts(char *string)
{
	int j = 0;

	if (!string)
		return;
	while (string[j] != '\0')
	{
		_putchar(string[j]);
		j++;
	}
}


char *_strdup(const char *string)
{
	int size = 0;
	char *zet;

	if (string == NULL)
		return (NULL);
	while (*string++)
		size++;
	zet = malloc(sizeof(char) * (size + 1));
	if (!zet)
		return (NULL);
	for (size++; size--;)
		zet[size] = *--string;
	return (zet);
}


char *_strcpy(char *destination, char *source)
{
	int j = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[j])
	{
		destination[j] = source[j];
		j++;
	}
	destination[j] = 0;
	return (destination);
}
