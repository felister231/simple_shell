#include "shell.h"

/**
 * fork_commandline - Fork and execute a command in the info_t struct.
 * @data: Pointer to info_t struct containing shell information
 *
 * Return: None.
 */

void fork_commandline(data_info *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_Enviroment_var(data)) == -1)
		{
			free_Datainfo(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_Errorstderr(data, "Permission denied\n");
		}
	}
}



/**
 * find_commandLine - Find and execute the given command.
 * @data: Pointer to info_t struct containing shell information.
 *
 * This function checks if the command contains any arguments and if it does,
 * it tries to locate the path of the command using the "pathCmd" function.
 * If the command is found, it updates the path in the info_t struct and calls
 * the "fork_commandline" function to execute the command.
 * it checks if the command is an absolute path or a built-in command, and if
 * so, it executes the command. Otherwise, it prints an error message
i *
 * Return: None.
 */

void find_commandLine(data_info *data)
{
	char *path = NULL;
	int a, b;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (a = 0, b = 0; data->arg[a]; a++)
		if (!is_delim(data->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = pathCmd(data, _getenviroment(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_commandline(data);
	}
	else
	{
		if ((interactive(data) || _getenviroment(data, "PATH=")
					|| data->argv[0][0] == '/') && is_commandline(data, data->argv[0]))
			fork_commandline(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_Errorstderr(data, "not found\n");
		}
	}
}
