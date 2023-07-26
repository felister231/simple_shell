#include "shell.h"

/**
 * fork_commandline - Fork and execute a command in the info_t struct.
 * @info: Pointer to info_t struct containing shell information
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
 * fun_findBuiltin - Check if the command is a built-in and execute it.
 * @info: Pointer to info_t struct containing shell information.
 *
 * This function iterates through a table of recognized built-in commands
 * and checks if the current command matches any of them. If a match is found,
 * it updates the line count in the info_t struct and calls the corresponding
 * built-in function with the given info_t struct. If no match is found, it
 * returns -1 to indicate that the command is not a built-in.
 *
 * Return: The result of the execution or -1 if not a built-in.
 */
int fun_findBuiltin(data_info *data)
{
	int a, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", _myenvironment},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", _mysetenviroment},
		{"unsetenv", unset_Environ_variroment},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(data->argv[0], builtintbl[a].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[a].func(data);
			break;
		}
	return (built_in_ret);
}

/**
 * find_commandLine - Find and execute the given command.
 * @info: Pointer to info_t struct containing shell information.
 *
 * This function checks if the command contains any arguments and if it does,
 * it tries to locate the path of the command using the "pathCmd" function.
 * If the command is found, it updates the path in the info_t struct and calls
 * the "fork_commandline" function to execute the command. If the command is not found,
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

/**
 * hsh - The main function of the simple shell program.
 * @info: Pointer to the info_t structure containing shell information.
 * @av: Array of strings containing the command-line arguments.
 *
 * Return: Returns exit status of shell or a special value if an error occurs.
 */

int hsh(data_info *data, char **argv)
{
	ssize_t a = 0;
	int builtin_result = 0;

	while (a != -1 && builtin_result != -2)
	{
		clear_Datainfo(data);
		if (interactive(data))
			_puts("$ ");
		errorputchar(BUF_FLUSH);
		a = get_userinput(data);
		if (a != -1)
		{
			set_Datainfo(data, argv);
			builtin_result = fun_findBuiltin(data);
			if (builtin_result == -1)
				find_commandLine(data);
		}
		else if (interactive(data))
			_putchar('\n');
		free_Datainfo(data, 0);
	}
	write_cmdhistory(data);
	free_Datainfo(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (builtin_result == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_result);
}

