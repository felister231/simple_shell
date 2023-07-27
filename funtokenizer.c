#include "shell.h"

/**
 * str_Delim - Split a string into words using a delimiter
 * @string: The input string to be split
 * @c: The delimiter character
 *
 * Split the input string into words based on  specified delimiter char 'd'.
 * Returns a dynamically allocated [] of strings containing words. The last
 * element of [] is set to NULL to indicate the end. Returns NULL if memory
 * allocation fails or if the input string is empty.
 *
 * Return: An array of strings containing the words, or NULL on failure
 */
char **str_Delim(char *string, char c)
{	int x, y, z, a, word_count = 0;
	char **b;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (x = 0; string[x] != '\0'; x++)
	{
		if ((string[x] != c && string[x + 1] == c) ||
				(string[x] != c && !string[x + 1]) || string[x + 1] == c)
		{			word_count++;
		}
	}
	if (word_count == 0)
		return (NULL);
	b = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!b)
		return (NULL);
	for (x = 0, y = 0; y < word_count; y++)
	{
		while (string[x] == c)
			x++;
		z = 0;
		while (string[x + z] != c && string[x + z] != '\0')
			z++;
		b[y] = (char *)malloc((z + 1) * sizeof(char));
		if (!b[y])
		{
			for (a = 0; a < y; a++)
				free(b[a]);
			free(b);
			return (NULL);
		}
		for (a = 0; a < z; a++)
			b[y][a] = string[x++];
		b[y][a] = '\0'; /* Null-terminate the word.*/
		while (string[x] == c)
			x++;
	}
	b[y] = NULL; /* Null-terminate the array of strings.*/
	return (b);
}
/**
 * strtow - Split a string into words using multiple delimiters
 * @input_string: The input string to be split
 * @delimiters: The delimiter characters
 *
 * Return: An array of strings containing the words, or NULL on failure
 */

char **strtow(char *input_string, char *delimiters)
{
	int a, b, word_length, char_index, word_count = 0;
	char **words;

	if (input_string == NULL || input_string[0] == 0)
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (a = 0; input_string[a] != '\0'; a++)
	{
		if (!is_delim(input_string[a], delimiters) && (is_delim(input_string[a + 1],
						delimiters) || !input_string[a + 1]))
			word_count++;
	}
	if (word_count == 0)
		return (NULL);
	words = malloc((1 + word_count) * sizeof(char *));
	if (!words)
		return (NULL);
	for (a = 0, b = 0; b < word_count; b++)
	{
		while (is_delim(input_string[a], delimiters))
			a++;
		word_length = 0;
		while (!is_delim(input_string[a + word_length], delimiters)
				&& input_string[a + word_length])
			word_length++;
		words[b] = malloc((word_length + 1) * sizeof(char));
		if (!words[b])
		{
			for (char_index = 0; char_index < b; char_index++)
				free(words[char_index]);
			free(words);
			return (NULL);
		}
		for (char_index = 0; char_index < word_length; char_index++)
			words[b][char_index] = input_string[a++];
		words[b][char_index] = '\0';
	}
	words[b] = NULL;
	return (words);
}
