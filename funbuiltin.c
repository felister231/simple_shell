#include "shell.h"

/**
 * _myhelp - Provides help information for the shell.
 *
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *data)
{
	char **argument_array;

	argument_array = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argument_array); /* temp att_unused workaround */
	return (0);
}

/**
 * _myexit - Exits the shell with a given exit status or error code.
 *
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: If the function is called with an exit argument, it returns -2.
 *         If the argument is not a valid integer,prints an error message
 *         and returns 1.
 *         If no exit arg is provided, it returns -2 and sets err_num to -1.
 */

int _myexit(info_t *data)
{
	int check_exit;

	if (data->argv[1])  /* If there is an exit arguement */
	{
		check_exit = _erratoi(data->argv[1]);
		if (check_exit == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}
		data->err_num = _erratoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * _mycd - Changes the current directory of the process.
 *
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */

int _mycd(info_t *data)
{
	char *d, *directory, buffer[1024];
	int chdir_ret;

	d = getcwd(buffer, 1024);
	if (!d)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		directory = _getenv(data, "HOME=");
		if (!directory)
			chdir_ret = /* TODO: what should this be? */
				chdir((directory = _getenv(data, "PWD=")) ? directory : "/");
		else
			chdir_ret = chdir(directory);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(d);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((directory = _getenv(data, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		_eputs(data->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
