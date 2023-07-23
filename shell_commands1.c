#include "main.h"

/**
 * show_help - Displays the help message for the shell.
 * @info: A pointer to the info_t struct containing shell information.
 *
 * Return: Always 0.
 */
int show_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

/**
 * exit_shell - Handles the 'exit' command in the shell.
 * @info: A pointer to the info_t struct containing shell information.
 *
 * Return: -2 to indicate that the shell should exit gracefully.
 *         If exit arg is provided,the exit code is set in info->err_num.
 */
int exit_shell(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Handles the 'cd' command in the shell to change WD
 * @info: A pointer to the info_t struct containing shell information.
 *
 * Return: Always 0.
 */
int change_directory(info_t *info)
{	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);

	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1]) /* If no argument is provided, change to HOME directory */
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
		chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
		chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else /* Change to the specified directory */
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD=")); /* Update OLDPWD */
		_setenv(info, "PWD", getcwd(buffer, 1024)); /* Update PWD */
	}
	return (0);
}
