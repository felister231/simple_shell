#include "shell.h"
/**
 * pathCmd - Search for a command executable in the given path
 * @data: Pointer to the info_t struct
 * @pathString: Path string containing directories to search for the command
 * @command: Command to search for
 *
 * Return: Pointer to full path of command executable, or NULL if not found
 */

#include <stdlib.h>

char *pathCmd(data_info *data, char *pathString, char *command)
{
	int i = 0, current_position = 0;
	char *path;

	if (!pathString)
		return (NULL);

	if ((_strlen(command) > 2) && str_Startwith(command, "./"))
	{
		if (is_commandline(data, command))
			return (command);
	}

	while (1)
	{
		if (!pathString[i] || pathString[i] == ':')
		{
			path = duplicate_chars(pathString, current_position, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_commandline(data, path))
				return (path);
			if (!pathString[i])
				break;
			current_position = i;
		}
		i++;
	}

	return (NULL);
}
