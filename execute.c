#include "shell.h"

void execute(char *input_command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(input_command);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execlp(input_command, input_command, NULL);

		perror("execlp");
		free (input_command);
		exit(EXIT_FAILURE);
	}
}

