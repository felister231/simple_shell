#include "shell.h"

/**
 * duplicate_chars - Extract a portion of a string and store  a static buffer
 * @pathstr: Input string
 * @start: Starting index (inclusive) for extraction
 * @stop: Stopping index (exclusive) for extraction
 *
 * Return: Pointer to the static buffer containing the extracted characters
 */

char *duplicate_chars(char *pathstr, int start, int stop)
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
 * is_commandline - Check if the path is a regular file (executable command)
 * @data: Pointer to the info_t struct (unused)
 * @path: Path to check
 *
 * Return: 1 if the path is a regular file (executable command), 0 otherwise
 */

int is_commandline(data_info *data, char *path)
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
