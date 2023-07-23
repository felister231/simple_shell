#include "shell.h"


char *_strcat(char *destination, char *source)
{
	char *zet = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (zet);
}


char *starts_with(const char *stack, const char *edle)
{
	while (*edle)
		if (*edle++ != *stack++)
			return (NULL);
	return ((char *)stack);
}


int _strlen(char *string)
{
	int j = 0;

	if (!string)
		return (0);

	while (*string++)
		j++;
	return (j);
}


int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
