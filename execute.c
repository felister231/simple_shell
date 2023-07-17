#include "shell.h"

void execute(char *input_command)
{
	int child_process, exit_process, number_signal;
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
	else
	{
		waitpid(pid, &child_process, 0);
		if (WIFEXITED(child_process))
		{
			exit_process = WEXITSTATUS(child_process);
			if (exit_process != 0)
			{
				printf("Command exec failed with status %d\n",exit_process);
			}
		}
		else if(WIFSIGNALED(child_process))
		{
			number_signal = WTERMSIG(child_process);
			printf("Command terminated by number signal  %d\n", number_signal);

		}
		free(input_command);
	}
}
int main()
{
execute(char *input_command);
}
