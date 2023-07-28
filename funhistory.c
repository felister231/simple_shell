#include "shell.h"

/**
 * write_cmdhistory - Write the command history to a file
 * @data: Pointer to the info_t structure containing the command history
 * Return: On success, returns 1. On failure, returns -1.
 */

int write_cmdhistory(data_info *data)
{
	ssize_t file_descriptor;
	char *file_tag = get_Filehist(data);
	list_t *node = NULL;

	if (!file_tag)
		return (-1);

	file_descriptor = open(file_tag, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_tag);
	if (file_descriptor == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		putstrfd(node->str, file_descriptor);
		put_Filedescriptor('\n', file_descriptor);
	}
	put_Filedescriptor(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}


/**
 * get_Filehist - Get the path of the history file
 * @data: Pointer to the info_t structure containing the environment
 *
 * Return: On success, returns a pointer to a newly allocated string containing
 * the path of the history file. On failure or if the history file is not set,
 * returns NULL.
 */

char *get_Filehist(data_info *data)
{
	char *buffer, *directory;

	directory = _getenviroment(data, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}
