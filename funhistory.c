#include "shell.h"

/**
 * write_history - Write the command history to a file
 * @info: Pointer to the info_t structure containing the command history
 * Return: On success, returns 1. On failure, returns -1.
 */

int write_history(info_t *data)
{
	ssize_t file_descriptor;
	char *file_tag = get_history_file(data);
	list_t *node = NULL;

	if (!file_tag)
		return (-1);

	file_descriptor = open(file_tag, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_tag);
	if (file_descriptor == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}


/**
 * get_history_file - Get the path of the history file
 * @info: Pointer to the info_t structure containing the environment
 *
 * Return: On success, returns a pointer to a newly allocated string containing
 * the path of the history file. On failure or if the history file is not set,
 * returns NULL.
 */

char *get_history_file(info_t *data)
{
	char *buffer, *directory;

	directory = _getenv(data, "HOME=");
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


/**
 * build_history_list - Build and maintain the history list.
 * @info: Pointer to the info_t structure containing the history list.
 * @buf: Pointer to the buffer containing the command line input.
 * @linecount: The current line count.
 *
 * Return: Always returns 0.
 */

int build_history_list(info_t *data, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	add_node_end(&node, buffer, linecount);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * read_history - Read history from history file and build the history list.
 * @info: Pointer to the info_t structure containing the history list.
 *
 * Return: 1 on success, 0 on failure.
 */


int read_history(info_t *data)
{
	int a, last_index = 0, linecount = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat st;
	char *buffer = NULL, *file_tag = get_history_file(data);

	if (!file_tag)
		return 0;

	file_descriptor = open(file_tag, O_RDONLY);
	free(file_tag);
	if (file_descriptor == -1)
		return 0;
	if (!fstat(file_descriptor, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return 0;
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return 0;
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return free(buffer), 0;
	close(file_descriptor);
	for (a = 0; a < file_size; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			build_history_list(data, buffer + last_index, linecount++);
			last_index = a + 1;
		}
	if (last_index != a)
		build_history_list(data, buffer + last_index, linecount++);
	free(buffer);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		delete_node_at_index(&(data->history), 0);
	renumber_history(data);
	return data->histcount;
}


/**
 * renumber_history - Renumber histylist nodes sequential nos starting from 0.
 * @info: Pointer to the info_t structure containing the history list.
 *
 * Return: The total number of history list nodes after renumbering.
 */
int renumber_history(info_t *data)
{
	list_t *node = data->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (data->histcount = a);
}
