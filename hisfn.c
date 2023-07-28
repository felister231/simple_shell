#include "shell.h"

/**
 * readAll_his - Read history from history file and build the history list.
 * @data: Pointer to the info_t structure containing the history list.
 *
 * Return: 1 on success, 0 on failure.
 */


int readAll_his(data_info *data)
{
	int a, last_index = 0, linecount = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat st;
	char *buffer = NULL, *file_tag = get_Filehist(data);

	if (!file_tag)
		return (0);

	file_descriptor = open(file_tag, O_RDONLY);
	free(file_tag);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (a = 0; a < file_size; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			history_build_ls(data, buffer + last_index, linecount++);
			last_index = a + 1;
		}
	if (last_index != a)
		history_build_ls(data, buffer + last_index, linecount++);
	free(buffer);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		deleteNode_index(&(data->history), 0);
	renum_Nodehistory(data);
	return (data->histcount);
}

/**
 * history_build_ls - Build and maintain the history list.
 * @data: Pointer to the info_t structure containing the history list.
 * @buffer: Pointer to the buffer containing the command line input.
 * @linecount: The current line count.
 *
 * Return: Always returns 0.
 */

int history_build_ls(data_info *data, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	nodeAdd_end(&node, buffer, linecount);

	if (!data->history)
		data->history = node;
	return (0);
}


/**
 * renum_Nodehistory - Renumber histylist nodes sequential nos starting from 0.
 * @data: Pointer to the info_t structure containing the history list.
 *
 * Return: The total number of history list nodes after renumbering.
 */
int renum_Nodehistory(data_info *data)
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
