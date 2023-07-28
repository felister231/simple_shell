#include "shell.h"

/**
 * fun_findBuiltin - Check if the command is a built-in and execute it.
 * @data: Pointer to info_t struct containing shell information.
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
 * hsh - The main function of the simple shell program.
 * @data: Pointer to the info_t structure containing shell information.
 * @argv: Array of strings containing the command-line arguments.
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

