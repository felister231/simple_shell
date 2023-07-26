#include "shell.h"

/**
 * main - entry point of my simple shell project
 * @argc: argument  count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	data_info data[] = { INFO_INIT };
	int fileD = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileD)
		: "r" (fileD));

	if (argc == 2)
	{
		fileD = open(argv[1], O_RDONLY);
		if (fileD == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				errorputchar('\n');
				errorputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fileD;
	}
	enviro_list_pop(data);
	readAll_his(data);
	hsh(data, argv);
	return (EXIT_SUCCESS);
}
