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
 * @info: Pointer to the info_t struct
 * @pathstr: Path string containing directories to search for the command
 * @cmd: Command to search for
 *
 * Return: Pointer to full path of command executable, or NULL if not found
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * is_cmd - Check if the path is a regular file (executable command)
 * @info: Pointer to the info_t struct (unused)
 * @path: Path to check
 *
 * Return: 1 if the path is a regular file (executable command), 0 otherwise
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
