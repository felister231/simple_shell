#include "shell.h"

/**
 * dup_chars - Extract a portion of a string and store it in a static buffer
 * @pathstr: Input string
 * @start: Starting index (inclusive) for extraction
 * @stop: Stopping index (exclusive) for extraction
 *
 * Return: Pointer to the static buffer containing the extracted characters
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Search for a command executable in the given path
 * @data: Pointer to the info_t struct
 * @pathString: Path string containing directories to search for the command
 * @command: Command to search for
 *
 * Return: Pointer to full path of command executable, or NULL if not found
 */

#include <stdlib.h>

char *find_path(info_t *data, char *pathString, char *command)
{
	int i = 0, current_position = 0;
	char *path;

	if (!pathString)
		return NULL;

	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_cmd(data, command))
			return command;
	}

	while (1)
	{
		if (!pathString[i] || pathString[i] == ':')
		{
			path = dup_chars(pathString, current_position, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_cmd(data, path))
				return path;
			if (!pathString[i])
				break;
			current_position = i;
		}
		i++;
	}

	return NULL;
}



/**
 * is_cmd - Check if the path is a regular file (executable command)
 * @info: Pointer to the info_t struct (unused)
 * @path: Path to check
 *
 * Return: 1 if the path is a regular file (executable command), 0 otherwise
 */

int is_cmd(info_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
